#ifndef PRICECALCULATOR8_CPP
#define PRICECALCULATOR8_CPP

#include <string>
#include <vector>
#include "showSeat6.cpp"

// Class: PriceCalculator
// Responsibility: Calculates ticket prices based on seat category

class PriceCalculator
{
public:

    // Seat prices
    static constexpr double SILVER_PRICE = 150.0;
    static constexpr double GOLD_PRICE = 250.0;
    static constexpr double PLATINUM_PRICE = 400.0;

    // Get price based on seat type
    double getPriceForSeatType(const std::string& seatType) const
    {
        if (seatType == "SILVER")
            return SILVER_PRICE;

        if (seatType == "GOLD")
            return GOLD_PRICE;

        if (seatType == "PLATINUM")
            return PLATINUM_PRICE;

        return 0.0;
    }

    // Calculate price for one seat
    double calculateSeatPrice(const ShowSeat& seat) const
    {
        return getPriceForSeatType(
            seat.getSeat().getSeatType()
        );
    }

    // Calculate total price for selected seats
    double calculateTotalPrice(
        const std::vector<ShowSeat*>& selectedSeats
    ) const
    {
        double total = 0.0;

        for (const ShowSeat* seat : selectedSeats)
        {
            if (seat != nullptr)
            {
                total += calculateSeatPrice(*seat);
            }
        }

        return total;
    }
};

#endif
