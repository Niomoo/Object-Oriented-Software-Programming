#ifndef SPECIFIC_FLIGHT_H
#define SPECIFIC_FLIGHT_H

#include <string>
#include <vector>

#include "booking.h"
#include "flight_log.h"

using namespace std;

class EmployeeRole;

/**
 * @brief class of SpecificFlight
 * @param date - date of the specific flight
 */
class SpecificFlight
{
public:
  SpecificFlight(string flightNumber, string origin, string destination,string departureTime, string arrivalTime)
  {
    this->flightNumber = flightNumber;
    this->origin = origin;
    this->destination = destination;
    this->departureTime = departureTime;
    this->arrivalTime = arrivalTime;
  }

  void specifyAirplane(Airplane *airplane)
  {
    this->airplane = airplane;
    airplane->addLinkToSpecificFlight(this);
  }

  void createFlightLog()
  {
    FlightLog *flightLog = new FlightLog(this);
    flightLogs.push_back(flightLog);
  }

  void changeAirplane(Airplane *airplane)
  {
    this->airplane->deleteLinkToSpecificFlight(this);
    this->airplane = airplane;
    airplane->addLinkToSpecificFlight(this);
  }

  vector<EmployeeRole *> findCrewMember()
  {
    return crewMembers;
  }

  void addLinkToBooking(Booking *booking)
  {
    bookings.push_back(booking);
  }

private:
  string flightNumber;
  string origin;
  string destination;
  string departureTime;
  string arrivalTime;
  Airplane *airplane;
  vector<EmployeeRole *> crewMembers;
  vector<Booking *> bookings;
  vector<FlightLog *> flightLogs;
};

#endif /* SPECIFIC_FLIGHT_H */
