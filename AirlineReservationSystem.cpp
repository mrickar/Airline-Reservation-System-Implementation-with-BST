#include "AirlineReservationSystem.h"

void AirlineReservationSystem::addPassenger(const std::string &firstname, const std::string &lastname)
{
    /* TODO */

    if (searchPassenger(firstname, lastname))
    {
        return;
    }
    passengers.insert(Passenger(firstname, lastname));
}

Passenger *AirlineReservationSystem::searchPassenger(const std::string &firstname, const std::string &lastname)
{
    /* TODO */
    BSTNode<Passenger> *tmp = passengers.search(Passenger(firstname, lastname));
    if (tmp == NULL)
        return NULL;
    return &tmp->data;
}

void AirlineReservationSystem::addFlight(const std::string &flightCode, const std::string &departureTime, const std::string &arrivalTime, const std::string &departureCity, const std::string &arrivalCity, int economyCapacity, int businessCapacity)
{
    /* TODO */
    if (flights.search(Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity)))
    {
        return;
    }
    flights.insert(Flight(flightCode, departureTime, arrivalTime, departureCity, arrivalCity, economyCapacity, businessCapacity));
}

std::vector<Flight *> AirlineReservationSystem::searchFlight(const std::string &departureCity, const std::string &arrivalCity)
{
    /* TODO */
    std::vector<Flight *> vc;
    searchFlightHelper(departureCity, arrivalCity, vc, flights.getRoot());
    return vc;
}

void AirlineReservationSystem::issueTicket(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)
{
    /* TODO */
    Flight *wantedFlight = findFlightWithCode(flights.getRoot(), flightCode);
    if (!wantedFlight)
    {
        return;
    }
    Passenger *wantedPass = searchPassenger(firstname, lastname);
    if (!wantedPass)
    {
        return;
    }
    wantedFlight->addTicket(Ticket(wantedPass, wantedFlight, ticketType));
}

void AirlineReservationSystem::saveFreeTicketRequest(const std::string &firstname, const std::string &lastname, const std::string &flightCode, TicketType ticketType)
{
    /* TODO */
    Flight *wantedFlight = findFlightWithCode(flights.getRoot(), flightCode);
    if (!wantedFlight)
        return;
    Passenger *wantedPass = searchPassenger(firstname, lastname);
    if (!wantedPass)
        return;
    freeTicketRequests.enqueue(Ticket(wantedPass, wantedFlight, ticketType));
}

void AirlineReservationSystem::executeTheFlight(const std::string &flightCode)
{
    /* TODO */
    Flight *wantedFlight = findFlightWithCode(flights.getRoot(), flightCode);
    if (!wantedFlight)
        return;
    int sizeOfqueue = freeTicketRequests.size();
    for (int i = 0; i < sizeOfqueue; i++)
    {
        Ticket newTick = freeTicketRequests.dequeue();
        if (wantedFlight == newTick.getFlight() && wantedFlight->addTicket(newTick))
        {
            continue;
        }
        else
        {
            freeTicketRequests.enqueue(newTick);
        }
    }
    wantedFlight->setCompleted(true);
}

void AirlineReservationSystem::print() const
{
    std::cout << "# Printing the airline reservation system ..." << std::endl;

    std::cout << "# Passengers:" << std::endl;
    passengers.print(inorder);

    std::cout << "# Flights:" << std::endl;
    flights.print(inorder);

    std::cout << "# Free ticket requests:" << std::endl;
    freeTicketRequests.print();

    std::cout << "# Printing is done." << std::endl;
}
void AirlineReservationSystem::searchFlightHelper(const std::string &departureCity, const std::string &arrivalCity, std::vector<Flight *> &vc, BSTNode<Flight> *cur)
{

    if (cur == NULL)
        return;

    if (cur->data.getDepartureCity() == departureCity && cur->data.getArrivalCity() == arrivalCity)
    {
        vc.push_back(&(cur->data));
    }
    searchFlightHelper(departureCity, arrivalCity, vc, cur->left);
    searchFlightHelper(departureCity, arrivalCity, vc, cur->right);
}
Flight *AirlineReservationSystem::findFlightWithCode(BSTNode<Flight> *curNode, const std::string &flightCode)
{
    while (curNode)
    {
        if (flightCode == curNode->data.getFlightCode())
        {
            return &curNode->data;
        }
        else if (flightCode > curNode->data.getFlightCode())
        {
            curNode = curNode->right;
        }
        else
        {
            curNode = curNode->left;
        }
    }
    return NULL;
}