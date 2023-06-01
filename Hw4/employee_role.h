#ifndef EMPLOYEE_ROLE_H
#define EMPLOYEE_ROLE_H

#include <iostream>
#include <vector>

#include "specific_flight.h"

using namespace std;

/**
 * @brief class of EmployeeRole extends from PersonRole
 * @param jobFunction - job of the employee
 */
class EmployeeRole {
 public:

  // constructor
  EmployeeRole(string name) : name{ name } {}

  // return the job of the employee
  string getName() { return name; }


 private:
  string name;
  vector<SpecificFlight*> specific_flights{};
};

#endif /* EMPLOYEE_ROLE_H */
