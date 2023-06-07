#ifndef EMPLOYEE_ROLE_H
#define EMPLOYEE_ROLE_H

#include <vector>

#include "specific_flight.h"

using namespace std;

/**
 * @brief class of EmployeeRole
 * @param name - name of the employee
 */
class EmployeeRole {
 public:

  // constructor
  EmployeeRole(string name) : name{ name } {}

  string getName() { return name; }

  // link the crew member to specificFlight
  void addSpecificFlight(SpecificFlight* flight) {
    this->specific_flights.push_back(flight);
    flight->addEmployeeRole(this);
  }

  // show information of the employee
  void showInfo() {
    cout << "Employee: " << name << endl;
    if(specific_flights.size() > 0) {
      cout << "SpecificFlights" << endl;
      for(const auto f : specific_flights) {
        cout << ">> Flight " << f->getAirplane()->getAirplane() << " " << f->getFlightNumber() << endl;
      }
    }
  }

 private:
  string name;
  vector<SpecificFlight*> specific_flights{};
};

#endif /* EMPLOYEE_ROLE_H */
