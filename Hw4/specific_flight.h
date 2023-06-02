#ifndef SPECIFIC_FLIGHT_H
#define SPECIFIC_FLIGHT_H

#include <string>
#include <vector>

#include "airplane.h"
#include "booking.h"
#include "employee_role.h"
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
  SpecificFlight(string flightID)
  : flightID{flightID} {}

  void specifyAirplane(Airplane *airplane)
  {
    this->airplane = airplane;
    airplane->addLinkToSpecificFlight(this);
  }

  void createFlightLog(FlightLog* flightLog)
  {
    this->flightLog = flightLog;    
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

  void showInfo() {
    cout << "Flight ID" << endl << ">> " << flightID << endl;
    if(airplane != nullptr) {
      cout << "Airplane" << endl << ">> " << airplane->getAirplane() << endl;
    }
    if(flightLog != nullptr) {  
      cout << "Flight Log" << endl;
      cout << ">> Origin: " << flightLog->getOrigin() << endl;
      cout << ">> Destination: " << flightLog->getDestination() << endl;
      cout << ">> Departure Time: " << flightLog->getDepartureTime() << endl;
      cout << ">> Arrival Time: " << flightLog->getArrivalTime() << endl;
    }
    if(bookings.size() > 0) {
      cout << "Bookings" << endl;
      for(int i = 0; i < bookings.size(); i++) {
        cout << ">> Seat number " << bookings[i]->getSeatNumber() << ": " << bookings[i]->getPassengerRole() << endl;
      }
    }
    cout << "-----------------------------" << endl;
  }

private:
  string flightID;
  Airplane *airplane;
  vector<EmployeeRole *> crewMembers;
  vector<Booking *> bookings;
  FlightLog *flightLog;
};

#endif /* SPECIFIC_FLIGHT_H */
