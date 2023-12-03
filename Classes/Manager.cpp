#include <sstream>
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
        int weight = airline[0] + airline[1] + airline[2];

       if(!network.addEdge(sourceAirport, targetAirport, weight)) {
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
