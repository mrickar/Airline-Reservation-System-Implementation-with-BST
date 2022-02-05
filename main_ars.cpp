#include <iostream>

#include "AirlineReservationSystem.h"
// g++ AirlineReservationSystem.cpp main_ars.cpp Passenger.cpp Ticket.cpp Flight.cpp -o b
int main()
{
    AirlineReservationSystem ars;

    ars.addPassenger("jack", "sophia");
    ars.addPassenger("archie", "rosie");
    ars.addPassenger("harry", "isabella");
    ars.addPassenger("oscar", "lily");
    ars.addPassenger("leo", "ivy");
    ars.addPassenger("kate", "sophia");
    ars.addPassenger("harry", "isabella");

    ars.addFlight("DS7020", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 100, 5);
    ars.addFlight("DS7030", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "Brussels", 200, 10);
    ars.addFlight("DS7040", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 200, 10);
    ars.addFlight("DS7050", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "Istanbul", 200, 10);
    ars.addFlight("DS7060", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "Rome", 200, 10);
    ars.addFlight("DS7070", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "Amsterdam", 200, 10);
    ars.addFlight("DS7080", "20/12/2021 15:00", "20/12/2021 16:30", "Ankara", "London", 50, 0);

    ars.issueTicket("archie", "rosie", "DS7040", economy);
    ars.issueTicket("harry", "isabella", "DS7040", economy);
    ars.issueTicket("jack", "sophia", "DS7050", economy);
    ars.issueTicket("oscar", "lily", "DS7080", economy);
    ars.issueTicket("leo", "ivy", "DS7080", economy);
    ars.issueTicket("kate", "sophia", "DS7080", business);
    ars.print();
    ars.executeTheFlight("DS7080");
    ars.print();

    return 0;
}
