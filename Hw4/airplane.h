#ifndef AIRPLANE_H
#define AIRPLANE_H

#include <string>
#include <vector>

using namespace std;

class SpecificFlight;

/**
 * @brief class of Airline
 * @param name - name of the airline
 */
class Airplane {
public:
  Airplane(string airplane) : airplane {airplane} { }

  string getAirplane() { return airplane; }
  void addLinkToSpecificFlight(SpecificFlight *flight)
  {
    specificFlights.push_back(flight);
  }
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
