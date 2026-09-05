#include "bookingService9.cpp"
#include "cardPayment13.cpp"
#include "cashPayment14.cpp"
#include "cinema5.cpp"
#include "customer10.cpp"
#include "movie2.cpp"
#include "payment11.cpp"
#include "priceCalculator8.cpp"
#include "screen4.cpp"
#include "seat3.cpp"
#include "show7.cpp"
#include "showSeat6.cpp"
#include "upiPayment12.cpp"

// Class: CinemaMainMenu
// Responsibility: Starts the booking system

class CinemaMainMenu {
private:
  BookingService &bookingService;

public:
  // Constructor
  CinemaMainMenu(BookingService &service) : bookingService(service) {}

  // Start menu
  void launch() { bookingService.start(); }
};

int main() {
  // Create cinema
  Cinema cinema("PVR Cinemas");

  // Create Screen 1
  Screen screen1(1, "Screen-1");

  screen1.addSeat(Seat("A1", "SILVER"));
  screen1.addSeat(Seat("A2", "SILVER"));
  screen1.addSeat(Seat("A3", "SILVER"));
  screen1.addSeat(Seat("A4", "SILVER"));

  screen1.addSeat(Seat("B1", "GOLD"));
  screen1.addSeat(Seat("B2", "GOLD"));
  screen1.addSeat(Seat("B3", "GOLD"));

  screen1.addSeat(Seat("C1", "PLATINUM"));
  screen1.addSeat(Seat("C2", "PLATINUM"));

  cinema.addScreen(screen1);

  // Create Screen 2
  Screen screen2(2, "Screen-2");

  screen2.addSeat(Seat("A1", "SILVER"));
  screen2.addSeat(Seat("A2", "SILVER"));

  screen2.addSeat(Seat("B1", "GOLD"));
  screen2.addSeat(Seat("B2", "GOLD"));

  screen2.addSeat(Seat("C1", "PLATINUM"));
  screen2.addSeat(Seat("C2", "PLATINUM"));

  cinema.addScreen(screen2);

  // Create movies
  Movie movie1(1, "3 Idiots", "Hindi", 170);
  Movie movie2(2, "Interstellar", "English", 169);

  cinema.addMovie(movie1);
  cinema.addMovie(movie2);

  // Create shows
  Show show1(&movie1, screen1, "06:00 PM", 101);

  // Pre-book seats for demonstration
  ShowSeat *seat1 = show1.findSeat("A2");
  if (seat1 != nullptr) {
    seat1->bookSeat();
  }

  ShowSeat *seat2 = show1.findSeat("B3");
  if (seat2 != nullptr) {
    seat2->bookSeat();
  }

  Show show2(&movie1, screen2, "09:00 PM", 102);
  Show show3(&movie2, screen1, "09:30 PM", 103);

  // Create booking service
  BookingService bookingService;

  bookingService.addMovie(movie1);
  bookingService.addMovie(movie2);

  bookingService.addShow(show1);
  bookingService.addShow(show2);
  bookingService.addShow(show3);

  // Start application
  CinemaMainMenu menu(bookingService);
  menu.launch();

  return 0;
}
