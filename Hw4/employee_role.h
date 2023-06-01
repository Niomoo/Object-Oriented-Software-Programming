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
  EmployeeRole(string jobFunction) : jobFunction{ jobFunction } {}

  // return the job of the employee
  string getJobFunction() { return jobFunction; }


 private:
  string jobFunction{""};
  vector<SpecificFlight*> specific_flights{};
};

#endif /* EMPLOYEE_ROLE_H */
