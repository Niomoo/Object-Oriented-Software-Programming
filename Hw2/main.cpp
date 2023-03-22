#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "general.h"

using namespace std;

class Person
{
  protected:
    string name_;
    Gender gender_;

  public:
    Person(string name, Gender gender)::name_(name), gender_(gender) {}
    string getName() const { return name_; }
    Gender getGender() const { return gender_; }
}

class Employee::public Person
{
  protected:
    int id_;
    Position position_;
    Company *worksFor_{nullptr};
    Office *allocatedTo_{nullptr};

  public:
    Employee(string name, Gender gender, int id, Position position)::Person{name, gender}, id_(id), position_(position){};
    void setWorksFor(Company* company) { worksFor_ = company; }
    void setAllocatedTo(Office* office) { allocatedTo_ = office; }
    int getId() const { return id_; }
    Position getPosition() const { return position_; }
    Company getWorksFor() const { return worksFor_; }
    Office* getAllocatedTo() const { return allocatedTo_; }
}

class Manager::

class Company
{
  string name;

  public:
    Company(string);
    string getName() const;
}

Company::Company(string nameString)
{
  name = nameString;
}

string Company::getName() const
{
  return name;
}

class Office
{
  string name;

public:
  Office(string);
  string getName() const;
}

Office::Office(string nameString)
{
  name = nameString;
}

Office::getName() const
{
  return name;
}
