#include "Manager.h"

/**
 * @brief Standard Constructor, sets all the attributes to their respective empty values
 * @details Time complexity: O(1)
 */
Manager::Manager() {
    airlines = set<Airline>();
}

void Manager::readFiles() {
    readAirlines();
    readAirports();
    readFlights();
}

void Manager::readAirlines() {
    fstream  file("../data/airlines.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        // Exracting Info
        istringstream ss(line);
        string code, name, callSign, country;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, callSign, ',');
        getline(ss, country, ',');

        Airline temp = Airline(code, name, callSign, country);

        airlines.insert(temp);
    }
}

void Manager::readAirports() {
    fstream  file("../data/airports.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        // Exracting Info
        istringstream ss(line);
        string code, name, city, country;
        getline(ss, code, ',');
        getline(ss, name, ',');
        getline(ss, city, ',');
        getline(ss, country, ',');
        double latitude, longitude;
        ss >> latitude;
        ss.ignore(1); // Ignore comma
        ss >> longitude;
        ss.ignore(1); // Ignore comma

        Airport temp = Airport(code, name, city, country, latitude, longitude);

        if (!network.addVertex(temp)) {
            cout << "SOMETHING WENT WRONG WITH AIRPORT WITH CODE " << code << endl;
        }
    }

}

void Manager::readFlights() {
    fstream  file("../data/flights.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore header

    while (getline(file, line)) {
        // Exracting Info
        istringstream ss(line);
        string source, target, airline;
        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, ',');

        Airport sourceAirport = Airport(source);
        Airport targetAirport = Airport(target);

       if(!network.addEdge(sourceAirport, targetAirport, airline)) {
           cout << "SOMETHING WENT WRONG ADDING EDGE FROM AIRPORT " << source << " TO AIRPORT " << target << endl;
       }

    }
}

int Manager::getAirportNumber() const {
    return network.getNumVertex();
}

int Manager::getGlobalFlightNumber() const {
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        count += airport->getAdj().size();
    }
    return count;
}

void Manager::getOutFlights(Airport airport) const {
    Vertex<Airport>* airportPtr = network.findVertex(airport);
    if (airportPtr == NULL) {
        cout << "Airport Code not found/valid" << endl;
        return;
    }
    unordered_set<string> airlineSet;
    int count = 0;
    for (Edge<Airport> edge : airportPtr->getAdj()) {
        auto it = airlineSet.insert(edge.getAirline());
        if (it.second) count++;
    }

    cout << "INFORMATION REGARDING AIRPORT " << airportPtr->getInfo().getName()
    << " WITH CODE " << airportPtr->getInfo().getCode() << endl;
    cout << "NUMBER OF FLIGHTS OUT: " << airportPtr->getAdj().size() << endl;
    cout << "FROM " << count << " DIFFERENT AIRLINES" << endl;
}

void Manager::getFlightsInCity(string city) const {
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        // If airport is outside target city then we only count flights that go into target city
        if (airport->getInfo().getCity() != city) {
            for (Edge<Airport> edge : airport->getAdj()) {
                if (edge.getDest()->getInfo().getCity() != city) continue;
                count++;
            }
            continue;
        }
        // Else then airport is inside the city and we count all its flights
        count += airport->getAdj().size();
    }

    cout << "INFORMATION REGARDING " << city << endl;
    cout << "NUMBER OF FLIGHTS THAT PASS TROUGH IT: " << count << endl;
}

void Manager::getFlightsOfAirline(string airline) const {
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        for (Edge<Airport> edge : airport->getAdj()) {
            if (edge.getAirline() == airline) count++;
        }
    }

    cout << "INFORMATION REGARDING AIRLINE " << airline << endl;
    cout << "NUMBER OF FLIGHTS PROVIDE BY IT: " << count << endl;
}

void Manager::getCountriesAirport(Airport airport) const {
    Vertex<Airport>* airportPtr = network.findVertex(airport);
    if (airportPtr == NULL) {
        cout << "Airport Code not found/valid" << endl;
        return;
    }
    unordered_set<string> countries;
    int count = 0;
    for (Edge<Airport> edge : airportPtr->getAdj()) {
        auto it = countries.insert(edge.getDest()->getInfo().getCountry());
        if (it.second) count++;
    }

    cout << "INFORMATION REGARDING AIRPORT " << airportPtr->getInfo().getName()
         << " WITH CODE " << airportPtr->getInfo().getCode() << endl;
    cout << "NUMBER OF COUNTRIES IT FLIES TO: " << count << endl;
}

void Manager::getCountriesCity(string city) const {
    unordered_set<string> countries;
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        if (airport->getInfo().getCity() != city) continue;
        for (Edge<Airport> edge : airport->getAdj()) {
            auto it = countries.insert(edge.getDest()->getInfo().getCountry());
            if (it.second) count++;
        }
    }

    cout << "INFORMATION REGARDING " << city << endl;
    cout << "NUMBER OF COUNTRIES IT HAS FLIGHTS TO: " << count << endl;
}

void Manager::getDestinations(Airport airport) const {
    Vertex<Airport>* airportPtr = network.findVertex(airport);
    if (airportPtr == NULL) {
        cout << "Airport Code not found/valid" << endl;
        return;
    }

    unordered_set<string> airports;
    unordered_set<string> cities;
    unordered_set<string> countries;
    int airportCount = 0, cityCount = 0, countryCount = 0;

    for (Edge<Airport> edge : airportPtr->getAdj()) {
        auto airportIt = airports.insert(edge.getDest()->getInfo().getCode());
        auto cityIt = cities.insert(edge.getDest()->getInfo().getCity());
        auto countryIt = countries.insert(edge.getDest()->getInfo().getCountry());

        if(airportIt.second) airportCount++;
        if(cityIt.second) cityCount++;
        if(countryIt.second) countryCount++;
    }

    cout << "INFORMATION REGARDING AIRPORT " << airportPtr->getInfo().getName()
         << " WITH CODE " << airportPtr->getInfo().getCode() << endl;
    cout << "NUMBER OF DESTINATION AIRPORTS: " << airportCount << endl;
    cout << "NUMBER OF DESTINATION CITIES: " << cityCount << endl;
    cout << "NUMBER OF DESTINATION COUNTRIES: " << countryCount  << endl;
}

void Manager::getTopKAirport(const int& K) const {
    // Create a vector to store airports and their flight counts
    vector<pair<Vertex<Airport>*, int>> airportFlightsCount;

    // Iterate over all airports and count their total flights
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        int flightCount = airport->getAdj().size();
        airportFlightsCount.push_back({airport, flightCount});
    }

    // Sort the vector based on flight counts in descending order
    sort(airportFlightsCount.begin(), airportFlightsCount.end(),
         [](const auto& a, const auto& b) {
             return a.second > b.second;
         });

    // Display the top K airports
    cout << "Top " << K << " Airports based on Flight Counts:\n";
    for (int i = 0; i < min(K, static_cast<int>(airportFlightsCount.size())); ++i) {
        Vertex<Airport>* airport = airportFlightsCount[i].first;
        int flightCount = airportFlightsCount[i].second;

        cout << i+1 << ". " << airport->getInfo().getName()
             << " (" << airport->getInfo().getCode() << ") "
             << " -  Number of flights: " << flightCount << endl;
    }
}


void Manager::getReachableDestinations(const Airport& startAirport, int maxStops) const {
    // Find the starting vertex in the graph using the provided airport information
    Vertex<Airport>* startVertex = network.findVertex(startAirport);

    // Check if the starting airport is found in the graph
    if (startVertex == nullptr) {
        cout << "Airport Code not found/valid" << endl;
        return;
    }

    // Initialize sets to keep track of visited airports, cities, and countries
    unordered_set<string> visitedAirports;
    unordered_set<string> visitedCities;
    unordered_set<string> visitedCountries;

    // Perform DFS to find reachable destinations with the given maximum stops
    dfsReachableDestinations(startVertex, maxStops, 0, visitedAirports, visitedCities, visitedCountries);

    // Display the results
    cout << "Reachable destinations from "
         << startAirport.getCode()
         << " with a maximum of "
         << maxStops << " stop(s):" << endl;

    cout << "Airports: " << visitedAirports.size() << endl;
    cout << "Cities: " << visitedCities.size() << endl;
    cout << "Countries: " << visitedCountries.size() << endl;
}

void Manager::dfsReachableDestinations(Vertex<Airport>* currentVertex,
                                       int maxStops, int currentStops,
                                       unordered_set<string>& visitedAirports,
                                       unordered_set<string>& visitedCities,
                                       unordered_set<string>& visitedCountries) const {

    // Mark the current airport, city, and country as visited
    visitedAirports.insert(currentVertex->getInfo().getCode());
    visitedCities.insert(currentVertex->getInfo().getCity());
    visitedCountries.insert(currentVertex->getInfo().getCountry());

    // Base case: If the maximum stops are reached, stop the recursion
    if (currentStops == maxStops) {
        return;
    }

    // Explore neighboring airports recursively
    for (const Edge<Airport>& edge : currentVertex->getAdj()) {
        Vertex<Airport>* neighborVertex = edge.getDest();

        // Check if the neighbor airport is not visited to avoid cycles
        if (visitedAirports.find(neighborVertex->getInfo().getCode()) == visitedAirports.end()) {
            dfsReachableDestinations(neighborVertex, maxStops, currentStops + 1,
                                     visitedAirports, visitedCities, visitedCountries);
        }
    }
}
