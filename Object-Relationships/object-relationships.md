# Object Identification
From the noun-verb analysis, we identify the core objects that will persist in our system. We separate physical entities (Movie, Screen, Seat) from transactional entities (Booking, Payment) and operational services (BookingService, PriceCalculator).

# Object Relationships
Once objects are identified, we define how they relate to one another logically. 

**Relationships Used:**
- `◆──` = Composition (Strong dependency)
- `◇──` = Aggregation (Weak dependency)
- `──` = Association (General relationship)
- `▲` = Generalization / Inheritance (IS-A relationship)

**Key Mappings:**
- Cinema ◆── Screen
- Screen ◆── Seat
- Show ◇── Movie
- Show ◇── Screen
- Show ◆── ShowSeat
- ShowSeat ── Seat
- Booking ── Customer
- Booking ── Show
- Booking ── Seat
- Booking ── Payment

**Payment Hierarchy:**
```text
Payment
   ▲
   ├── UpiPayment
   ├── CardPayment
   └── CashPayment
```
