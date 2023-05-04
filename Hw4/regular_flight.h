#ifndef REGULAR_FLIGHT_H
#define REGULAR_FLIGHT_H

#include <string>
#include <vector>

#include "airline.h"

using namespace std;

class SpecificFlight;

/**
 * @brief class of RegularFlight
 * @param time - time of the regular flight
 * @param flightNumber - number of the flight
 * @param airline - airline of the flight
 */
class RegularFlight {
 public:

  // constructor
  RegularFlight(string time, int flightNumber, Airline* airline)
      : time{time}, flightNumber{flightNumber} {
    linkAirline(airline);
  }

  // return the time of the flight
  string getTime() const { return time; }

  // return the flight number of the flight
  int getFlightNumber() const { return flightNumber; }

  // return the specific flight list of the regular flight
  vector<SpecificFlight*>& getSpecificFlights() {
    return specific_flights;
  }

  // add a specific flight to the regular flight list
  void addSpecificFlight(SpecificFlight* specific_flight) {
    specific_flights.emplace_back(specific_flight);
  }

  // link the flight to the airline
  void linkAirline(Airline* airline) {
    this->airline = airline;
    airline->addRegularFlight(this);
  }

 private:
  string time;
  int flightNumber;
  vector<SpecificFlight*> specific_flights{};
  Airline* airline{nullptr};
};

#endif /* REGULAR_FLIGHT_H */
