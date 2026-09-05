#ifndef CINEMA5_CPP
#define CINEMA5_CPP

#include <string>
#include <vector>
#include "movie2.cpp"
#include "screen4.cpp"

// Class: Cinema
// Responsibility: Manages screens and movie catalog

class Cinema
{
private:
    std::string cinemaName;
    std::vector<Screen> screens;
    std::vector<Movie> movies;

public:

    // Constructor
    Cinema(const std::string& name)
        : cinemaName(name)
    {
    }

    // Add a screen
    void addScreen(const Screen& screen)
    {
        screens.push_back(screen);
    }

    // Add a movie
    void addMovie(const Movie& movie)
    {
        movies.push_back(movie);
    }

    // Getters
    const std::string& getCinemaName() const
    {
        return cinemaName;
    }

    const std::vector<Screen>& getScreens() const
    {
        return screens;
    }

    const std::vector<Movie>& getMovies() const
    {
        return movies;
    }
};

#endif
