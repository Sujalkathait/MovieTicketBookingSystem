#ifndef SEAT3_CPP
#define SEAT3_CPP

#include <string>

// Class: Seat
// Responsibility: Represents a physical seat in a screen

class Seat
{
private:
    std::string seatNumber;
    std::string seatType;

public:

    // Constructor
    Seat(
        const std::string& seatNumber = "",
        const std::string& seatType = ""
    )
        : seatNumber(seatNumber),
          seatType(seatType)
    {
    }

    // Getters
    const std::string& getSeatNumber() const
    {
        return seatNumber;
    }

    const std::string& getSeatType() const
    {
        return seatType;
    }
};

#endif