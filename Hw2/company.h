#ifndef COMPANY_H
#define COMPANY_H

#include <stdio.h>
#include <vector>
#include <string>

#include "general.h"
#include "employee.h"
#include "director.h"

using namespace std;

class BoardOfDirectors;

/**
 * @brief class for Company
 * @param name company name
 * @param director director name of the director
*/
class Company
{
  private:
    string name_;                       // name of the company
    vector<Employee *> employeeList_;   // list of employees
    BoardOfDirectors director_;         // director of the company

  public:
    // constructor
    Company(string name)
        : name_(name){};
    
    // get the name of the company
    string getName() { return name_; }

    // add an employee to the company
    void addEmployee(Employee *employee)
    {
      employeeList_.emplace_back(employee);
      employee->setWorksFor(this);
    }

    // count the number of employees in the company
    int getEmployeesCount() { return employeeList_.size(); }

    // set the director of the company
    void setBoardOfDirectors(BoardOfDirectors b)
    {
      b.setCompany(this);
      director_ = b;
    }

    // return the director of the company
    BoardOfDirectors getBoardOfDirectors() { return director_; }

    // Polymorphism: get employee from the id filter
    vector<Employee *> getInfo(int id)
    {
      vector<Employee *> result;
      for (Employee *e : employeeList_)
      {
        if (e->getID() == id)
          result.emplace_back(e);
      }
      return result;
    }

    // Polymorphism: get employee from the gender filter
    vector<Employee *> getInfo(Gender gender)
    {
      vector<Employee *> result;
      for (Employee *e : employeeList_)
      {
        if (e->getGender() == gender)
          result.emplace_back(e);
      }
      return result;
    }

    // Polymorphism: get employee from the employee position
    vector<Employee *> getInfo(Position position)
    {
      vector<Employee *> result;
      for (Employee *e : employeeList_)
      {
        if (e->getPosition() == position)
          result.emplace_back(e);
      }
      return result;
    }
};

#endif