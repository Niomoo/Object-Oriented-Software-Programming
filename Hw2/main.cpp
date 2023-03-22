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
    Person(string name, Gender gender)
      : name_(name), gender_(gender) {};
    string getName() const { return name_; }
    Gender getGender() const { return gender_; }
};

class BoardOfDirectors : public Person {
  private:
    vector<Person *> memberList_;
    Company *company_{ nullptr };
  public:
    BoardOfDirectors(string name, Gender gender) 
      : Person{name, gender} {};
    void setCompany(Company *company) { company_ = company; };
    Company* getCompany() { return company_; };
    void setBoardMember(vector<Person *> & p) { 
      if(p.size() >= 3 && p.size() <= 8) {
        cout << "Board members successfully added!";
        memberList_ = p;
      } else {
        cout << "The number of Board members is not accepted!";
      }
     };
    int getDirectorsCount() { return memberList_.size(); };
};

class Employee : public Person
{
  protected:
    int id_;
    Position position_;
    Company *worksFor_{nullptr};
    Office *allocatedTo_{nullptr};

  public:
    Employee(string name, Gender gender, int id, Position position)
        : Person{name, gender}, id_(id), position_(position){};
    void setWorksFor(Company *company) { worksFor_ = company; }
    void setAllocatedTo(Office *office) { allocatedTo_ = office; }
    int getID() const { return id_; }
    Position getPosition() const { return position_; }
    Company *getWorksFor() const { return worksFor_; }
    Office *getAllocatedTo() const { return allocatedTo_; }
};

class Manager : public Employee
{
  private:
    vector<AdministrativeAssistant*> assistantList_;
  public:
    Manager(string name, Gender gender, int id)
        : Employee{name, gender, id, Position::Manager} {};
    void addAssistant(AdministrativeAssistant* a) {
      assistantList_.emplace_back(a);
    }
    vector<AdministrativeAssistant*> getAssistantList() const { return assistantList_; }
};

class AdministrativeAssistant : public Employee
{
  private:
    vector<Manager*> managerList_;
  public:
    AdministrativeAssistant(string name, Gender gender, int id, Manager* manager)
      : Employee{name, gender, id, Position::AdministrativeAssistant}, managerList_{manager} {
        manager -> addAssistant(this);
      };
    void addManager(Manager* m) { 
      managerList_.emplace_back(m);
      m -> addAssistant(this); 
    }
    vector<Manager*> getManager() const { return managerList_; }
};

class Company
{
  private:
    string name_;
    vector<Employee *> employeeList_;
    BoardOfDirectors director_;

  public:
    Company(string name, BoardOfDirectors director)
      : name_(name), director_(director) {};
    string getName() { return name_; }
    void addEmployee(Employee *employee) { 
      employeeList_.emplace_back(employee); 
      employee -> setWorksFor(this);
    }
    int getEmployeesCount() { return employeeList_.size(); }
    void setBoardOfDirectors(BoardOfDirectors b) {
      b.setCompany(this);
    }
    vector<Employee *> getInfo(int id) {
      vector<Employee *> result;
      for(Employee * e : employeeList_) {
        if(e -> getID() == id) result.emplace_back(e);
      }
      return result;
    }
    vector<Employee *> getInfo(Gender gender)
    {
      vector<Employee *> result;
      for (Employee *e : employeeList_)
      {
        if (e -> getGender() == gender) result.emplace_back(e);
      }
      return result;
    }
    vector<Employee *> getInfo(Position position)
    {
      vector<Employee *> result;
      for (Employee *e : employeeList_)
      {
        if (e -> getPosition() == position) result.emplace_back(e);
      }
      return result;
    }
};

class Office
{
  private:
    string name_;
    vector<Employee *> employeeList_;

  public:
    Office(string name) : name_(name) {};
    string getName() const { return name_; }
    void addEmployee(Employee* e) {
      employeeList_.emplace_back(e);
      e -> setAllocatedTo(this);
    }
    vector<Employee *> getEmployees() const { return employeeList_; }
};
