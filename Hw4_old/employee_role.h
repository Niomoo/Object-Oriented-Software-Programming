#ifndef EMPLOYEE_ROLE_H
#define EMPLOYEE_ROLE_H

#include <iostream>
#include <vector>

#include "person_role.h"
#include "specific_flight.h"

using namespace std;

/**
 * @brief class of EmployeeRole extends from PersonRole
 * @param jobFunction - job of the employee
 */
class EmployeeRole : public PersonRole {
 public:

  // constructor
  EmployeeRole(string jobFunction) : jobFunction{ jobFunction } {}
  EmployeeRole(string jobFunction, EmployeeRole* supervisor)
      : EmployeeRole{jobFunction} {
    addSupervisor(supervisor);
  }

  // return the job of the employee
  string getJobFunction() { return jobFunction; }

  // add subordinate to the supervisor employee
  void addSubordinate(EmployeeRole* emp) {
    subordinates.emplace_back(emp);
    emp->linkSupervisor(emp);
  }

  // add supervisor to the subordinate employee
  void addSupervisor(EmployeeRole* emp) { emp->addSubordinate(this); }

  // link the supervisor and the employee
  void linkSupervisor(EmployeeRole* emp) { this->supervisor = emp; }

  // add flight to the employee
  void addSpecificFlight(SpecificFlight* specific_flight) {
    this->specific_flights.push_back(specific_flight);
    specific_flight->addEmployeeRole(this);
  }

  // get subordinates of the employee
  vector<EmployeeRole*>& getSubordinates() { return subordinates; }

 private:
  string jobFunction{""};
  EmployeeRole* supervisor{nullptr};
  vector<EmployeeRole*> subordinates{};
  vector<SpecificFlight*> specific_flights{};
};

#endif /* EMPLOYEE_ROLE_H */
