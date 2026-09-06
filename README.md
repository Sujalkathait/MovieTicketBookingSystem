# Movie Ticket Booking System

https://github.com/Sujalkathait/MovieTicketBookingSystem/raw/main/MovieTicketBookingSystem%20video/project%20demo.mp4
## 1. What is this Project?
Welcome to the Movie Ticket Booking System! This is an in-memory Console Application built in C++ that simulates a real-world cinema booking experience. It demonstrates Low-Level Design (LLD) principles, Object-Oriented Programming (OOP), and clean architecture by breaking down a complex system into manageable classes and services.

---

## 2. What does it do?
With this application, you can perform all the core functions of a movie theater:
- **Browse Movies:** View a list of all currently playing movies and their details (language, duration).
- **Select Shows:** Pick a specific screen and time for your chosen movie.
- **Pick Seats:** View a live, formatted seating chart (Silver, Gold, Platinum) and select available seats.
- **Pay:** Process payments securely via simulated UPI, Card, or Cash methods.
- **Get a Ticket:** Receive a fully formatted ticket receipt containing your unique Booking ID, customer details, and seat numbers.
- **Cancel Tickets:** Look up an existing booking and cancel it to automatically release the seats back to the public and issue a refund.
- **Search Tickets:** Retrieve past bookings at any time using your phone number or unique Booking ID.

---

## 3. Project Files Explained
The code is broken down into small, modular files to ensure it is easy to read and maintain. Each file has a single responsibility:
- `main1.cpp`: The entry point. It initializes the cinema, screens, seats, movies, and starts the main menu.
- `movie2.cpp`: Defines the `Movie` class (stores title, language, duration).
- `seat3.cpp` & `screen4.cpp`: Manages the physical layout of the cinema, including seat numbers and categories (Silver, Gold, Platinum).
- `cinema5.cpp`, `showSeat6.cpp`, `show7.cpp`: Connects movies to screens at specific times and tracks the real-time availability of individual seats.
- `priceCalculator8.cpp`: Dynamically calculates the total price based on the category of the selected seats.
- `bookingService9.cpp`: The brain of the application. It handles the entire booking flow, manages the list of all tickets, processes cancellations, and handles user input.
- `customer10.cpp`: Stores the customer's personal details (Name and Phone Number).
- `payment11.cpp` to `cashPayment14.cpp`: Implements a polymorphic payment system that handles UPI, Card, and Cash transactions.

---

## 4. How to Run the Code

To run this program, open your terminal (e.g., inside VS Code) in the `MovieTicketBookingSystem/` folder and compile the code using `g++`:

```bash
g++ main1.cpp -o MovieTicketBooking
```

Once compiled, you can start the program from the terminal based on your operating system:

**On Windows:**
```powershell
.\MovieTicketBooking.exe
```

**On MacOS / Linux:**
```bash
./MovieTicketBooking
```

---

## 5. Error Handling
The application is robust and designed to prevent crashes from bad user input:
- **Invalid Inputs:** If you accidentally type letters instead of numbers in menus, the system safely catches the error, clears the input buffer, and asks you again without crashing.
- **Invalid Booking IDs:** If you try to look up or cancel a booking that doesn't exist (or was already cancelled), the system will notify you safely.
- **Seat Validation:** The system prevents you from booking a seat that doesn't exist, booking a seat that is already taken, or entering duplicate seats in the same transaction.
- **Payment Failures:** If you abort the payment process halfway through, the transaction is rolled back and your selected seats are immediately freed up for other users.

---

## 6. System Diagrams

### 6.1 End-to-End System Workflow
This flowchart shows how a user interacts with the system from start to finish.

```mermaid
flowchart TD
    Start([User Starts System]) --> Menu[Main Menu]

    Menu --> M1{Select Option}

    M1 -->|1 - Movies| ShowMovies["Show Available Movies & Shows"]
    ShowMovies --> Menu

    M1 -->|2 - Book Ticket| SelectMovie["Select Movie & Show"]
    SelectMovie --> Layout["Show Live Seat Layout"]

    Layout --> PickSeats["Enter Seats (e.g., A1, B2)"]
    PickSeats --> Validate{"Are Seats Valid & Available?"}

    Validate -->|No| ShowError["Show Seat Error"]
    ShowError --> Layout

    Validate -->|Yes| CalcPrice["Calculate Ticket Price"]

    CalcPrice --> CustInfo["Enter Customer Details (Name & Phone)"]
    CustInfo --> SelectPay["Select Payment Method"]

    SelectPay --> PayMode{Payment Method}

    PayMode -->|1 - UPI| UPIPay["Process UPI Payment"]
    PayMode -->|2 - Card| CardPay["Process Card Payment"]
    PayMode -->|3 - Cash| CashPay["Process Cash Payment"]
    PayMode -->|0 - Decline| Rollback["Cancel and Free Selected Seats"]

    UPIPay --> PayCheck{"Payment Successful?"}
    CardPay --> PayCheck
    CashPay --> PayCheck

    PayCheck -->|No| Rollback
    PayCheck -->|Yes| Confirm["Confirm Booking and Mark Seats as BOOKED"]

    Confirm --> GenTicket["Create Booking ID (e.g., BK1001)"]
    GenTicket --> PrintTicket[Print Ticket]
    PrintTicket --> Menu

    Rollback --> Menu

    M1 -->|3 - Cancel Ticket| CancelPrompt["Enter Booking ID"]
    CancelPrompt --> FindBooking{"Is Booking Found?"}

    FindBooking -->|No| CancelErr["Show Booking Not Found Error"]
    CancelErr --> Menu

    FindBooking -->|Yes| ConfirmCancel{"Confirm Cancellation?"}

    ConfirmCancel -->|No| Abort["Stop Cancellation"]
    Abort --> Menu

    ConfirmCancel -->|Yes| CancelBooking["Cancel Booking"]
    CancelBooking --> Refund["Issue Full Refund"]
    Refund --> Release["Free Seats and Update Status to CANCELLED"]
    Release --> Menu

    M1 -->|4 - My Tickets| Lookup["Enter Booking ID or Phone Number"]
    Lookup --> Search{"Is Booking Found?"}

    Search -->|Yes| ShowTicket[Show Ticket]
    ShowTicket --> Menu

    Search -->|No| NotFound[Show: No Tickets Found]
    NotFound --> Menu

    M1 -->|0 - Exit| ExitApp([Exit App])
```

### 6.2 UPI Payment Sequence Diagram
This image shows the interaction logic when a customer pays using UPI.

![Cinema Booking UPI Sequence Diagram](MovieTicketBookingSystem%20image/Cinema_Booking_UPI_Sequence_Diagram.png)

### 6.3 System Architecture
This image outlines the object-oriented architectural relationships in the codebase.

![Architecture Sequence Diagram](MovieTicketBookingSystem%20image/squence%20diagram.png)
