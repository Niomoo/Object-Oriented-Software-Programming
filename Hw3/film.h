#ifndef FILM_H
#define FILM_H

#include <string>
#include <vector>
#include "booking.h"

class Audience;

class Film
{
private:
    std::string title;
    std::vector<Booking *> bookings;

public:
    Film(std::string title);
    std::string getTitle();
    void addLinkToBooking(Booking *booking);
    void getAllBookingOfFilm();
};

#endif
