#ifndef AUDIENCE_H
#define AUDIENCE_H

#include <string>
#include <vector>
#include "booking.h"

class Film;

class Audience
{
private:
    std::string name;
    std::vector<Booking *> bookings;

public:
    Audience(std::string name);
    std::string getName();
    void makeBooking(Film *film, int seatNumber);
    void addLinkToBooking(Booking *booking);
    void getAllBookingOfAudience();
};

#endif
