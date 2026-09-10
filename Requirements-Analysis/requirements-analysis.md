# Requirements Analysis

Requirements Analysis is the foundational phase of the software development lifecycle (SDLC). Before writing a single line of code, we must clearly define what the system is expected to achieve. This step ensures that the final software perfectly aligns with business needs and user expectations.

In the context of the **Cinema Booking System**, our requirements are broken down into **Functional** and **Non-Functional** requirements.

---

## 1. Functional Requirements

Functional requirements describe the specific behaviors and functions the system must support. These define *what* the system does.

### Core User Journey
The system must support the complete lifecycle of a ticket booking process:
1. **System Access**: The customer must be able to interact with the application interface.
2. **Browsing**: The customer can view a list of all currently screening movies.
3. **Show Selection**: The customer selects a movie, followed by a specific showtime and screen.
4. **Seat Selection**: The system displays all available seats for the selected show. The customer can select one or more seats.
5. **Validation**: The system must verify that the selected seats are not already booked.
6. **Pricing Calculation**: The system dynamically calculates the total cost based on the number of seats and their respective tiers (e.g., Gold, Silver).
7. **Payment Selection**: The customer chooses a preferred payment method.
8. **Transaction Processing**: The system processes the payment securely.
9. **Booking Confirmation**: Upon successful payment, a unique Booking ID is generated.
10. **Ticket Generation**: A final digital ticket is printed/displayed to the customer.

### Payment Requirements
The payment subsystem must be flexible and decoupled from the main booking logic. It must actively support:
- **UPI Payments** (Unified Payments Interface)
- **Credit/Debit Card Payments**
- **Cash Payments** (Over-the-counter simulation)

---

## 2. Non-Functional Requirements

Non-functional requirements specify the criteria that can be used to judge the operation of a system, rather than specific behaviors. They define *how* the system performs.

1. **In-Memory Storage**: For the scope of this project, the system will not use an external database. All data (Movies, Screens, Bookings) must be managed in memory using C++ Standard Template Library (STL) containers (e.g., `std::vector`, `std::map`).
2. **Extensibility**: The architecture must easily support adding new features, such as new payment methods or seat types, without modifying existing core logic (Open/Closed Principle).
3. **Robustness**: The system must handle edge cases gracefully, such as:
   - Attempting to book a seat that has already been booked.
   - Processing a payment that fails or is insufficient.
4. **Console UI**: The user interface will be entirely text-based via standard input/output streams (`std::cin` / `std::cout`).

---

## 3. Scope and Limitations
- The system assumes a single-threaded environment (concurrency and race conditions like two users booking the exact same seat at the exact same millisecond are out of scope for this LLD simulation).
- Persistence is not required; data is lost when the application terminates.

---

### Next Steps in Design
Once the requirements are finalized, the next immediate step is to parse this plain English text to identify candidate software objects using **[Noun-Verb Analysis](../Noun-Verb-Analysis/noun-verb-analysis.md)**.
