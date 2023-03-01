#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Passenger {
    string name;                    // name of the passenger
    string phone;             // phone of the passenger
    vector<int> tickets;            // tickets booked by the passenger
    
    public:
        Passenger(string, string);  // constructor
        void addTicket(int);        // add ticket to the ticket list
        void showBooking();         // show the booking list
        string getName() const;     // get the name of the passenger
};

Passenger::Passenger(string nameString, string phoneNumber) {
    name = nameString;
    phone = phoneNumber;
}

void Passenger::addTicket(int bus) {
    tickets.push_back(bus);
}

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

string Passenger::getName() const {
    return name;
}

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

Bus::Bus(int routeNumber)
{
    route = routeNumber;
    passengerCount = 0;
};

bool Bus::addPassenger(string name) {
    if (passengerCount < 10) {
        passengerList.push_back(name);
        passengerCount++;
        return true;
    }
    return false;
}

void Bus::showPassenger() {
    cout << "Passenger list of the bus " << route << ": ";
    for(auto passenger : passengerList) {
        cout << passenger << " ";
    }
    cout << endl;
}

int Bus::getRoute() const {
    return route;
}

class System {
    vector<Bus> busList;                  
    vector<Passenger> passengerList;

    public:
        createBus(int);                    // create a new bus route
        createPassenger(string, string);   // create a new passenger
        bookTicket(string, int);           // create booking record
        showBusBooking(int);        
        showPassengerTicket(string);
};

System::createBus(int route) {
    Bus bus(route);
    busList.push_back(bus);
}

System::createPassenger(string name, string phone) {
    Passenger passenger(name, phone);
    passengerList.push_back(passenger);
}

System::bookTicket(string name, int route) {
    for(auto & passenger: passengerList) {
        if(passenger.getName() == name) {
            for(auto & bus: busList) {
                if(bus.getRoute() == route) {
                    if(bus.addPassenger(passenger.getName())) {
                        passenger.addTicket(bus.getRoute());
                    }
                }
            }
        }
    }
}

System::showBusBooking(int route) {
    for(auto bus: busList) {
        if(bus.getRoute() == route) {
            bus.showPassenger();
        }
    }
}

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