#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
#include <vector>

using namespace std;

class SpecificFlight;

/**
 * @brief class of Airplane
 * @param airplane - name of the airplane
 */
class Airplane {
public:
  // constructor
  Airplane(string airplane) : airplane {airplane} { }

  string getAirplane() { return airplane; }
  vector<SpecificFlight *> getSpecificFlights() { return specificFlights; }
  
  // link to specificFlight
  void addLinkToSpecificFlight(SpecificFlight *flight)
  {
    specificFlights.push_back(flight);
  }

  // delete the link to specificFlight
  void deleteLinkToSpecificFlight(SpecificFlight *flight)
  {
    for(auto i = specificFlights.begin(); i != specificFlights.end(); ++i) {
      if(*i == flight) {
        specificFlights.erase(i);
        break;
      }
    }
  }

private:
  string airplane;
  vector<SpecificFlight *> specificFlights;
};

#endif /* AIRPLANE_H */
