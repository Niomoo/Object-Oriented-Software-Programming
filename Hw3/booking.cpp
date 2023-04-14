#include "booking.h"
#include "audience.h"
#include "film.h"
#include <iostream>

Booking::Booking(Audience *audience, Film *film, int seatNumber)
{
    this->audience = audience;
    this->audience->addLinkToBooking(this);
    this->film = film;
    this->film->addLinkToBooking(this);
    this->seatNumber = seatNumber;
}

void Booking::showInfoBooking()
{
    std::cout << "-----------------------" << std::endl;
    std::cout << "Audience: " << audience->getName() << std::endl;
    std::cout << "Film: " << film->getTitle() << std::endl;
    std::cout << "Seat Number: " << seatNumber << std::endl;
}
