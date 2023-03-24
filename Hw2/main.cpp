#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include "general.h"
#include "company.h"
#include "office.h"
#include "employee.h"
#include "director.h"
#include "manager.h"
#include "assistant.h"

using namespace std;

int main()
{
  /*---------- Relation 1 ----------*/
  /* create Company */
  auto google = new Company("Google");

  /** create Employees
   *  each employee belongs to a company
   */
  auto Amy = Employee("Amy", Gender::F, 15342, Position::JuniorEngineer);
  auto Tony = Employee("Tony", Gender::M, 15343, Position::JuniorEngineer);
  auto Jackson = Employee("Jackson", Gender::M, 15344, Position::JuniorEngineer);
  auto Louis = Employee("Louis", Gender::M, 15355, Position::SeniorEngineer);
  auto Kelly = Employee("Kelly", Gender::F, 15356, Position::SeniorEngineer);

  /** add relation:
   *  add employee to the company 
   */
  google->addEmployee(&Amy);
  google->addEmployee(&Tony);
  google->addEmployee(&Jackson);
  google->addEmployee(&Louis);
  google->addEmployee(&Kelly);

  /* print result */
  cout << "<<Relation 1>>" << endl;
  cout << "Number of employees: " << google->getEmployeesCount() << endl;
  cout << "Amy works for " << Amy.getWorksFor()->getName() << endl;
  cout << "Jackson works for " << Jackson.getWorksFor()->getName() << endl;
  
  /* show more information of the employee */
  cout << "Female in Google:";
  auto engineersF = google->getInfo(Gender::F);
  for (auto e : engineersF)
  {
    cout << " " << e->getName();
  }
  cout << endl;
  cout << "Male in Google:";
  auto engineersM = google->getInfo(Gender::M);
  for (auto e : engineersM)
  {
    cout << " " << e->getName();
  }
  cout << endl;

  cout << "Junior Engineer in Google:";
  auto engineersJ = google->getInfo(Position::JuniorEngineer);
  for (auto e : engineersJ)
  {
    cout << " " << e->getName();
  }
  cout << endl;

  cout << "Senior Engineer in Google:";
  auto engineersS = google->getInfo(Position::SeniorEngineer);
  for (auto e : engineersS)
  {
    cout << " " << e->getName();
  }
  cout << endl;


  /*---------- Relation 2 ----------*/
  /* create Manager */
  auto Jessica = new Manager("Jessica", Gender::F, 24653);
  auto Charlie = new Manager("Charlie", Gender::M, 24654);
  auto Chris = new Manager("Chris", Gender::M, 24655);
  auto Tina = new Manager("Tina", Gender::F, 24656);

  /** create AdministrativeAssistant 
   *  each assistant have at least one manager
   */
  auto Eva = new AdministrativeAssistant("Eva", Gender::F, 24787, Jessica);
  auto Bob = new AdministrativeAssistant("Bob", Gender::M, 24788, Charlie);
  auto Tom = new AdministrativeAssistant("Tom", Gender::M, 24789, Jessica);

  /** add relation: 
   *  assign additional manager to some assistants
   */
  dynamic_cast<AdministrativeAssistant *>(Eva)->addManager(Tina);
  dynamic_cast<AdministrativeAssistant *>(Tom)->addManager(Charlie);

  /* print result */
  cout << "\n\n<<Relation 2>>" << endl;
  cout << "The subordinate of Jessica:";
  for(auto a : dynamic_cast<Manager *>(Jessica) -> getAssistantList()) {
    cout << " " << a->getName();
  }
  cout << endl;
  cout << "The subordinate of Charlie:";
  for (auto a : dynamic_cast<Manager *>(Charlie)->getAssistantList())
  {
    cout << " " << a->getName();
  }
  cout << endl;
  cout << "The subordinate of Chris:";
  for (auto a : dynamic_cast<Manager *>(Chris)->getAssistantList())
  {
    cout << " " << a->getName();
  }
  cout << endl;
  cout << "The subordinate of Tina:";
  for (auto a : dynamic_cast<Manager *>(Tina)->getAssistantList())
  {
    cout << " " << a->getName();
  }
  cout << endl;
  cout << "The supervisor of Eva:";
  for(auto m : dynamic_cast<AdministrativeAssistant *>(Eva) -> getManager()) {
    cout << " " << m->getName();
  }
  cout << endl;
  cout << "The supervisor of Bob:";
  for (auto m : dynamic_cast<AdministrativeAssistant *>(Bob)->getManager())
  {
    cout << " " << m->getName();
  }
  cout << endl;
  cout << "The supervisor of Tom:";
  for (auto m : dynamic_cast<AdministrativeAssistant *>(Tom)->getManager())
  {
    cout << " " << m->getName();
  }
  cout << endl;


  /*---------- Relation 3 ----------*/
  /* create Company */
  auto apple = new Company("Apple");
  auto microsoft = new Company("Microsoft");
  auto nvidia = new Company("Nvidia");

  /** create BoardOfDirector
   *  each company has only one board of director
   */
  vector<Person *> a;
  a.push_back(new Person("Jobs", Gender::M));
  auto Jobs = new BoardOfDirectors(a);
  vector<Person *> b;
  b.push_back(new Person("Satya", Gender::M));
  auto Satya = new BoardOfDirectors(b);
  vector<Person *> c;
  c.push_back(new Person("Jensen", Gender::M));
  auto Jensen = new BoardOfDirectors(c);

  /** add relation:
   *  assign board of director to the company
   */
  Jobs->setCompany(apple);
  Satya->setCompany(microsoft);
  Jensen->setCompany(nvidia);

  /* print result */
  cout << "\n\n<<Relation 3>>" << endl;
  cout << "The company of director Jobs: ";
  cout << Jobs->getCompany()->getName() << endl;
  cout << "The company of director Satya: ";
  cout << Satya->getCompany()->getName() << endl;
  cout << "The company of director Jensen: ";
  cout << Jensen->getCompany()->getName() << endl;

  /*---------- Relation 4 ----------*/
  /* create Office */
  auto Taipei = new Office("Taipei");
  auto NewYork = new Office("NewYork");
  auto Paris = new Office("Paris");

  /** add relation:
   *  assign employees to the office
   */
  Taipei->addEmployee(&Tony);
  Taipei->addEmployee(&Kelly);
  NewYork->addEmployee(&Jackson);
  Paris->addEmployee(&Louis);

  /* print result */
  cout << "\n\n<<Relation 4>>" << endl;
  cout << "The employees allocated to Taipei:";
  auto engineersT = Taipei->getEmployees();
  for (auto e : engineersT)
  {
    cout << " " << e->getName();
  }
  cout << endl;
  cout << "The employees allocated to NewYork:";
  auto engineersN = NewYork->getEmployees();
  for (auto e : engineersN)
  {
    cout << " " << e->getName();
  }
  cout << endl;
  cout << "The employees allocated to Paris:";
  auto engineersP = Paris->getEmployees();
  for (auto e : engineersP)
  {
    cout << " " << e->getName();
  }
  cout << endl;
  for (auto e : {Amy, Tony, Jackson, Louis, Kelly})
  {
    if (e.getAllocatedTo() != nullptr) {
      cout << e.getName() << " is in " << e.getAllocatedTo()->getName() << ".\n"; 
    }
    else cout << e.getName() << " is not allocated to any office.\n";
  }

  /*---------- Relation 5 ----------*/
  /* create Person */
  vector<Person *> p;
  p.push_back(new Person("Sam", Gender::M));
  p.push_back(new Person("Mary", Gender::F));
  p.push_back(new Person("Jenny", Gender::F));
  p.push_back(new Person("Oliver", Gender::M));
  p.push_back(new Person("Patty", Gender::F));

  /* create BoardOfDirector */
  auto TSMC = new BoardOfDirectors(p);

  /* print result */
  cout << "\n\n<<Relation 5>>" << endl;
  cout << "The board members of TSMC are:";
  auto members = TSMC->getDirectors();
  for (auto m : members)
  {
    cout << " " << m->getName();
  }
  cout << endl;
  cout << "The numbers of board members: " << TSMC->getDirectorsCount() << endl;

  return 0;
}