#include <iostream>
#include <vector>
#include <string>

#include "Audience.h"
#include "Film.h"

using namespace std;

int main() {
    // create films
    Film* film1 = new Film("Star Wars");
    Film* film2 = new Film("Titanic");

    // create audiences
    Audience* audience1 = new Audience("Alice");
    Audience* audience2 = new Audience("Bob");
    Audience* audience3 = new Audience("Tony");
    Audience* audience4 = new Audience("Jessica");
    Audience* audience5 = new Audience("Linda");

    // audiences makes bookings
    audience1->makeBooking(film1, 2);
    audience1->makeBooking(film2, 3);
    audience2->makeBooking(film1, 4);
    audience3->makeBooking(film2, 8);
    audience4->makeBooking(film1, 3);
    audience5->makeBooking(film2, 7);

    // show all bookings of films
    film1->getAllBookingOfFilm();
    film2->getAllBookingOfFilm();

    // show all bookings of audiences
    audience1->getAllBookingOfAudience();
    audience2->getAllBookingOfAudience();
    audience3->getAllBookingOfAudience();
    audience4->getAllBookingOfAudience();
    audience5->getAllBookingOfAudience();

    return 0;
}
