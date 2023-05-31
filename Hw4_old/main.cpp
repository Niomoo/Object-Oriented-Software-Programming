#include "airline.h"
#include "booking.h"
#include "employee_role.h"
#include "passenger_role.h"
#include "person.h"
#include "person_role.h"
#include "regular_flight.h"
#include "specific_flight.h"

using namespace std;

int main()
{
    Airline *eva_air = new Airline("EVA Air");
    RegularFlight *flight1 = new RegularFlight("10:25", 1523, eva_air);
    SpecificFlight *flight1_0501 = new SpecificFlight("2023-05-01", flight1);
    SpecificFlight *flight1_0502 = new SpecificFlight("2023-05-02", flight1);
    SpecificFlight *flight1_0503 = new SpecificFlight("2023-05-03", flight1);

    RegularFlight *flight2 = new RegularFlight("14:45", 2459, eva_air);
    SpecificFlight *flight2_0501 = new SpecificFlight("2023-05-01", flight2);

    Person *mary = new Person("Mary", "D251236785", eva_air, {new EmployeeRole("Captain")});
    Person *jack = new Person("Jack", "R151789654", eva_air, {new EmployeeRole("Flight attendant")});
    Person *tony = new Person("Tony", "A158785135", eva_air, {new EmployeeRole("Flight attendant", jack->get_employee_role())});
    Person *hank = new Person("Hank", "F127457811", eva_air, {new EmployeeRole("Flight attendant", jack->get_employee_role()), new PassengerRole()});

    Person *robin = new Person("Robin", "T134574416", {new PassengerRole()});
    Person *elsa = new Person("Elsa", "S249085452", {new PassengerRole()});
    Person *jasmine = new Person("Jasmine", "W226451701", {new PassengerRole()});

    cout << "\nTime for flights in Eva Air:" << endl;
    for (const auto &f : eva_air->getRegularFlights())
    {
        cout << "No." << f->getFlightNumber() << ": " << f->getTime() << endl;
    }
    cout << "\nDate for Flight No.1523:" << endl;
    for (const auto &f : flight1->getSpecificFlights())
    {
        cout << f->getDate() << endl;
    }
    cout << "\nDate for Flight No.2459:" << endl;
    for (const auto &f : flight2->getSpecificFlights())
    {
        cout << f->getDate() << endl;
    }
    cout << "\nEmployees in Eva Air:" << endl;
    for (const auto &p : eva_air->getPeople())
    {
        cout << p->getName() << " : " 
            << p->get_employee_role()->getJobFunction() << endl;
    }
    cout << "\nJack is the supervisor of the employees:" << endl;
    for (const auto &s : jack->get_employee_role()->getSubordinates())
    {
        cout << s->getPerson()->getName() << endl;
    }

    Booking *b1 = hank->get_passenger_role()->bookSpecificFlight(flight1_0501, 11);
    hank->get_passenger_role()->bookSpecificFlight(flight1_0502, 23);
    robin->get_passenger_role()->bookSpecificFlight(flight1_0501, 12);
    elsa->get_passenger_role()->bookSpecificFlight(flight1_0502, 25);
    jasmine->get_passenger_role()->bookSpecificFlight(flight2_0501, 17);

    cout << endl;
    cout << "Passenger " << hank->getName() << " has booked: " << endl;
    hank->get_passenger_role()->printBookings();
    cout << endl;
    cout << "Passenger " << robin->getName() << " has booked: " << endl;
    robin->get_passenger_role()->printBookings();
    cout << endl;
    cout << "Passenger " << elsa->getName() << " has booked: " << endl;
    elsa->get_passenger_role()->printBookings();
    cout << endl;
    cout << "Passenger " << jasmine->getName() << " has booked: " << endl;
    jasmine->get_passenger_role()->printBookings();
    cout << endl;

    cout << "Passenger " << hank->getName() << " has cancelled No."
         << b1->getSpecificFlight()->getRegularFlight()->getFlightNumber()
         << " on " << b1->getSpecificFlight()->getDate()
         << endl;
    hank->get_passenger_role()->cancelBooking(b1);
    cout << endl;

    cout << "Passenger " << hank->getName() << " has booked: " << endl;
    hank->get_passenger_role()->printBookings();
    cout << endl;

    for (auto &p : {mary, jack, tony, hank, robin, elsa, jasmine})
        delete p;
    for (auto &p : {flight1_0501, flight1_0502, flight1_0503, flight2_0501})
        delete p;
    for (auto &p : {flight1, flight2})
        delete p;
    delete eva_air;
    return 0;
}
