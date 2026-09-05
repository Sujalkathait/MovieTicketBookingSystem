#ifndef SHOW7_CPP
#define SHOW7_CPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "movie2.cpp"
#include "screen4.cpp"
#include "showSeat6.cpp"

// Class: Show
// Responsibility: Represents a movie show at a specific time and screen

class Show
{
private:
    int showId;
    const Movie* movie;
    Screen screen;
    std::string showTime;
    std::vector<ShowSeat> showSeats;

public:

    // Constructor
    Show(const Movie* m, const Screen& s, const std::string& time, int id)
        : movie(m),
          screen(s),
          showTime(time),
          showId(id)
    {
        for (const Seat& seat : screen.getSeats())
        {
            ShowSeat ss(seat);
            showSeats.push_back(ss);
        }
    }

    // Getters
    int getShowId() const
    {
        return showId;
    }

    const Movie& getMovie() const
    {
        return *movie;
    }

    const Screen& getScreen() const
    {
        return screen;
    }

    const std::string& getShowTime() const
    {
        return showTime;
    }

    const std::vector<ShowSeat>& getShowSeats() const
    {
        return showSeats;
    }

    std::vector<ShowSeat>& getShowSeats()
    {
        return showSeats;
    }

    // Find a seat by seat number
    ShowSeat* findSeat(const std::string& seatNumber)
    {
        for (auto& showSeat : showSeats)
        {
            if (showSeat.getSeat().getSeatNumber() == seatNumber)
            {
                return &showSeat;
            }
        }

        return nullptr;
    }

    const ShowSeat* findSeat(const std::string& seatNumber) const
    {
        for (const auto& showSeat : showSeats)
        {
            if (showSeat.getSeat().getSeatNumber() == seatNumber)
            {
                return &showSeat;
            }
        }

        return nullptr;
    }

    // Display seat layout
    void displaySeatLayout() const
    {
        std::cout << "\nSCREEN-" << screen.getScreenId()
                  << "  " << showTime
                  << " | " << movie->getTitle()
                  << "\n\n";

        std::string currentCategory = "";

        for (const auto& showSeat : showSeats)
        {
            std::string seatType = showSeat.getSeat().getSeatType();

            if (seatType != currentCategory)
            {
                if (!currentCategory.empty())
                {
                    std::cout << "\n";
                }

                currentCategory = seatType;

                std::cout << std::left
                          << std::setw(12)
                          << currentCategory;
            }

            std::cout << showSeat.getSeat().getSeatNumber()
                      << (showSeat.isAvailable() ? "[ ] " : "[X] ");
        }

        std::cout << "\n\n";
        std::cout << "[ ] = Available    [X] = Booked\n\n";
    }
};

#endif