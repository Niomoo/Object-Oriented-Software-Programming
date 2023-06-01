#ifndef FLIGHTLOG_H
#define FLIGHTLOG_H

class PassengerRole;
class SpecificFlight;

class FlightLog {
public:
    FlightLog(SpecificFlight *flight)
    {
        this->flightNumber = flight->flightNumber;
        this->origin = flight->origin;
        this->destination = flight->destination;
        this->departureTime = flight->departureTime;
        this->arrivalTime = flight->arrivalTime;
        this->airplane = flight->airplane;
        this->specificFlight = flight;
    }

private:
    string flightNumber;
    string origin;
    string destination;
    string departureTime;
    string arrivalTime;
    Airplane *airplane;
    SpecificFlight *specificFlight;
};

#endif /* FLIGHTLOG_H */
