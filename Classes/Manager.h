#ifndef AED2324_PRJ2_G22_MANAGER_H
#define AED2324_PRJ2_G22_MANAGER_H

#include <set>
#include <queue>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
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
    void getDestinations(Airport airport) const;
    void getReachableDestinations(const Airport &startAirport, int stops) const;
    /*void dfsReachableDestinations(
            Vertex<Airport>* currentVertex,
            int maxStops, int currentStops,
            unordered_set<string>& visitedAirports,
            unordered_set<string>& visitedCities,
            unordered_set<string>& visitedCountries
    ) const;*/
    void getTopKAirport(const int& K) const;

    // Auxiliary Functions
    void readAirlines();
    void readAirports();
    void readFlights();
};

#endif //AED2324_PRJ2_G22_MANAGER_H
