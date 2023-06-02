#ifndef PASSENGER_ROLE_H
#define PASSENGER_ROLE_H

#include <vector>

#include "booking.h"
#include "specific_flight.h"

using namespace std;

/**
 * @brief class of PassengerRole extends from PersonRole
 */
class PassengerRole {
 public:
  
  // constructor
  PassengerRole(string name) : name{name}{}

  string getName() const { return name; }
  void makeBooking(Booking* booking) {
    booking->getSpecificFlight()->addLinkToBooking(booking);
    booking->getPassengerRole()->addLinkToBooking(booking);
  }
  

 private:
  string name;
  vector<Booking*> bookings;
  void addLinkToBooking(Booking* booking) {
    bookings.push_back(booking);
  }
};

#endif /* PASSENGER_ROLE_H */
