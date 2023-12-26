#ifndef AED2324_PRJ2_G22_MANAGER_H
#define AED2324_PRJ2_G22_MANAGER_H

#include <set>
#include <list>
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
    void getDiameterPairs() const;
    void getTopKAirport(const int& K) const;
    void getEssentialAirports() const;
    void dfs_art(Vertex<Airport>* v, unordered_set<string>& essentialAirports, unsigned int index) const;

    // Auxiliary Functions
    void readAirlines();
    void readAirports();
    void readFlights();
    int getMaximumDistance(Vertex<Airport>* sourceVertex, list<pair<string, string>>& trips) const;
};

#endif //AED2324_PRJ2_G22_MANAGER_H
