#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

/**
 * @brief class for passenger
 */
class Passenger {
    string name;                    // name of the passenger
    string phone;                   // phone of the passenger
    vector<int> tickets;            // tickets booked by the passenger
    
    public:
        Passenger(string, string);  // constructor
        void addTicket(int);        // add ticket to the ticket list
        void showBooking();         // show the booking list
        string getName() const;     // get the name of the passenger
};

/**
 * @brief Passenger constructor
 * @param nameString passenger name
 * @param phoneNumber passenger phone number
 */
Passenger::Passenger(string nameString, string phoneNumber) {
    name = nameString;
    phone = phoneNumber;
}

/**
 * @brief Add ticket to the list
 * @param bus route number
 */
void Passenger::addTicket(int bus) {
    tickets.push_back(bus);
}

/**
 * @brief Print the tickets of the passenger
 */
void Passenger::showBooking() {
    if(tickets.size() == 0) {
        cout << "Passenger " << name << " has no tickets" << endl;
    } else {        
        cout << "Passenger " << name << " has booked: ";
        for(auto ticket : tickets) {
            cout << ticket << " ";
        }
        cout << endl;
    }
}

/**
 * @brief Get the name from the passenger
 * @return the name of the passenger
 */
string Passenger::getName() const {
    return name;
}

/**
 * @brief class for bus
 */
class Bus {
    int route;                      // route number
    int passengerCount;             // number of passengers
    vector<string> passengerList;   // passenger that booked the ticket

    public:
        Bus(int);                    // constructor
        bool addPassenger(string);   // add passenger to the passenger list
        void showPassenger();        // show passenger that booked the bus route
        int getRoute() const;        // get the route of the bus
};

/**
 * @brief Bus constructor
 * @param routeNumber route number for the bus
 */
Bus::Bus(int routeNumber)
{
    route = routeNumber;
    passengerCount = 0;
};

/**
 * @brief Add passenger to the bus
 * @param name passenger name for the ticket
 */
bool Bus::addPassenger(string name) {
    if (passengerCount < 10) {
        passengerList.push_back(name);
        passengerCount++;
        return true;
    }
    return false;
}

/**
 * @brief Print the passengers of the bus
 */
void Bus::showPassenger() {
    cout << "Passenger list of the bus " << route << ": ";
    for(auto passenger : passengerList) {
        cout << passenger << " ";
    }
    cout << endl;
}

/**
 * @brief Get the route number of the bus
 * @return the route number of the bus
 */
int Bus::getRoute() const {
    return route;
}

/**
 * @brief class for the booking system
 */
class System {
    vector<Bus> busList;                    // list of bus
    vector<Passenger> passengerList;        // list of passenger

    public:
        createBus(int);                     // create a new bus route
        createPassenger(string, string);    // create a new passenger
        bookTicket(string, int);            // create booking record
        showBusBooking(int);                // show the booking record
        showPassengerTicket(string);        // show the passenger tickets
};

/**
 * @brief Create a bus class
 * @param route route number of the bus
 */
System::createBus(int route) {
    Bus bus(route);
    busList.push_back(bus);
}

/**
 * @brief Create a passenger class
 * @param name name of the passenger
 * @param phone phone number of the passenger 
 */
System::createPassenger(string name, string phone) {
    Passenger passenger(name, phone);
    passengerList.push_back(passenger);
}

/**
 * @brief Create a ticket booking record
 * @param name name of the passenger
 * @param route route number of the bus
 */
System::bookTicket(string name, int route) {
    for(auto & passenger: passengerList) {
        if(passenger.getName() == name) {
            for(auto & bus: busList) {
                if(bus.getRoute() == route) {
                    if(bus.addPassenger(passenger.getName())) {        // check if the bus seat is available
                        passenger.addTicket(bus.getRoute());
                    } else {
                        cout << "Ticket for Bus " << bus.getRoute() << " is not available." << endl;
                    }
                }
            }
        }
    }
}

/**
 * @brief Print the passenger of the bus
 * @param route route number of the bus
 */
System::showBusBooking(int route) {
    for(auto bus: busList) {
        if(bus.getRoute() == route) {
            bus.showPassenger();
        }
    }
}

/**
 * @brief Print the ticket booked by the passenger
 * @param name name of the passenger
 */
System::showPassengerTicket(string name) {
    for(auto passenger: passengerList) {
        if(passenger.getName() == name) {
            passenger.showBooking();
        }
    }
}

int main() {

    System system;

    system.createBus(101);
    system.createBus(202);

    system.createPassenger("Amy", "0901234567");
    system.createPassenger("Tony", "062757575");
    system.createPassenger("Charlie", "0925124384");
    system.createPassenger("Jessica", "0229123456");
    system.createPassenger("Sam", "0987098098");
    
    system.bookTicket("Amy", 101);
    system.bookTicket("Amy", 202);
    system.bookTicket("Tony", 101);
    system.bookTicket("Charlie", 202);
    system.bookTicket("Jessica", 101);
    system.bookTicket("Jessica", 202);

    system.showBusBooking(101);
    system.showBusBooking(202);

    system.showPassengerTicket("Amy");
    system.showPassengerTicket("Tony");
    system.showPassengerTicket("Charlie");
    system.showPassengerTicket("Jessica");
    system.showPassengerTicket("Sam");

    return 0;
};