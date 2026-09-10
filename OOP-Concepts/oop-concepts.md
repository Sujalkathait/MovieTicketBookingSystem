# OOP Concepts
Object-Oriented Programming (OOP) concepts heavily influence our Class Design.

## Encapsulation
Internal states are hidden from the outside. For instance, `Booking::totalAmount` and `Customer::phone` are private properties accessed only via public getter methods, preventing unauthorized modification.

## Abstraction
The system hides complex logic. A user simply triggers `bookingService.startBooking()`, entirely unaware of the complex seating validations, price calculations, and ticket generations happening behind the scenes.

## Inheritance
`UpiPayment`, `CardPayment`, and `CashPayment` all inherit from the common `Payment` interface, inheriting the contract to implement a `pay()` method.

## Polymorphism
The system handles payments via the `Payment` interface. During runtime, calling `pay(amount)` dynamically executes the correct logic whether the underlying object is a `UpiPayment` or a `CardPayment`.
