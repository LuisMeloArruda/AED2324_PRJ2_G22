#ifndef AED2324_PRJ1_G22_APP_H
#define AED2324_PRJ1_G22_APP_H

#include "Manager.h"

/**
 * @brief The class which runs the program
 */
class App {
public:
    explicit App(const Manager &information);

    // Display functions
    void run();
    static int menu();
    bool statistics();
    bool scheduleFlight(bool minimumOn) const;

    // Lookup functions
    void checkGlobal() const;
    void checkOutFlights() const;
    void checkFlightsInCity() const;
    void checkFlightsOfAirline() const;
    void checkCountriesAirport() const;
    void checkCountriesCity() const;
    void checkDestinations() const;
    void checkReachableDestinations() const;
    void checkDiameter() const;
    void checkTopKAirport() const;
    void checkEssentialAirports();

    // Auxiliary Functions
    static bool isValidOption(int choice, int numberOfOptions);
    static bool continueQuestion();
    void getPath(bool withFilters, bool minimumON) const;
    list<string> getFilters() const;
    list<Vertex<Airport>*> askForAirport() const;
    list<Vertex<Airport> *> getAirportsByCode() const;
    list<Vertex<Airport> *> getAirportsByName() const;
    list<Vertex<Airport> *> getAirportsByCity() const;
    list<Vertex<Airport> *> getAirportsByCoordinates() const;

private:
    /** @brief Manager object which keeps information about airlines and network*/
    Manager information;
};

#endif //AED2324_PRJ1_G22_APP_H
