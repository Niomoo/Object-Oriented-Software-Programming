#ifndef OFFICE_H
#define OFFICE_H

#include <stdio.h>
#include <vector>
#include <string>

#include "employee.h"

using namespace std;

/**
 * @brief class for Office
 * @param location location of the office
*/
class Office
{
  private:
    string name_;                          // location of the office
    vector<Employee *> employeeList_;      // list of employees that allocated to the office

  public:
    // constructor
    Office(string name) : name_(name){};
    
    // return the location of the office
    string getName()  { return name_; }

    // allocate an employee to the office
    void addEmployee(Employee *e)
    {
      employeeList_.emplace_back(e);
      e->setAllocatedTo(this);
    }

    // return the list of employees that allocated to the office
    vector<Employee *> getEmployees() const { return employeeList_; }
};

#endif