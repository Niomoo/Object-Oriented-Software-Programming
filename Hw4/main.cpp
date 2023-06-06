#include "airplane.h"
#include "passenger_role.h"
#include "booking.h"
#include "specific_flight.h"
#include "employee_role.h"
#include "flight_log.h"

using namespace std;

int main()
{
    Airplane *airplane = new Airplane("BR76");
    Airplane *airplane2 = new Airplane("CI87");
    SpecificFlight *specificFlight = new SpecificFlight("T1-2362");

    specificFlight -> specifyAirplane(airplane);
    specificFlight -> createFlightLog(new FlightLog("Taipei", "Tokyo", "2023-05-24 06:45", "2023-05-24 07:23"));
    specificFlight -> showInfo();

    specificFlight -> changeAirplane(airplane2);
    specificFlight -> showInfo();

    PassengerRole *passenger = new PassengerRole("John");
    PassengerRole *passenger2 = new PassengerRole("Amy");

    EmployeeRole *employee = new EmployeeRole("Tom");
    EmployeeRole *employee2 = new EmployeeRole("Mary");
    EmployeeRole *employee3 = new EmployeeRole("Jack");

    passenger -> makeBooking(new Booking(passenger, specificFlight, 1));
    passenger2 -> makeBooking(new Booking(passenger2, specificFlight, 2));
    
    employee -> addSpecificFlight(specificFlight);
    employee2 -> addSpecificFlight(specificFlight);
    employee3 -> addSpecificFlight(specificFlight);

    specificFlight -> showInfo();
    if(specificFlight -> getBookings().size() > 0)
    {
        cout << "Bookings" << endl;
        for (const auto b : specificFlight->getBookings())
        {
            cout << ">> Seat number " << b->getSeatNumber() << ": " << b->getPassengerRole()->getName() << endl;
        }
    } 
    if(specificFlight -> findCrewMember().size() > 0) {
      cout << "CrewMembers\n>> ";
      for(const auto c : specificFlight -> findCrewMember()) {
        cout << c->getName() << " ";
      }
      cout << "\n-----------------------------" << endl;
    }

    return 0;
}
