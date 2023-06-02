#ifndef FLIGHTLOG_H
#define FLIGHTLOG_H

class SpecificFlight;

class FlightLog {
public:
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
