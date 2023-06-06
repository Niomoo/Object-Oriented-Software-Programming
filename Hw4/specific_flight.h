#ifndef SPECIFIC_FLIGHT_H
#define SPECIFIC_FLIGHT_H

#include <string>
#include <vector>
#include <iostream>

#include "airplane.h"
#include "booking.h"
#include "passenger_role.h"
#include "flight_log.h"
// #include "employee_role.h"

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

  void addEmployeeRole(EmployeeRole* employeeRole) {
    this->crewMembers.push_back(employeeRole);
  }

  void addLinkToBooking(Booking *booking)
  {
    bookings.push_back(booking);
  }

  void showInfo(){
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
  //   cout << "Bookings" << endl;
  //   for(const auto b : bookings) {
  //     cout << ">> Seat number " << b->getSeatNumber() << ": " << b->getPassengerRole() << endl;
  //   }
  // cout << "-----------------------------" << endl;
  } else {
    cout << "-----------------------------" << endl;
  }
  // if(crewMembers.size() > 0) {
  //   cout << "CrewMembers\n>> ";
  //   for(const auto c : crewMembers) {
  //     cout << c->getName() << " " << endl;
  //   }
  //   cout << "-----------------------------" << endl;
  // }
  }

  vector<Booking *> getBookings() const { return bookings; }

private:
  string flightID;
  Airplane *airplane;
  vector<EmployeeRole *> crewMembers;
  vector<Booking *> bookings;
  FlightLog *flightLog;
};


#endif /* SPECIFIC_FLIGHT_H */
