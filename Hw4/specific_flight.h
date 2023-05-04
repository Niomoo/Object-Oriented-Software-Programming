#ifndef SPECIFIC_FLIGHT_H
#define SPECIFIC_FLIGHT_H

#include <string>
#include <vector>

#include "booking.h"
#include "regular_flight.h"

using namespace std;

class EmployeeRole;

/**
 * @brief class of SpecificFlight
 * @param date - date of the specific flight
 * @param regular_flight - one regular flight links to many specific flights on different dates
 */
class SpecificFlight {
 public:

  // constructor
  SpecificFlight(string date, RegularFlight* regular_flight) : date{date} {
    linkRegularFlight(regular_flight);
  }

  // return the date of the specific flight
  string getDate() const { return date; }

  // return the regular flight
  RegularFlight* getRegularFlight() const { return regular_flight; }

  // add booking record to the specific flight
  void addBooking(Booking* booking) {
    bookings.emplace_back(booking);
    booking->linkSpecificFlight(this);
  }

  // link the specific flight to the regular flight
  void linkRegularFlight(RegularFlight* regular_flight) {
    this->regular_flight = regular_flight;
    regular_flight->addSpecificFlight(this);
  }

  // add employees that serve on the specific flight
  void addEmployeeRole(EmployeeRole* emp) { this->employees.push_back(emp); }
 
  // remove the booking record
  void cancelBooking(Booking* booking) {
    for (auto it = bookings.begin(); it != bookings.end(); ++it) {
      if (*it == booking) {
        bookings.erase(it);
        break;
      }
    }
  }

 private:
  string date;
  vector<Booking*> bookings{};
  vector<EmployeeRole*> employees{};
  RegularFlight* regular_flight{nullptr};
};

#endif /* SPECIFIC_FLIGHT_H */
