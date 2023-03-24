#ifndef MANAGER_H
#define MANAGER_H

#include <stdio.h>
#include <vector>
#include <string>

#include "general.h"
#include "employee.h"

using namespace std;

class AdministrativeAssistant;

/**
 * @brief class for Manager inherited from Employee class
 * @param name manager name
 * @param gender gender
 * @param id id number of the manager
 */
class Manager : public Employee
{
  private:
    vector<AdministrativeAssistant *> assistantList_{}; // list of administrative assistants

  public:
    // constructor
    Manager(string name, Gender gender, int id)
      : Employee{name, gender, id, Position::Manager} {};

    // add an assistant to the manager
    void addAssistant(AdministrativeAssistant *a)
    {
      assistantList_.emplace_back(a);
    }

    // get the list of all assistants
    vector<AdministrativeAssistant *> getAssistantList() const { return assistantList_; }
};

#endif