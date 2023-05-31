#  Object-Oriented Software Engineering - Hw4
## Problem
Design a flight booking system using object-oriented programming.
### Class Diagram
![](https://i.imgur.com/GRomGFN.png)
## Description
### Objects
- Airline
    - addPerson()
    - addRegularFlight()
    - getRegularFlight()
    - getPeople()
- Person
    - getName()
    - getIdNumber()
    - get_employee_role()
    - get_passenger_role()
    - addPersonRole()
    - linkAirline()
- PersonRole
    - linkPerson()
    - getPerson()
- EmployeeRole
    - getJubFunction()
    - addSubordinate()
    - addSupervisor()
    - linkSupervisor()
    - addSpecificFlight()
- PassengerRole
    - addBooking()
    - bookSpecificFlight()
    - printBookings()
    - cancelBooking()
- RegularFlight
    - getTime()
    - getFlightNumber()
    - getSpecificFlights()
    - addSpecificFlight()
    - linkAirline()
- SpecificFlight
    - getDate()
    - getRegularFlight()
    - addBooking()
    - linkRegularFlight()
    - addEmployeeRole()
    - cancelBooking()


## Results
### Flight details
![](https://i.imgur.com/OLfzXmJ.png)
### Employee details
![](https://i.imgur.com/ZI3BWOi.png)
### Booking details
![](https://i.imgur.com/j8YpTD3.png)
