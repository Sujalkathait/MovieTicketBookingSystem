# Noun-Verb Analysis

Noun-Verb Analysis (often attributed to Abbott's Textual Analysis technique) is a linguistic approach used in Object-Oriented Design to bridge the gap between plain English requirements and technical software design. 

By analyzing the requirements document, we can extract **Nouns** to serve as candidate Classes or Attributes, and **Verbs** to serve as candidate Methods or Responsibilities.

---

## 1. Noun Extraction (Identifying Objects & Attributes)

We scan the functional requirements and extract all relevant nouns. We then filter these nouns to decide if they represent a major entity (Class) or simply a property of an entity (Attribute).

| Extracted Noun | Classification | Reasoning / Role in System |
|---|---|---|
| **Cinema** | `Class` | The top-level container holding screens and movies. |
| **Movie** | `Class` | Represents the film being shown. |
| **Screen** | `Class` | Represents a physical auditorium hall. |
| **Show** | `Class` | A specific screening of a Movie in a Screen at a specific time. |
| **Seat** | `Class` | The physical chair in a Screen. |
| **ShowSeat** | `Class` | The *status* (booked/available) of a Seat for a specific Show. |
| **Customer** | `Class` | The person making the booking. |
| **Booking** | `Class` | The transactional record of the purchase. |
| **Ticket** | `Class` | The final output receipt. |
| **Payment** | `Class` (Abstract) | The generic transaction. |
| **UPI, Card, Cash** | `Class` (Concrete) | Specific types of Payments. |
| **Price** | `Attribute` | A property belonging to a Booking or a Seat type. |
| **Name, Phone** | `Attribute` | Properties belonging to a Customer. |

### System / Service Nouns
Some nouns represent operational logic rather than physical objects. These become our "Service" or "Manager" classes.
- **System** → `BookingService` (Orchestrates the workflow)
- **Calculator** → `PriceCalculator` (Handles financial logic)
- **Printer** → `TicketPrinter` (Handles output formatting)

---

## 2. Verb Extraction (Identifying Methods & Responsibilities)

Next, we extract the verbs from the requirements. These verbs define the behavior of our classes. We must assign each verb to the appropriate class responsible for executing it.

| Extracted Verb | Assigned To Class | Resulting Method Signature |
|---|---|---|
| **view (movies)** | `Cinema` / `BookingService` | `getMovies()`, `displayShows()` |
| **select (show/seat)**| `BookingService` | Handled via UI input selection logic. |
| **check (availability)**| `ShowSeat` | `bool isAvailable()` |
| **book (seat)** | `ShowSeat` | `void book()` |
| **calculate (price)** | `PriceCalculator` | `double calculatePrice(vector<ShowSeat> seats)` |
| **process / pay** | `Payment` (and subclasses)| `bool pay(double amount)` |
| **create (booking)** | `BookingService` | Instantiates `new Booking(...)` |
| **print (ticket)** | `TicketPrinter` | `void printTicket(Booking b)` |

---

## 3. Practical Example

Let's look at a specific requirement sentence:
> *"The **System** **calculates** the ticket **price** based on the selected **seats**."*

- **System**: Refined into a specialized service (`PriceCalculator`).
- **calculates**: The method/action (`calculatePrice()`).
- **price**: The return type (`double`).
- **seats**: The input parameters (`vector<ShowSeat>`).

### Final Method Mapping:
```cpp
// Inside PriceCalculator class
double calculatePrice(std::vector<ShowSeat> selectedSeats);
```

---

### Next Steps in Design
Now that we have candidate classes (Nouns) and candidate methods (Verbs), we must define how these classes interact and contain one another. This is done through **[Object Relationships](../Object-Relationships/object-relationships.md)**.
