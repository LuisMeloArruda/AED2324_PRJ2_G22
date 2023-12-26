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
        }
    }
}

int App::menu() {
    int choice;
    // Print Menu
    cout << "\nChoose an option:"
            "\n0. Exit"
            "\n1. Statistics"
    << "\nYour option:";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 1)) {
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
            "\n9. Top-k airport with the greatest air traffic capacity"
            "\nYour option:";
    cin >> choice;
    cout << endl;

    // Check if option is valid
    while(!isValidOption(choice, 9)) {
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
            checkTopKAirport();
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

    information.getFlightsInCity(city);
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

    information.getCountriesCity(city);
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
