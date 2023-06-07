#ifndef BOOKING_H
#define BOOKING_H

class SpecificFlight;
class PassengerRole;

/**
 * @brief class of Booking
 * @param passenger - passenger who makes the booking
 * @param flight - specificFlight of the booking
*/
class Booking {
 public:
  // constructor
  Booking(PassengerRole* passenger, SpecificFlight* flight, int seatNumber) {
    this->passenger = passenger;
    this->flight = flight;
    this->seatNumber = seatNumber;
  }

  PassengerRole* getPassengerRole() const { return passenger; }
  SpecificFlight* getSpecificFlight() const { return flight; }
  int getSeatNumber() const { return seatNumber; }


 private:
  int seatNumber;
  PassengerRole* passenger{nullptr};
  SpecificFlight* flight{nullptr};
};

#endif /* BOOKING_H */
