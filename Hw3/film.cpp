#include "film.h"
#include "audience.h"
#include <string>
#include <iostream>

Film::Film(std::string title)
{
    this->title = title;
}

std::string Film::getTitle()
{
    return title;
}

void Film::addLinkToBooking(Booking *booking)
{
    bookings.push_back(booking);
}

void Film::getAllBookingOfFilm()
{
    std::cout << "All bookings for film " << title << ":" << std::endl;
    for (auto booking : bookings)
    {
        booking->showInfoBooking();
    }
}
