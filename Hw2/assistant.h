
#ifndef ASSISTANT_H
#define ASSISTANT_H

#include <stdio.h>
#include <vector>
#include <string>

#include "general.h"
#include "employee.h"
#include "manager.h"

using namespace std;

/**
 * @brief class for AdministrativeAssistant inherited from Employee class
 * @param name assistant name
 * @param gender gender
 * @param id id number of the employee
 * @param manager managers of the assistant
 */
class AdministrativeAssistant : public Employee
{
	private:
		vector<Manager *> managerList_; // list of managers

	public:
		// constructor
		AdministrativeAssistant(string name, Gender gender, int id, Manager *manager)
			: Employee{name, gender, id, Position::AdministrativeAssistant}, managerList_{manager}
		{
			manager->addAssistant(this);
		};

		// add a manager to the assistant
		void addManager(Manager *m)
		{
			managerList_.emplace_back(m);
			m->addAssistant(this);
		}

		// get the manager list of the assistant
		vector<Manager *> getManager() const { return managerList_; }
};

#endif