#ifndef SHOWSEAT6_CPP
#define SHOWSEAT6_CPP

#include "seat3.cpp"

// Seat availability status
enum class ShowSeatStatus
{
    AVAILABLE,
    BOOKED
};

// Class: ShowSeat
// Responsibility: Tracks seat availability for a specific show

class ShowSeat
{
private:
    Seat seat;
    ShowSeatStatus status;

public:

    // Constructor
    ShowSeat(const Seat& seat)
        : seat(seat),
          status(ShowSeatStatus::AVAILABLE)
    {
    }

    // Check if seat is available
    bool isAvailable() const
    {
        return status == ShowSeatStatus::AVAILABLE;
    }

    // Book the seat
    void bookSeat()
    {
        status = ShowSeatStatus::BOOKED;
    }

    // Release the seat
    void releaseSeat()
    {
        status = ShowSeatStatus::AVAILABLE;
    }

    // Getters
    const Seat& getSeat() const
    {
        return seat;
    }

    ShowSeatStatus getStatus() const
    {
        return status;
    }
};

#endif
