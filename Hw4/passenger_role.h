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
  PassengerRole() {}
  ~PassengerRole() {
    for (auto& b : bookings) {
      delete b;
    }
  }

  void makeBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkPassengerRole(this);
  }


 private:
  vector<Booking*> bookings{};
  Booking* addLinkToBooking(SpecificFlight* specific_flight, int seatNumber) {
    Booking* b = new Booking(seatNumber);
    this->makeBooking(b);
    return b;
  }
};

#endif /* PASSENGER_ROLE_H */
