#ifndef PERSON_H
#define PERSON_H

#include <initializer_list>
#include <iostream>
#include <string>
#include <vector>

#include "airline.h"
#include "employee_role.h"
#include "passenger_role.h"
#include "person_role.h"
#include "specific_flight.h"

using namespace std;

/**
 * @brief class of Person
 * @param name - name of the person
 * @param idNumber - ID of the person
 * @param Airline - airline system of the person
 * @param roles - role of the person, each person may have 0 to 2 roles
*/
class Person {
 public:

  // constructor
  Person(string name, string idNumber, Airline* airline,
         initializer_list<PersonRole*> roles)
      : name{ name }, idNumber{ idNumber } {
    if (airline != nullptr) {
      linkAirline(airline);
    }
    for (auto& p : roles) {
      this->addPersonRole(p);
    }
  }
  Person(string name, string idNumber)
      : Person{name, idNumber, nullptr, {}} {}
  Person(string name, string idNumber,
         initializer_list<PersonRole*> roles)
      : Person{name, idNumber, nullptr, roles} {}
  ~Person() {
    for (auto& p : roles) {
      delete p;
    }
  }

  // return the person name 
  string getName() const { return name; }
  
  // return the person id number
  string getIdNumber() const { return idNumber; }

  // return the employee role of the person
  EmployeeRole* get_employee_role() {
    for (auto role : roles) {
      EmployeeRole* emp = dynamic_cast<EmployeeRole*>(role);
      if (emp != nullptr) {
        return emp;
      }
    }
    cerr << name << " does not have an EmployeeRole" << endl;
    return nullptr;
  }

  // return the passenger role of the person
  PassengerRole* get_passenger_role() {
    for (auto role : roles) {
      PassengerRole* pas = dynamic_cast<PassengerRole*>(role);
      if (pas != nullptr) {
        return pas;
      }
    }
    cerr << name << " does not have an EmployeeRole" << endl;
    return nullptr;
  }

  // add person role to the person
  void addPersonRole(PersonRole* person_role) {
    if (roles.size() > 2) {
      cerr << "PersonRole should not more than 2" << endl;
      return;
    }
    roles.push_back(person_role);
    person_role->linkPerson(this);
  }

  //link airline to the person
  void linkAirline(Airline* airline) {
    this->airline = airline;
    airline->addPerson(this);
  }

 private:
  string name;
  string idNumber;
  vector<PersonRole*> roles{};
  Airline* airline{nullptr};
};

#endif /* PERSON_H */
