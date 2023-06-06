#include "specific_flight.h"

void SpecificFlight::showInfo() {
    cout << "Flight ID" << endl
         << ">> " << flightID << endl;
    if (airplane != nullptr)
    {
        cout << "Airplane" << endl
             << ">> " << airplane->getAirplane() << endl;
    }
    if (flightLog != nullptr)
    {
        cout << "Flight Log" << endl;
        cout << ">> Origin: " << flightLog->getOrigin() << endl;
        cout << ">> Destination: " << flightLog->getDestination() << endl;
        cout << ">> Departure Time: " << flightLog->getDepartureTime() << endl;
        cout << ">> Arrival Time: " << flightLog->getArrivalTime() << endl;
    }
    if (bookings.size() > 0)
    {
          cout << "Bookings" << endl;
          for(const auto b : bookings) {
            p = b->getPassengerRole();
            cout << ">> Seat number " << b->getSeatNumber() << ": " << p->getName() << endl;
          }
        cout << "-----------------------------" << endl;
    }
    else
    {
        cout << "-----------------------------" << endl;
    }
    if(crewMembers.size() > 0) {
      cout << "CrewMembers\n>> ";
      for(const auto c : crewMembers) {
        cout << c->getName() << " " << endl;
      }
      cout << "-----------------------------" << endl;
    }
}