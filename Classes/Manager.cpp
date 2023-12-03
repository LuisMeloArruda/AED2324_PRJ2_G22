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
