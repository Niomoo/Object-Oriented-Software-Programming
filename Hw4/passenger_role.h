#ifndef PASSENGER_ROLE_H
#define PASSENGER_ROLE_H

#include <vector>

#include "booking.h"
#include "specific_flight.h"

using namespace std;

/**
 * @brief class of PassengerRole
 * @param name - name of the passenger
 */
class PassengerRole {
public:  
  // constructor
  PassengerRole(string name) : name{name}{}

  string getName() const { return name; }

  // make the booking instance link to passenger and specificFlight
  void makeBooking(Booking* booking) {
    booking->getSpecificFlight()->addLinkToBooking(booking);
    booking->getPassengerRole()->addLinkToBooking(booking);
  }
  
  void showInfo() {
    cout << "Passenger: " << name << endl;
    if(bookings.size() > 0) {
      cout << "Bookings" << endl;
      for(const auto b : bookings) {
        cout << ">> Flight " << b->getSpecificFlight()->getAirplane()->getAirplane() << " "<< b->getSpecificFlight()->getFlightNumber() << ": Seat number " << b->getSeatNumber() << endl;
      }
    }
  }

private:
  string name;
  vector<Booking*> bookings;
  // link to booking instance
  void addLinkToBooking(Booking* booking) {
    bookings.push_back(booking);
  }
};

#endif /* PASSENGER_ROLE_H */
