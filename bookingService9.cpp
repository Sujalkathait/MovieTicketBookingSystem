
#ifndef BOOKINGSERVICE9_CPP
#define BOOKINGSERVICE9_CPP

#include <cctype>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "cardPayment13.cpp"
#include "cashPayment14.cpp"
#include "cinema5.cpp"
#include "customer10.cpp"
#include "movie2.cpp"
#include "payment11.cpp"
#include "priceCalculator8.cpp"
#include "show7.cpp"
#include "upiPayment12.cpp"


// ============================================================================
// Class: Booking
// Responsibility: Stores booking and ticket information
// ============================================================================

enum class BookingStatus { CONFIRMED, CANCELLED };

class Booking {
private:
  std::string bookingId;
  Customer customer;
  std::string movieTitle;
  std::string screenName;
  std::string showTime;
  std::vector<std::string> seatCodes;
  std::vector<ShowSeat *> bookedSeats;
  double totalAmount;
  std::string paymentMode;
  BookingStatus status;

public:
  // Constructor
  Booking(const std::string &id, const Customer &customer,
          const std::string &movieTitle, const std::string &screenName,
          const std::string &showTime,
          const std::vector<std::string> &seatCodes,
          const std::vector<ShowSeat *> &bookedSeats, double totalAmount,
          const std::string &paymentMode)
      : bookingId(id), customer(customer), movieTitle(movieTitle),
        screenName(screenName), showTime(showTime), seatCodes(seatCodes),
        bookedSeats(bookedSeats), totalAmount(totalAmount),
        paymentMode(paymentMode), status(BookingStatus::CONFIRMED) {}

  // Get booking ID
  const std::string &getBookingId() const { return bookingId; }

  // Get customer details
  const Customer &getCustomer() const { return customer; }

  // Get total booking amount
  double getTotalAmount() const { return totalAmount; }

  // Check booking status
  bool isConfirmed() const { return status == BookingStatus::CONFIRMED; }

  // Cancel booking and release seats
  bool cancel() {
    if (!isConfirmed())
      return false;

    for (ShowSeat *seat : bookedSeats) {
      if (seat)
        seat->releaseSeat();
    }

    status = BookingStatus::CANCELLED;
    return true;
  }

  // Display ticket
  void printTicket() const {
    std::cout << "\n========== TICKET ==========\n";
    std::cout << "Booking ID : " << bookingId << "\n";
    std::cout << "Customer   : " << customer.getCustomerName() << "\n";
    std::cout << "Phone      : " << customer.getPhoneNumber() << "\n";
    std::cout << "Movie      : " << movieTitle << "\n";
    std::cout << "Screen     : " << screenName << "\n";
    std::cout << "Show Time  : " << showTime << "\n";

    std::cout << "Seats      : ";

    for (size_t i = 0; i < seatCodes.size(); i++) {
      std::cout << seatCodes[i];

      if (i + 1 < seatCodes.size())
        std::cout << ", ";
    }

    std::cout << "\n";
    std::cout << "Amount     : Rs." << static_cast<int>(totalAmount) << "\n";
    std::cout << "Payment    : " << paymentMode << "\n";
    std::cout << "Status     : " << (isConfirmed() ? "CONFIRMED" : "CANCELLED")
              << "\n";
    std::cout << "============================\n\n";
  }
};

// ============================================================================
// Class: BookingService
// Responsibility: Manages movie booking, payment, tickets and cancellation
// ============================================================================

class BookingService {
private:
  std::vector<Movie> movies;
  std::vector<Show> shows;
  std::vector<Booking> bookings;

  PriceCalculator priceCalculator;
  int bookingSequence = 1001;

public:
  // Add movie to the system
  void addMovie(const Movie &movie) { movies.push_back(movie); }

  // Add show to the system
  void addShow(const Show &show) { shows.push_back(show); }

  // Generate unique booking ID
  std::string generateBookingId() {
    return "BK" + std::to_string(bookingSequence++);
  }

  // Display main menu
  void displayMainMenu() const {
    std::cout << "\n===== MOVIE TICKET BOOKING =====\n";
    std::cout << "1. Movies\n";
    std::cout << "2. Book Ticket\n";
    std::cout << "3. Cancel Ticket\n";
    std::cout << "4. My Tickets\n";
    std::cout << "0. Exit\n";
    std::cout << "Choose: ";
  }

  // Display available movies
  void displayMovies() const {
    std::cout << "\n===== MOVIES =====\n";

    for (size_t i = 0; i < movies.size(); i++) {
      std::cout << i + 1 << ". " << movies[i].getTitle() << " | "
                << movies[i].getLanguage() << " | "
                << movies[i].getDurationInMinutes() << " min\n";
    }
  }

  // Find shows for a selected movie
  std::vector<size_t> getShowsForMovie(const std::string &movieTitle) const {

    std::vector<size_t> result;

    for (size_t i = 0; i < shows.size(); i++) {
      if (shows[i].getMovie().getTitle() == movieTitle)
        result.push_back(i);
    }

    return result;
  }

  // Display available shows
  void displayShows(const std::vector<size_t> &showIndices) const {

    std::cout << "\n===== SHOWS =====\n";

    for (size_t i = 0; i < showIndices.size(); i++) {
      const Show &show = shows[showIndices[i]];

      std::cout << i + 1 << ". " << show.getScreen().getScreenName() << " | "
                << show.getShowTime() << "\n";
    }
  }

  // Convert seat input into standard format
  std::vector<std::string> parseSeatInput(const std::string &input) const {

    std::vector<std::string> seats;
    std::stringstream ss(input);
    std::string seat;

    while (std::getline(ss, seat, ',')) {
      size_t start = seat.find_first_not_of(" \t");
      size_t end = seat.find_last_not_of(" \t");

      if (start == std::string::npos)
        continue;

      seat = seat.substr(start, end - start + 1);

      for (char &ch : seat) {
        ch = static_cast<char>(std::toupper(static_cast<unsigned char>(ch)));
      }

      seats.push_back(seat);
    }

    return seats;
  }

  // Process selected payment
  bool processPayment(Payment &payment, double amount) {

    return payment.pay(amount);
  }

  // Book selected seats
  void bookTickets(Show &show) {

    std::cout << "\nEnter seats (e.g. A1,B2): ";

    std::string input;
    std::getline(std::cin >> std::ws, input);

    std::vector<std::string> seatNumbers = parseSeatInput(input);

    if (seatNumbers.empty()) {
      std::cout << "No seats entered.\n";
      return;
    }

    std::vector<ShowSeat *> selectedSeats;

    // Validate selected seats
    for (const std::string &number : seatNumbers) {

      ShowSeat *seat = show.findSeat(number);

      if (!seat) {
        std::cout << "Seat " << number << " does not exist.\n";
        return;
      }

      if (!seat->isAvailable()) {
        std::cout << "Seat " << number << " is already booked.\n";
        return;
      }

      for (ShowSeat *selected : selectedSeats) {
        if (selected == seat) {
          std::cout << "Duplicate seat " << number << ".\n";
          return;
        }
      }

      selectedSeats.push_back(seat);
    }

    // Display seat prices
    std::cout << "\n===== SEAT PRICES =====\n";

    for (ShowSeat *seat : selectedSeats) {
      std::cout << seat->getSeat().getSeatNumber() << " - "
                << seat->getSeat().getSeatType() << " - Rs."
                << static_cast<int>(priceCalculator.calculateSeatPrice(*seat))
                << "\n";
    }

    // Calculate total price
    double totalAmount = priceCalculator.calculateTotalPrice(selectedSeats);

    std::cout << "Total: Rs." << static_cast<int>(totalAmount) << "\n\n";

    // Enter customer details
    std::string name;
    std::string phone;

    std::cout << "Enter Customer Name: ";
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter Phone Number: ";
    std::getline(std::cin >> std::ws, phone);

    Customer customer(name, phone);

    // Select payment method
    std::cout << "\n1. UPI\n";
    std::cout << "2. Card\n";
    std::cout << "3. Cash\n";
    std::cout << "0. Cancel\n";
    std::cout << "Choose Payment: ";

    int choice;

    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid payment selection.\n";
      return;
    }

    bool paymentSuccess = false;
    std::string paymentMode;

    if (choice == 1) {

      UpiPayment payment("user@upi");
      paymentSuccess = processPayment(payment, totalAmount);

      paymentMode = payment.getPaymentType();

    } else if (choice == 2) {

      CardPayment payment("4532123456789012", "12/28");

      paymentSuccess = processPayment(payment, totalAmount);

      paymentMode = payment.getPaymentType();

    } else if (choice == 3) {

      CashPayment payment;

      paymentSuccess = processPayment(payment, totalAmount);

      paymentMode = payment.getPaymentType();

    } else if (choice == 0) {

      std::cout << "Payment cancelled.\n";
      return;

    } else {

      std::cout << "Invalid payment selection.\n";
      return;
    }

    // Check payment result
    if (!paymentSuccess) {
      std::cout << "Payment failed.\n";
      return;
    }

    // Mark seats as booked
    for (ShowSeat *seat : selectedSeats)
      seat->bookSeat();

    // Create booking
    Booking booking(generateBookingId(), customer, show.getMovie().getTitle(),
                    show.getScreen().getScreenName(), show.getShowTime(),
                    seatNumbers, selectedSeats, totalAmount, paymentMode);

    // Store booking permanently
    bookings.push_back(booking);

    std::cout << "\nBooking successful!\n";

    bookings.back().printTicket();
  }

  // Start ticket booking process
  void handleBookingFlow() {

    if (movies.empty()) {
      std::cout << "No movies available.\n";
      return;
    }

    displayMovies();

    std::cout << "\nChoose movie: ";

    int movieChoice;

    if (!(std::cin >> movieChoice)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid movie selection.\n";
      return;
    }

    if (movieChoice < 1 || movieChoice > static_cast<int>(movies.size())) {

      std::cout << "Invalid movie selection.\n";
      return;
    }

    const Movie &movie = movies[movieChoice - 1];

    std::vector<size_t> showIndices = getShowsForMovie(movie.getTitle());

    if (showIndices.empty()) {
      std::cout << "No shows available.\n";
      return;
    }

    displayShows(showIndices);

    std::cout << "\nChoose show: ";

    int showChoice;

    if (!(std::cin >> showChoice)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid show selection.\n";
      return;
    }

    if (showChoice < 1 || showChoice > static_cast<int>(showIndices.size())) {

      std::cout << "Invalid show selection.\n";
      return;
    }

    Show &show = shows[showIndices[showChoice - 1]];

    // Display current seat availability
    show.displaySeatLayout();

    // Start seat booking
    bookTickets(show);
  }

  // Cancel an existing booking
  void cancelBooking() {

    std::cout << "\nEnter Booking ID: ";

    std::string id;
    if (!(std::cin >> id)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid ID.\n";
      return;
    }

    for (Booking &booking : bookings) {

      if (booking.getBookingId() != id)
        continue;

      if (!booking.isConfirmed()) {
        std::cout << "Booking already cancelled.\n";
        return;
      }

      // Display booking before cancellation
      booking.printTicket();

      std::cout << "Are you sure? (y/n): ";

      char choice;
      if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        choice = 'n';
      }

      if (choice == 'y' || choice == 'Y') {

        booking.cancel();

        std::cout << "Booking cancelled.\n";
        std::cout << "Rs." << static_cast<int>(booking.getTotalAmount())
                  << " refunded.\n";

      } else {

        std::cout << "Cancellation aborted.\n";
      }

      return;
    }

    std::cout << "Booking not found.\n";
  }

  // Find booking by ID or phone number
  void findBooking() const {

    std::cout << "\nEnter Booking ID or Phone Number: ";

    std::string query;
    if (!(std::cin >> query)) {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      std::cout << "Invalid query.\n";
      return;
    }

    bool found = false;

    for (const Booking &booking : bookings) {

      if (booking.getBookingId() == query ||
          booking.getCustomer().getPhoneNumber() == query) {

        booking.printTicket();
        found = true;
      }
    }

    if (!found)
      std::cout << "No tickets found for: " << query << "\n";
  }

  // Run the complete application
  void start() {

    int choice;

    do {
      displayMainMenu();

      if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid choice.\n";
        continue;
      }

      switch (choice) {

      case 1:
        displayMovies();
        break;

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
