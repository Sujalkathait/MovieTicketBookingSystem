#ifndef SCREEN4_CPP
#define SCREEN4_CPP

#include <string>
#include <vector>
#include "seat3.cpp"

// Class: Screen
// Responsibility: Manages seats inside a screen

class Screen
{
private:
    int screenId;
    std::string screenName;
    std::vector<Seat> seats;

public:

    // Constructor
    explicit Screen(
        int screenId = 0,
        const std::string& screenName = ""
    )
        : screenId(screenId),
          screenName(
              screenName.empty()
                  ? "Screen-" + std::to_string(screenId)
                  : screenName
          )
    {
    }

    // Add a seat to the screen
    void addSeat(const Seat& seat)
    {
        seats.push_back(seat);
    }

    // Getters
    int getScreenId() const
    {
        return screenId;
    }

    const std::string& getScreenName() const
    {
        return screenName;
    }

    const std::vector<Seat>& getSeats() const
    {
        return seats;
    }
};

#endif
