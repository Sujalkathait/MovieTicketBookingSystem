# Class Design

With our analysis complete and our architectural principles (OOP & SOLID) defined, we convert our logical entities into a strict Class Design. This acts as the final blueprint before writing C++ code or drawing UML diagrams.

Below is the detailed data dictionary defining the responsibilities and dependencies of every class in the Cinema Booking System.

---

## Core Entities (Structural)

### 1. `Cinema`
*The root container class.*
- **Responsibilities:** Holds all the screens and manages the movies currently playing at the establishment.
- **Key Attributes:** `name: string`, `screens: vector<Screen>`, `movies: vector<Movie>`
- **Dependencies:** Composes `Screen`, Aggregates `Movie`.

### 2. `Screen`
*A physical hall/auditorium.*
- **Responsibilities:** Defines a physical space that holds physical seats.
- **Key Attributes:** `screenNumber: int`, `seats: vector<Seat>`
- **Dependencies:** Composes `Seat`.

### 3. `Seat`
*The physical chair.*
- **Responsibilities:** Stores static data about a physical seat location and its pricing tier.
- **Key Attributes:** `seatNumber: string` (e.g., "A1"), `type: SeatType` (e.g., GOLD, SILVER).

### 4. `Movie`
*The film.*
- **Responsibilities:** Stores metadata about a film.
- **Key Attributes:** `title: string`, `durationMinutes: int`.

---

## Core Entities (Transactional & Temporal)

### 5. `Show`
*A temporal event.*
- **Responsibilities:** Links a `Movie` and a `Screen` at a specific `showTime`. Crucially, it manages the *availability* of seats for this specific screening.
- **Key Attributes:** `showTime: string`, `movie: Movie`, `screen: Screen`, `showSeats: vector<ShowSeat>`
- **Dependencies:** Composes `ShowSeat`.

### 6. `ShowSeat`
*The runtime state of a seat.*
- **Responsibilities:** Wraps a physical `Seat` and tracks whether it is AVAILABLE or BOOKED for a specific `Show`.
- **Key Methods:** `isAvailable(): bool`, `book(): void`
- **Dependencies:** Associates with `Seat`.

### 7. `Booking`
*The receipt record.*
- **Responsibilities:** Aggregates all data resulting from a successful transaction.
- **Key Attributes:** `bookingId: string`, `customer: Customer`, `show: Show`, `seats: vector<ShowSeat>`, `totalAmount: double`, `payment: Payment`

---

## Actors & Services (Operational)

### 8. `Customer`
*The end user.*
- **Responsibilities:** Provides identifying data for the booking.
- **Key Attributes:** `name: string`, `phone: string`

### 9. `BookingService`
*The System Orchestrator.*
- **Responsibilities:** The high-level controller that prompts the user, validates availability, triggers payment, and generates the booking. (Strictly follows the Facade pattern).
- **Key Methods:** `startBooking(): void`

### 10. `PriceCalculator`
*The Financial Engine.*
- **Responsibilities:** Follows SRP. Iterates over selected `ShowSeats`, checks their underlying `Seat` tier, and returns a total double value.
- **Key Methods:** `calculate(vector<ShowSeat>): double`

### 11. `TicketPrinter`
*The Output Engine.*
- **Responsibilities:** Follows SRP. Takes a finalized `Booking` object and formats it into a printable string/console output.
- **Key Methods:** `printTicket(Booking): void`

---

## Payment Subsystem

### 12. `Payment` (Interface)
*The Abstraction.*
- **Responsibilities:** Defines the contract all payment methods must follow.
- **Key Methods:** `virtual bool pay(double amount) = 0`

### 13. `UpiPayment` / `CardPayment` / `CashPayment`
*The Implementations.*
- **Responsibilities:** Concrete classes executing the `pay()` function based on their specific logic (e.g., verifying a UPI ID or validating a Card Number).

---

### Next Steps in Design
We now have a complete, strict dictionary of our classes. To communicate this blueprint universally to other engineers, we visually render it as a **[UML Class Diagram](../UML-Diagram/uml-class-diagram.md)**.
