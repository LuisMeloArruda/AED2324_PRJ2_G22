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
            "\nYour option:";
    cin >> choice;

    // Check if option is valid
    while(!isValidOption(choice, 1)) {
        cin >> choice;
    }

    // Call correct lookup function
    switch (choice) {
        case 0:
            break;
        case 1:
            checkGlobal();
            break;
    }
    return (choice == 0);
}

void App::checkGlobal() const {
    cout << "GLOBAL NUMBER OS AIRPORTS: "  << information.getAirportNumber() << endl;
    cout << "GLOBAL NUMBER OF FLIGHTS: " << information.getGlobalFlightNumber() << endl;
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