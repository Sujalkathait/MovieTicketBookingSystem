# Object Relationships

Once candidate classes have been identified through Noun-Verb Analysis, the next critical step in Low-Level Design (LLD) is defining how these objects relate to one another. Properly mapping relationships ensures data integrity, prevents memory leaks, and creates a logical hierarchy.

In Object-Oriented Design, we primarily utilize four types of relationships.

---

## 1. Composition (Strong "Has-A" Relationship)
**Symbol:** `◆──` 
**Definition:** A strict whole-part relationship where the child object *cannot exist* independently of the parent object. If the parent is destroyed, the child is destroyed.

**Usage in our system:**
- **Cinema ◆── Screen**: A physical `Screen` (auditorium) cannot exist floating in a void; it is a permanent structural part of a `Cinema`. If the Cinema closes, the Screen is gone.
- **Screen ◆── Seat**: A physical `Seat` is bolted to the floor of a `Screen`. It cannot exist without the Screen.
- **Show ◆── ShowSeat**: A `ShowSeat` represents the booking status of a seat for a specific show. If the `Show` is cancelled, all `ShowSeat` statuses for that show instantly cease to exist.

## 2. Aggregation (Weak "Has-A" Relationship)
**Symbol:** `◇──`
**Definition:** A whole-part relationship where the child object *can exist* independently of the parent object. They are loosely coupled.

**Usage in our system:**
- **Cinema ◇── Movie**: A `Cinema` has a list of currently playing `Movies`. However, if the Cinema closes, the `Movie` still exists in the real world (or in other cinemas).
- **Show ◇── Movie**: A `Show` is a screening of a `Movie`. If the `Show` is cancelled, the `Movie` itself is not destroyed.
- **Show ◇── Screen**: A `Show` takes place in a `Screen`. If the `Show` ends, the `Screen` remains intact for the next show.

## 3. Association (General "Uses-A" Relationship)
**Symbol:** `──`
**Definition:** A generic relationship where objects interact with each other, but neither owns the other.

**Usage in our system:**
- **Booking ── Customer**: A `Booking` is associated with a `Customer`. The booking doesn't "own" the customer.
- **Booking ── Show**: A `Booking` points to the `Show` it was made for.
- **Booking ── Seat**: A `Booking` references the physical `Seats` reserved.
- **Booking ── Payment**: A `Booking` references the `Payment` transaction that verified it.

## 4. Generalization / Inheritance ("Is-A" Relationship)
**Symbol:** `▲`
**Definition:** A relationship where a specialized subclass inherits the properties and behaviors of a generalized superclass or interface.

**Usage in our system:**
To strictly adhere to the Open/Closed Principle, the system defines a generalized `Payment` interface. Specific payment methods inherit from this interface.

```text
       Payment (Interface)
              ▲
              │
      ┌───────┼───────┐
      │       │       │
  UpiPayment  │  CashPayment
         CardPayment
```
- A `UpiPayment` **IS-A** `Payment`.
- A `CardPayment` **IS-A** `Payment`.

---

### Relational Summary Matrix

| Entity A | Relationship Type | Entity B | Description |
|---|---|---|---|
| **Cinema** | Composition (`◆──`) | **Screen** | Cinema physically owns its Screens. |
| **Screen** | Composition (`◆──`) | **Seat** | Screen physically owns its Seats. |
| **Show** | Composition (`◆──`) | **ShowSeat** | Show strictly owns the status of its seats. |
| **Cinema** | Aggregation (`◇──`) | **Movie** | Cinema hosts Movies. |
| **Show** | Aggregation (`◇──`) | **Movie** | Show features a Movie. |
| **Booking** | Association (`──`) | **Customer** | Booking is linked to a Customer. |
| **UpiPayment**| Inheritance (`▲`) | **Payment** | UPI is a type of Payment. |

---

### Next Steps in Design
With our objects and relationships strictly mapped, we can now apply software engineering principles to ensure our code is scalable and robust. This leads us to **[OOP Concepts](../OOP-Concepts/oop-concepts.md)** and **[SOLID Principles](../SOLID-Principles/solid-principles.md)**.
