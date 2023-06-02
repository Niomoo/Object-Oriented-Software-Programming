#include "airplane.h"
#include "booking.h"
#include "employee_role.h"
#include "passenger_role.h"
#include "specific_flight.h"
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

    passenger -> makeBooking(new Booking(passenger, specificFlight, 1));
    specificFlight -> showInfo();

    return 0;
}
