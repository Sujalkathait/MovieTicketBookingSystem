#ifndef MOVIE2_CPP
#define MOVIE2_CPP

#include <string>

// Class: Movie
// Responsibility: Stores movie information (title, language, duration)

class Movie
{
private:
    int movieId;
    std::string title;
    std::string language;
    int durationInMinutes;

public:

    // Constructor with all movie details
    Movie(
        int id = 0,
        const std::string& title = "",
        const std::string& language = "English",
        int duration = 0
    )
        : movieId(id),
          title(title),
          language(language),
          durationInMinutes(duration)
    {
    }

    // Constructor without movie ID
    Movie(const std::string& title, int duration)
        : movieId(0),
          title(title),
          language("English"),
          durationInMinutes(duration)
    {
    }

    // Getters
    int getMovieId() const
    {
        return movieId;
    }

    const std::string& getTitle() const
    {
        return title;
    }

    const std::string& getLanguage() const
    {
        return language;
    }

    int getDurationInMinutes() const
    {
        return durationInMinutes;
    }
};

#endif
