#ifndef AED2324_PRJ2_G22_MANAGER_H
#define AED2324_PRJ2_G22_MANAGER_H

#include <set>
#include <fstream>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include "Airline.h"
#include "Airport.h"
#include "Graph.h"

class Manager {
private:
    set<Airline> airlines;
    Graph<Airport> network;
public:
    Manager();
    void readFiles();

    // Lookup Functions
    int getAirportNumber() const;
    int getGlobalFlightNumber() const;
    void getOutFlights(Airport airport) const;
    void getFlightsInCity(string city) const;
    void getFlightsOfAirline(string airline) const;
    void getCountriesAirport(Airport airport) const;
    void getCountriesCity(string city) const;

    // Auxiliary Functions
    void readAirlines();
    void readAirports();
    void readFlights();
};

#endif //AED2324_PRJ2_G22_MANAGER_H
