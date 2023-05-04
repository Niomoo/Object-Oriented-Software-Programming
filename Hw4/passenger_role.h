#ifndef PASSENGER_ROLE_H
#define PASSENGER_ROLE_H

#include <vector>

#include "booking.h"
#include "person_role.h"
#include "specific_flight.h"

using namespace std;

/**
 * @brief class of PassengerRole extends from PersonRole
 */
class PassengerRole : public PersonRole {
 public:
  
  // constructor
  PassengerRole() {}
  ~PassengerRole() {
    for (auto& b : bookings) {
      delete b;
    }
  }

  // add booking record to the passenger booking list
  void addBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkPassengerRole(this);
  }

  // make a booking record given to a specific flight and seatNumber
  Booking* bookSpecificFlight(SpecificFlight* specific_flight, int seatNumber) {
    Booking* b = new Booking(seatNumber);
    this->addBooking(b);
    specific_flight->addBooking(b);
    return b;
  }

  // show the booking details of the passenger
  void printBookings() {
    for (const auto& b : bookings) {
      cout << "No."
           << b->getSpecificFlight()->getRegularFlight()->getFlightNumber() << " : " 
           << b->getSpecificFlight()->getDate() << " : "
           << b->getSpecificFlight()->getRegularFlight()->getTime()
           << "\t Seat number: " << b->getSeatNumber()
           << endl;
    }
  }

  // cancel a booking request
  void cancelBooking(Booking* booking) {
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
      if (*it == booking) {
        (*it)->getSpecificFlight()->cancelBooking(*it);
        delete *it;
        bookings.erase(it);
        break;
      }
    }
  }

 private:
  vector<Booking*> bookings{};
};

#endif /* PASSENGER_ROLE_H */
