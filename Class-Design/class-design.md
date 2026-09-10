# Class Design
The objects and relationships identified earlier are transformed into software classes.

- **Cinema**: Central hub. Holds screens and movies.
- **Screen**: Represents a physical hall. Contains Seats.
- **Seat**: Represents physical placement (e.g., A1) and tier (Gold/Silver).
- **Show**: Links a Movie and Screen at a specific time. Contains ShowSeats.
- **ShowSeat**: Tracks runtime availability (Booked/Available) of a Seat for a Show.
- **Booking**: The transaction record holding Customer, Show, Seats, and Payment.
- **BookingService**: The orchestrator of the entire booking logic.
- **PriceCalculator**: Computes final costs.
- **Payment**: Abstract interface handling transactions.
- **TicketPrinter**: Outputs the final receipt.
