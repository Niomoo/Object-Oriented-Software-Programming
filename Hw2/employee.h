#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>

#include "general.h"
#include "person.h"

using namespace std;

class Company;
class Office;

/**
 * @brief class for Employee inherited from Person class
 * @param name employee name
 * @param gender gender
 * @param id id number of the employee
 * @param position the working position of the employee
*/
class Employee : public Person
{
  protected:
    int id_;                            // id number
    Position position_;                 // position of the employee
    Company *worksFor_{nullptr};        // the company that the employee works for
    Office *allocatedTo_{nullptr};       // the office that the employee allocated to

  public:
    // constructor
    Employee(string name, Gender gender, int id, Position position)
      : Person{name, gender}, id_(id), position_(position){};
    
    // set the company of the employee works for
    void setWorksFor(Company *company) { worksFor_ = company; }

    // set the office of the employee allocated to
    void setAllocatedTo(Office *office) { allocatedTo_ = office; }

    // return the id number of the employee
    int getID() const { return id_; }

    // return the job position of the employee
    Position getPosition() const { return position_; }

    // return the company that the employee works for
    Company *getWorksFor() const { return worksFor_; }

    // return the office that the employee allocated to
    Office *getAllocatedTo() const { return allocatedTo_; }
};

#endif