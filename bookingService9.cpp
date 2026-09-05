#ifndef BOOKINGSERVICE9_CPP
#define BOOKINGSERVICE9_CPP

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

#include "movie2.cpp"
#include "cinema5.cpp"
#include "show7.cpp"
#include "priceCalculator8.cpp"
#include "customer10.cpp"
#include "payment11.cpp"
#include "upiPayment12.cpp"
#include "cardPayment13.cpp"
#include "cashPayment14.cpp"

// Class: Booking
// Responsibility: Stores booking and ticket information

enum class BookingStatus
{
    CONFIRMED,
    CANCELLED
};

class Booking
{
private:
    std::string bookingId;
    Customer customer;
    std::string movieTitle;
    std::string screenName;
    std::string showTime;
    std::vector<std::string> seatCodes;
    std::vector<ShowSeat*> bookedSeats;
    double totalAmount;
    std::string paymentMode;
    BookingStatus status;

public:

    // Constructor
    Booking(
        const std::string& id,
        const Customer& customer,
        const std::string& movieTitle,
        const std::string& screenName,
        const std::string& showTime,
        const std::vector<std::string>& seatCodes,
        const std::vector<ShowSeat*>& bookedSeats,
        double totalAmount,
        const std::string& paymentMode
    )
        : bookingId(id),
          customer(customer),
          movieTitle(movieTitle),
          screenName(screenName),
          showTime(showTime),
          seatCodes(seatCodes),
          bookedSeats(bookedSeats),
          totalAmount(totalAmount),
          paymentMode(paymentMode),
          status(BookingStatus::CONFIRMED)
    {
    }

    // Getters
    const std::string& getBookingId() const
    {
        return bookingId;
    }

    const Customer& getCustomer() const
    {
        return customer;
    }

    const std::string& getMovieTitle() const
    {
        return movieTitle;
    }

    const std::string& getScreenName() const
    {
        return screenName;
    }

    const std::string& getShowTime() const
    {
        return showTime;
    }

    const std::vector<std::string>& getSeatCodes() const
    {
        return seatCodes;
    }

    double getTotalAmount() const
    {
        return totalAmount;
    }

    const std::string& getPaymentMode() const
    {
        return paymentMode;
    }

    BookingStatus getStatus() const
    {
        return status;
    }

    bool isConfirmed() const
    {
        return status == BookingStatus::CONFIRMED;
    }

    // Cancel booking and release seats
    bool cancel()
    {
        if (status == BookingStatus::CANCELLED)
        {
            return false;
        }

        for (ShowSeat* seat : bookedSeats)
        {
            if (seat != nullptr)
            {
                seat->releaseSeat();
            }
        }

        status = BookingStatus::CANCELLED;
        return true;
    }

    // Display ticket
    void printTicket() const
    {
        std::cout << "\n========== TICKET ==========\n";
        std::cout << "Booking ID : " << bookingId << "\n";
        std::cout << "Customer   : " << customer.getCustomerName() << "\n";
        std::cout << "Phone      : " << customer.getPhoneNumber() << "\n";
        std::cout << "Movie      : " << movieTitle << "\n";
        std::cout << "Screen     : " << screenName << "\n";
        std::cout << "Show Time  : " << showTime << "\n";

        std::cout << "Seats      : ";

        for (size_t i = 0; i < seatCodes.size(); i++)
        {
            std::cout << seatCodes[i];

            if (i + 1 < seatCodes.size())
            {
                std::cout << ", ";
            }
        }

        std::cout << "\n";
        std::cout << "Amount     : Rs." << static_cast<int>(totalAmount) << "\n";
        std::cout << "Payment    : " << paymentMode << "\n";
        std::cout << "Status     : "
                  << (isConfirmed() ? "CONFIRMED" : "CANCELLED")
                  << "\n";
        std::cout << "============================\n\n";
    }
};


// Class: BookingService
// Responsibility: Manages movie booking, payment, tickets and cancellation

class BookingService
{
private:
    std::vector<Movie> movies;
    std::vector<Show> shows;
    std::vector<Booking> bookings;

    PriceCalculator priceCalculator;

    int bookingSequence;

public:

    // Constructor
    BookingService()
        : bookingSequence(1001)
    {
    }

    // Add movie
    void addMovie(const Movie& movie)
    {
        movies.push_back(movie);
    }

    // Add show
    void addShow(const Show& show)
    {
        shows.push_back(show);
    }

    // Generate booking ID
    std::string generateBookingId()
    {
        return "BK" + std::to_string(bookingSequence++);
    }

    // Display main menu
    void displayMainMenu() const
    {
        std::cout << "\n===== MOVIE TICKET BOOKING =====\n";
        std::cout << "1. Movies\n";
        std::cout << "2. Book Ticket\n";
        std::cout << "3. Cancel Ticket\n";
        std::cout << "4. My Tickets\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose: ";
    }

    // Display movies
    void displayMovies() const
    {
        std::cout << "\n===== MOVIES =====\n";

        for (size_t i = 0; i < movies.size(); i++)
        {
            std::cout << i + 1 << ". "
                      << movies[i].getTitle()
                      << " | "
                      << movies[i].getLanguage()
                      << " | "
                      << movies[i].getDurationInMinutes()
                      << " min\n";
        }

        std::cout << "\n";
    }

    // Find shows for a movie
    std::vector<size_t> getShowsForMovie(
        const std::string& movieTitle
    ) const
    {
        std::vector<size_t> result;

        for (size_t i = 0; i < shows.size(); i++)
        {
            if (shows[i].getMovie().getTitle() == movieTitle)
            {
                result.push_back(i);
            }
        }

        return result;
    }

    // Display shows
    void displayShows(const std::vector<size_t>& showIndices) const
    {
        std::cout << "\n===== SHOWS =====\n";

        for (size_t i = 0; i < showIndices.size(); i++)
        {
            const Show& show = shows[showIndices[i]];

            std::cout << i + 1 << ". "
                      << show.getScreen().getScreenName()
                      << " | "
                      << show.getShowTime()
                      << "\n";
        }

        std::cout << "\n";
    }

    // Convert input like "A1, B2" into seat numbers
    std::vector<std::string> parseSeatInput(
        const std::string& input
    ) const
    {
        std::vector<std::string> seats;
        std::stringstream ss(input);
        std::string seat;

        while (std::getline(ss, seat, ','))
        {
            size_t start = seat.find_first_not_of(" \t");
            size_t end = seat.find_last_not_of(" \t");

            if (start != std::string::npos)
            {
                seat = seat.substr(start, end - start + 1);

                for (char& ch : seat)
                {
                    ch = static_cast<char>(
                        std::toupper(
                            static_cast<unsigned char>(ch)
                        )
                    );
                }

                seats.push_back(seat);
            }
        }

        return seats;
    }

    // Process payment
    bool processPayment(
        Payment& payment,
        double amount
    )
    {
        return payment.pay(amount);
    }

    // Book tickets
    void bookTickets(Show& show)
    {
        std::cout << "Enter seats (e.g. A1,B2): ";

        std::string input;
        std::getline(std::cin >> std::ws, input);

        std::vector<std::string> seatNumbers =
            parseSeatInput(input);

        if (seatNumbers.empty())
        {
            std::cout << "No seats entered.\n";
            return;
        }

        std::vector<ShowSeat*> selectedSeats;

        // Check seats
        for (const std::string& number : seatNumbers)
        {
            ShowSeat* seat = show.findSeat(number);

            if (seat == nullptr)
            {
                std::cout << "Seat " << number
                          << " does not exist.\n";
                return;
            }

            if (!seat->isAvailable())
            {
                std::cout << "Seat " << number
                          << " is already booked.\n";
                return;
            }

            for (ShowSeat* selected : selectedSeats)
            {
                if (selected == seat)
                {
                    std::cout << "Duplicate seat "
                              << number << ".\n";
                    return;
                }
            }

            selectedSeats.push_back(seat);
        }

        // Display seat prices
        std::cout << "\n===== SEAT PRICES =====\n";

        for (ShowSeat* seat : selectedSeats)
        {
            std::cout << seat->getSeat().getSeatNumber()
                      << " - "
                      << seat->getSeat().getSeatType()
                      << " - Rs."
                      << static_cast<int>(
                             priceCalculator.calculateSeatPrice(*seat)
                         )
                      << "\n";
        }

        double totalAmount =
            priceCalculator.calculateTotalPrice(selectedSeats);

        std::cout << "Total: Rs."
                  << static_cast<int>(totalAmount)
                  << "\n\n";

        // Customer details
        std::string customerName;
        std::string customerPhone;

        std::cout << "Enter Customer Name: ";
        std::getline(std::cin >> std::ws, customerName);

        std::cout << "Enter Phone Number: ";
        std::getline(std::cin >> std::ws, customerPhone);

        Customer customer(customerName, customerPhone);

        // Payment
        std::cout << "\n1. UPI\n";
        std::cout << "2. Card\n";
        std::cout << "3. Cash\n";
        std::cout << "0. Cancel\n";
        std::cout << "Choose Payment: ";

        int choice;
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); choice = -1; }

        bool paymentSuccess = false;
        std::string paymentMode;

        if (choice == 1)
        {
            UpiPayment payment("user@upi");
            paymentSuccess =
                processPayment(payment, totalAmount);

            paymentMode = payment.getPaymentType();
        }
        else if (choice == 2)
        {
            CardPayment payment(
                "4532123456789012",
                "12/28"
            );

            paymentSuccess =
                processPayment(payment, totalAmount);

            paymentMode = payment.getPaymentType();
        }
        else if (choice == 3)
        {
            CashPayment payment;

            paymentSuccess =
                processPayment(payment, totalAmount);

            paymentMode = payment.getPaymentType();
        }

        // Payment failed
        if (!paymentSuccess)
        {
            std::cout << "\nPayment failed.\n";
            std::cout << "Seats are still available.\n";
            return;
        }

        // Book seats
        for (ShowSeat* seat : selectedSeats)
        {
            seat->bookSeat();
        }

        // Create booking
        std::string bookingId =
            generateBookingId();

        Booking booking(
            bookingId,
            customer,
            show.getMovie().getTitle(),
            show.getScreen().getScreenName(),
            show.getShowTime(),
            seatNumbers,
            selectedSeats,
            totalAmount,
            paymentMode
        );

        bookings.push_back(booking);

        std::cout << "\nBooking successful!\n";

        bookings.back().printTicket();
    }

    // Cancel booking
    void cancelBooking()
    {
        std::cout << "\nEnter Booking ID: ";

        std::string id;
        std::cin >> id;

        for (Booking& booking : bookings)
        {
            if (booking.getBookingId() == id)
            {
                if (!booking.isConfirmed())
                {
                    std::cout << "Booking already cancelled.\n";
                    return;
                }

                std::cout << "\n";
                booking.printTicket();

                std::cout << " Are you sure you want to cancel this booking? (y/n): ";

                char choice;
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); choice = -1; }

                if (choice == 'y' || choice == 'Y')
                {
                    booking.cancel();

                    std::cout << "Booking cancelled.\n";
                    std::cout << "Rs."
                              << static_cast<int>(
                                     booking.getTotalAmount()
                                 )
                              << " refunded.\n";
                }

                return;
            }
        }

        std::cout << "Booking not found.\n";
    }

    // Find tickets
    void findBooking()
    {
        std::cout << "\nEnter Booking ID or Phone Number: ";

        std::string query;
        std::cin >> query;

        bool flag = false;

        for (const Booking& booking : bookings)
        {
            if (booking.getBookingId() == query ||
                booking.getCustomer().getPhoneNumber() == query)
            {
                booking.printTicket();
                flag = true;
            }
        }

        if (!flag)
        {
            std::cout << "No tickets found.\n";
        }
    }

    // Handle booking process
    void handleBookingFlow()
    {
        if (movies.empty())
        {
            std::cout << "No movies available.\n";
            return;
        }

        displayMovies();

        std::cout << "Choose movie: ";

        int movieChoice;
        if (!(std::cin >> movieChoice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); movieChoice = -1; }

        if (movieChoice < 1 ||
            movieChoice > static_cast<int>(movies.size()))
        {
            std::cout << "Invalid movie selection.\n";
            return;
        }

        const Movie& movie =
            movies[movieChoice - 1];

        std::vector<size_t> showIndices =
            getShowsForMovie(movie.getTitle());

        if (showIndices.empty())
        {
            std::cout << "No shows available.\n";
            return;
        }

        displayShows(showIndices);

        std::cout << "Choose show: ";

        int showChoice;
        if (!(std::cin >> showChoice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); showChoice = -1; }

        if (showChoice < 1 ||
            showChoice > static_cast<int>(showIndices.size()))
        {
            std::cout << "Invalid show selection.\n";
            return;
        }

        Show& show =
            shows[showIndices[showChoice - 1]];

        show.displaySeatLayout();

        bookTickets(show);
    }

    // Start application
    void start()
    {
        int choice;

        do
        {
            displayMainMenu();
        if (!(std::cin >> choice)) { std::cin.clear(); std::cin.ignore(10000, '\n'); choice = -1; }

            switch (choice)
            {
                case 1:
                case 2:
                    handleBookingFlow();
                    break;

                case 3:
                    cancelBooking();
                    break;

                case 4:
                    findBooking();
                    break;

                case 0:
                    std::cout << "\nThank you\n";
                    break;

                default:
                    std::cout << "Invalid choice.\n";
            }

        } while (choice != 0);
    }
};

#endif
