#include "airplane.h"
#include "passenger_role.h"
#include "booking.h"
#include "specific_flight.h"
#include "employee_role.h"
#include "flight_log.h"

using namespace std;

int main()
{
    // Create airplane instances
    Airplane *airplane = new Airplane("BR76");
    Airplane *airplane2 = new Airplane("CI87");
    // Create specificFlight instances
    SpecificFlight *specificFlight = new SpecificFlight("T1-2362");
    SpecificFlight *specificFlight2 = new SpecificFlight("T2-1459");

    // Link specificFlight to airplane
    specificFlight -> specifyAirplane(airplane);
    specificFlight -> createFlightLog(new FlightLog("Taipei", "Tokyo", "2023-05-24 06:45", "2023-05-24 07:23"));
    specificFlight2 -> specifyAirplane(airplane2);
    specificFlight2 -> createFlightLog(new FlightLog("Taipei", "Manila", "2023-05-26 13:55", "2023-05-26 15:12"));

    // Create passenger instances
    PassengerRole *passenger = new PassengerRole("John");
    PassengerRole *passenger2 = new PassengerRole("Amy");
    PassengerRole *passenger3 = new PassengerRole("Peter");
    PassengerRole *passenger4 = new PassengerRole("Jenny");
    PassengerRole *passenger5 = new PassengerRole("David");

    // Create employee instances
    EmployeeRole *employee = new EmployeeRole("Tom");
    EmployeeRole *employee2 = new EmployeeRole("Mary");
    EmployeeRole *employee3 = new EmployeeRole("Jack");
    EmployeeRole *employee4 = new EmployeeRole("Cindy");
    EmployeeRole *employee5 = new EmployeeRole("Kevin");

    // Create booking instances and link to passenger and specificFlight
    passenger -> makeBooking(new Booking(passenger, specificFlight, 10));
    passenger2 -> makeBooking(new Booking(passenger2, specificFlight, 21));
    passenger3 -> makeBooking(new Booking(passenger3, specificFlight, 7));
    passenger -> makeBooking(new Booking(passenger, specificFlight2, 11));
    passenger4 -> makeBooking(new Booking(passenger4, specificFlight2, 15));
    passenger5 -> makeBooking(new Booking(passenger5, specificFlight2, 3));
    
    // Link employee to specificFlight
    employee -> addSpecificFlight(specificFlight);
    employee2 -> addSpecificFlight(specificFlight);
    employee3 -> addSpecificFlight(specificFlight);
    employee2 -> addSpecificFlight(specificFlight2);
    employee4 -> addSpecificFlight(specificFlight2);
    employee5 -> addSpecificFlight(specificFlight2);

    // Show information of each instance
    specificFlight -> showInfo();
    specificFlight2->showInfo();

    passenger -> showInfo();
    passenger2 -> showInfo();
    passenger3 -> showInfo();
    passenger4 -> showInfo();
    passenger5 -> showInfo();
    cout << "-----------------------------" << endl;

    employee -> showInfo();
    employee2 -> showInfo();
    employee3 -> showInfo();
    employee4 -> showInfo();
    employee5 -> showInfo();
    cout << "-----------------------------" << endl;

    // Change specificFlight from airplane to airplane2
    specificFlight->changeAirplane(airplane2);
    specificFlight->showInfo();
    specificFlight2->showInfo();

    passenger->showInfo();
    passenger2->showInfo();
    passenger3->showInfo();
    passenger4->showInfo();
    passenger5->showInfo();
    cout << "-----------------------------" << endl;

    employee->showInfo();
    employee2->showInfo();
    employee3->showInfo();
    employee4->showInfo();
    employee5->showInfo();
    cout << "-----------------------------" << endl;

    return 0;
}
