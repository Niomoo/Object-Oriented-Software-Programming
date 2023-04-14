#ifndef BOOKING_H
#define BOOKING_H


class Audience;
class Film;

class Booking
{
private:
    Audience *audience;
    Film *film;
    int seatNumber;

public:
    Booking(Audience *audience, Film *film, int seatNumber);
    void showInfoBooking();
};

#endif
