#ifndef FLIGHTLOG_H
#define FLIGHTLOG_H

class SpecificFlight;

/**
 * @brief class of FlightLog
 * @param origin - origin of the flight
 * @param destination - destination of the flight
 * @param departureTime - departure time of the flight
 * @param arrivalTime - arrival time of the flight
*/
class FlightLog {
public:
    // constructor
    FlightLog(string origin, string destination, string departureTime, string arrivalTime)
    : origin{ origin }, destination{ destination }, departureTime{ departureTime }, arrivalTime{ arrivalTime }
    {}

    string getOrigin() { return origin; }
    string getDestination() { return destination; }
    string getDepartureTime() { return departureTime; }
    string getArrivalTime() { return arrivalTime; }
    
private:
    string origin;
    string destination;
    string departureTime;
    string arrivalTime;
};

#endif /* FLIGHTLOG_H */
