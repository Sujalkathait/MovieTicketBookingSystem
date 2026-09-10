# SOLID Principles

The SOLID principles are a set of five design guidelines intended to make software designs more understandable, flexible, and maintainable. Applying them prevents the codebase from rotting over time as new features are added.

The Cinema Booking System was architected with these principles strictly in mind.

---

## 1. Single Responsibility Principle (SRP)
**Definition:** A class should have one, and only one, reason to change. It should encapsulate a single, focused responsibility.

**Application in the System:**
Without SRP, a developer might put the logic for booking, price calculation, and ticket printing all inside a massive `BookingService` class. If the printing format changes, the `BookingService` has to be modified, risking breaking the booking logic.

We separated responsibilities into distinct classes:
- `BookingService` → Orchestrates the booking flow.
- `PriceCalculator` → Only knows how to compute prices based on Seat Tiers.
- `TicketPrinter` → Only knows how to format and output a string representation of the ticket.

## 2. Open/Closed Principle (OCP)
**Definition:** Software entities (classes, modules, functions) should be open for extension, but closed for modification.

**Application in the System:**
Assume the cinema decides to support **Apple Pay** next month. In a bad design, we would have to open the `BookingService` class and add a bunch of `if (paymentType == "ApplePay")` statements.

Because of OCP, our `BookingService` is *closed for modification*. We never have to touch its source code. We simply extend our system by creating a new `ApplePayment` class that inherits from the `Payment` interface. The `BookingService` is *open for extension* via polymorphism.

## 3. Liskov Substitution Principle (LSP)
**Definition:** Objects of a superclass shall be replaceable with objects of its subclasses without breaking the application.

**Application in the System:**
Any method in the system that accepts the base `Payment` object must work flawlessly whether we pass it a `UpiPayment`, `CardPayment`, or `CashPayment`. 

None of the subclasses throw unexpected exceptions (like `UnsupportedOperationException`) when `pay()` is called, ensuring the contract defined by the base class is honored perfectly.

## 4. Interface Segregation Principle (ISP)
**Definition:** No client should be forced to depend on methods it does not use. Interfaces should be thin and focused rather than "fat".

**Application in the System:**
The system uses focused abstraction. The `Payment` interface only mandates the `pay(double amount)` method. It does not force `CashPayment` to implement an irrelevant method like `validateCardExpiryDate()`. 
If card validation is needed, it is kept exclusively inside the `CardPayment` concrete class or a highly specialized interface.

## 5. Dependency Inversion Principle (DIP)
**Definition:** High-level modules should not depend on low-level modules. Both should depend on abstractions (interfaces).

**Application in the System:**
`BookingService` is a high-level module containing complex business rules. `UpiPayment` is a low-level module dealing with API implementation details.

In our system, `BookingService` **does not** instantiate or depend on `UpiPayment` directly.
```cpp
// BAD: High-level depends on low-level
class BookingService {
    UpiPayment upi; 
};
```

Instead, it depends on the `Payment` abstraction:
```cpp
// GOOD: High-level depends on abstraction
class BookingService {
    void processTransaction(Payment* payment); 
};
```
The exact implementation (Upi, Card, etc.) is injected dynamically at runtime.

---

### Next Steps in Design
By merging the identified objects, relationships, OOP features, and SOLID rules, we can definitively finalize our **[Class Design](../Class-Design/class-design.md)**.
