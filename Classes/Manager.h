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

/**
 * @brief The class which keeps information about airlines and network
 */
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
    void getFlightsInCity(string city, string country) const;
    void getFlightsOfAirline(string airline) const;
    void getCountriesAirport(Airport airport) const;
    void getCountriesCity(string city, string country) const;
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
    void getBestFlight(list<Vertex<Airport> *> list1, list<Vertex<Airport> *> list2) const;

    // Auxiliary Functions
    void dfsGetDestinations(Vertex<Airport> *v, int &airportCount, int &cityCount, int &countryCount,
                            unordered_set<string> &airports, set<pair<string, string>> &cities, unordered_set<string> &countries) const;
    void readAirlines();
    void readAirports();
    void readFlights();
    int getMaximumDistance(Vertex<Airport>* sourceVertex, list<pair<string, string>>& trips) const;
    void dfs_art(Vertex<Airport>* v, unordered_set<string>& essentialAirports, unsigned int index) const;
    list<Vertex<Airport> *> getAirportsByCode(string code) const;
    unsigned int getMinimumPath(Vertex<Airport>* source, Vertex<Airport>* target, list<list<pair<string, string>>>& options) const;
};

#endif //AED2324_PRJ2_G22_MANAGER_H
