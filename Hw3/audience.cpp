#include "audience.h"
#include "film.h"
#include <iostream>

Audience::Audience(std::string name)
{
    this->name = name;
}

std::string Audience::getName()
{
    return name;
}

void Audience::makeBooking(Film *film, int seatNumber)
{
    Booking *booking = new Booking(this, film, seatNumber);
    bookings.push_back(booking);
    film->addLinkToBooking(booking);
    addLinkToBooking(booking);
}

void Audience::addLinkToBooking(Booking *booking)
{
    bookings.push_back(booking);
}

void Audience::getAllBookingOfAudience()
{
    std::cout << "All bookings for audience " << name << ":" << std::endl;
    for (auto booking : bookings)
    {
        booking->showInfoBooking();
    }
}
