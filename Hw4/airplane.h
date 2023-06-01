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
  void addLinkToSpecificFlight(SpecificFlight *flight)
  {
    specificFlights.push_back(flight);
  }
  void deleteLinkToSpecificFlight(SpecificFlight *flight)
  {
    specificFlights.remove(flight);
  }

private:
  string registrationNumber;
  string model;
  int seatCapacity;
  int bookedSeats;
  vector<SpecificFlight *> specificFlights;
};

#endif /* AIRPLANE_H */
