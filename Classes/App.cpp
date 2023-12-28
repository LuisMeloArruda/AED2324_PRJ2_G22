#include "App.h"
#include "Manager.h"
#include <iostream>

using namespace std;

/**
 * @brief Constructor of class App, it sets the Extractor Object to the given information
 * @param information
 */
App::App(const Manager &information) {
    this->information = information;
}

/**
 * @brief Method the runs the program, it calls the menu and the read files fuctions
 */
void App::run() {
    information.readFiles();
    while (true) {
        int choice = menu();

        switch (choice) {
            case 0:
                return;
            case 1:
                if (statistics()) break;
                if (continueQuestion()) return;
                break;
            case 2:
                if (scheduleFlight(false)) break;
                if (continueQuestion()) return;
                break;
        }
    }
}

int App::menu() {
    int choice;
    // Print Menu
    cout << "\nChoose an option:"
            "\n0. Exit"
            "\n1. Statistics"
            "\n2. Schedule Flight"
    << "\nYour option:";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 2)) {
        cout << "\nYour option:";
        cin >> choice;
    }
    return choice;
}

bool App::statistics() const {
    // Print Menu
    int choice;
    cout << "\nChoose an option:"
            "\n0. Go Back"
            "\n1. Global number of airports and flights"
            "\n2. Number of flights out of an airport"
            "\n3. Number of flights per city"
            "\n4. Number of flights of airline"
            "\n5. Number of countries an airport flies to"
            "\n6. Number of countries a city has flights to"
            "\n7. Number of destinations of an airport"
            "\n8. Number of reachable airports given the number of stops"
            "\n9. Maximum distance (maximum number of lay-overs) between two airports"
            "\n10. Top-k airport with the greatest air traffic capacity"
            "\n11. List essential airports to the network's circulation capability"
            "\nYour option:";
    cin >> choice;
    cout << endl;

    // Check if option is valid
    while(!isValidOption(choice, 11)) {
        cout << "\nYour option:";
        cin >> choice;
    }

    // Call correct lookup function
    switch (choice) {
        case 0:
            break;
        case 1:
            checkGlobal();
            break;
        case 2:
            checkOutFlights();
            break;
        case 3:
            checkFlightsInCity();
            break;
        case 4:
            checkFlightsOfAirline();
            break;
        case 5:
            checkCountriesAirport();
            break;
        case 6:
            checkCountriesCity();
            break;
        case 7:
            checkDestinations();
            break;
        case 8:
            checkReachableDestinations();
            break;
        case 9:
            checkDiameter();
            break;
        case 10:
            checkTopKAirport();
            break;
        case 11:
            checkEssentialAirports();
            break;
    }
    return (choice == 0);
}

bool App::scheduleFlight(bool minimumOn) const {
    // Print Menu
    int choice;
    cout << "\nChoose an option:"
            "\n0. Go Back"
            "\n1. Enable/Disable the minimum number of preferred airlines."
            "\n2. Without Filters"
            "\n3. With Filters"
            "\nYour option:";
    cin >> choice;
    cout << endl;

    // Check if option is valid
    while(!isValidOption(choice, 3)) {
        cout << "\nYour option:";
        cin >> choice;
    }

    // Call correct lookup function
    switch (choice) {
        case 0:
            break;
        case 1:
            if (minimumOn) scheduleFlight(false);
            else scheduleFlight(true);
            break;
            break;
        case 2:
            getPath(false, minimumOn);
            break;
        case 3:
            getPath(true, minimumOn);
            break;
    }
    return (choice == 0);
}

void App::checkGlobal() const {
    cout << "GLOBAL NUMBER OS AIRPORTS: "  << information.getAirportNumber() << endl;
    cout << "GLOBAL NUMBER OF FLIGHTS: " << information.getGlobalFlightNumber() << endl;
}

void App::checkOutFlights() const {
    cout << "Please insert wanted Airport code:";
    string code;
    cin >> code;
    Airport temp = Airport(code);

    information.getOutFlights(temp);
}

void App::checkFlightsInCity() const {
    cout << "Please insert wanted City:";
    string city;
    cin >> city;
    cout << "Please insert wanted country:";
    string country;
    cin >> country;

    information.getFlightsInCity(city, country);
}

void App::checkFlightsOfAirline() const {
    cout << "Please insert wanted Airline code:";
    string airline;
    cin >> airline;

    information.getFlightsOfAirline(airline);
}

void App::checkCountriesAirport() const {
    cout << "Please insert wanted Airport code:";
    string code;
    cin >> code;
    Airport temp = Airport(code);

    information.getCountriesAirport(temp);
}

void App::checkCountriesCity() const {
    cout << "Please insert wanted City:";
    string city;
    cin >> city;
    cout << "Please insert wanted Country:";
    string country;
    cin >> country;

    information.getCountriesCity(city, country);
}

void App::checkDestinations() const {
    cout << "Please insert wanted Airport code:";
    string code;
    cin >> code;
    Airport temp = Airport(code);

    information.getDestinations(temp);
}

void App::checkReachableDestinations() const {
    cout << "Please insert wanted Airport code:";
    string code;
    cin >> code;
    Airport temp = Airport(code);
    cout << "Please insert the number of stops:";
    int stops;
    cin >> stops;
    information.getReachableDestinations(temp, stops);
};

void App::checkDiameter() const {
    cout << "Searching the network" << endl;
    information.getDiameterPairs();
}

void App::checkTopKAirport() const {
    cout << "How many top airports do you want to retrieve? \n";
    int K;
    cin >> K;
    while (K <= 0) {
        cout << "The number needs to be higher than zero. Try again: \n";
        cin >> K;
    }
    if (K > 0) {
        information.getTopKAirport(K);
    }
}

void App::checkEssentialAirports() const {
    information.getEssentialAirports();
}

/**
 * @brief Method to test if the given input is within the range of possibilities
 * @details Time complexity: O(1)
 * @param choice user's input
 * @param numberOfOptions range of possibilities
 * @return true if user's input is within range, false otherwise
 */
bool App::isValidOption(int choice, int numberOfOptions) {
    if (cin.fail()) {
        throw invalid_argument("Invalid number");
    }
    if (choice < 0 || choice > numberOfOptions) {
        cout << "Invalid option." << endl;
        return false;
    }
    return true;
}

/**
 * @brief Method asking if the user wants to continue
 * @details Time complexity: O(1)
 * @return true if the user wants to end the program, false otherwise
 */
bool App::continueQuestion() {
    cout << "\nWanna Continue? [Y/N]: ";
    string answer;
    cin >> answer;
    if (answer == "N" || answer == "n") return true;
    return false;
}

void App::getPath(bool withFilters, bool minimumOn) const {
    list<Vertex<Airport>*> sourceAirports;
    list<Vertex<Airport>*> targetAirports;

    list<string> airlines;
    if (withFilters) airlines = getFilters();

    cout << "\nChose form of input for departure:";
    sourceAirports = askForAirport();
    cout << "\nChose form of input for arrival:";
    targetAirports = askForAirport();

    information.getBestFlight(sourceAirports, targetAirports, airlines, minimumOn);
    airlines.clear();
}

list<string> App::getFilters() const {
    list<string> airlines;
    cout << "Airline code:\n";
    string airline;
    cin >> airline;
    airlines.push_back(airline);
    while (!continueQuestion()) {
        cout << "Airline code:\n";
        cin >> airline;
        airlines.push_back(airline);
    }
    return airlines;
}

list<Vertex<Airport>*> App::askForAirport() const {
    int choice;
    cout << "\n0. Airport Code"
            "\n1. Airport Name"
            "\n2. City Name"
            "\n3. Geographical Coordinates"
            "\nYour option:";
    cin >> choice;
    cout << endl;

    // Check if option is valid
    while(!isValidOption(choice, 3)) {
        cout << "\nYour option:";
        cin >> choice;
    }

    // Call correct lookup function
    switch (choice) {
        case 0:
            return getAirportsByCode();
        case 1:
            return getAirportsByName();
        case 2:
            return getAirportsByCity();
        case 3:
            return getAirportsByCoordinates();
    }
}

list<Vertex<Airport> *> App::getAirportsByCode() const {
    cout << "Please insert wanted Airport code:";
    string code;
    cin >> code;

    return information.getAirportsByCode(code);
}

list<Vertex<Airport> *> App::getAirportsByName() const {
    cout << "Please insert wanted Airport name:";
    string name;
    cin >> name;

    return information.getAirportsByName(name);
}

list<Vertex<Airport> *> App::getAirportsByCity() const {
    cout << "Please insert wanted city name:";
    string city;
    cin >> city;
    cout << "Please insert wanted country name to avoid misunderstandings:";
    string country;
    cin >> country;

    return information.getAirportsByCity(city, country);
}

list<Vertex<Airport> *> App::getAirportsByCoordinates() const {
    cout << "Please insert wanted latitude coordinate:";
    double latitude;
    cin >> latitude;
    cout << "Please insert wanted longitude coordinate:";
    double longitude;
    cin >> longitude;

    return information.getAirportsByCoordinates(latitude, longitude);
}
