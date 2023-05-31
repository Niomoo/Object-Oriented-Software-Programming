#ifndef AIRLINE_H
#define AIRLINE_H

#include <string>
#include <vector>

using namespace std;

class Person;
class RegularFlight;

/**
 * @brief class of Airline
 * @param name - name of the airline
 */
class Airline {
 public:
  
  // constructor
  Airline(string name) : name{ name } {}
  
  // add person to the airline
  void addPerson(Person* person) { people.emplace_back(person); }

  // add regular flight to the airline
  void addRegularFlight(RegularFlight* reg_flight) {
    flights.emplace_back(reg_flight);
  }

  // return regular flight pf the airline
  vector<RegularFlight*>& getRegularFlights() { return flights; }

  // return the person list of the airline
  vector<Person*>& getPeople() { return people; }

 private:
  string name;
  vector<Person*> people{};
  vector<RegularFlight*> flights{};
};

#endif /* AIRLINE_H */
