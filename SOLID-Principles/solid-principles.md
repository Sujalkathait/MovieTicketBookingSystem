# SOLID Principles
SOLID principles improve the maintainability and scalability of our Class Design.

## Single Responsibility
A class should have one, and only one, reason to change.
- `BookingService` → Manages the booking workflow.
- `PriceCalculator` → Handles price calculation based on seat tiers.
- `TicketPrinter` → Formats and prints the final ticket.

## Open/Closed
Classes should be open for extension but closed for modification. We can add a new payment method (e.g., `WalletPayment`) by implementing the `Payment` interface without modifying the existing `BookingService`.

## Liskov Substitution
Subclasses should be substitutable for their base classes. Any part of the system expecting a `Payment` object functions perfectly whether it receives a `UpiPayment` or a `CashPayment`.

## Interface Segregation
Clients should not be forced to depend on interfaces they do not use. Our system ensures simple, focused interfaces rather than bloated master classes.

## Dependency Inversion
High-level modules should not depend on low-level modules; both should depend on abstractions. `BookingService` depends on the abstract `Payment` interface, not the concrete `UpiPayment` class.
