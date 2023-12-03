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
    bool statistics() const;

    // Lookup functions
    void checkGlobal() const;
    void checkOutFlights() const;
    void checkFlightsInCity() const;
    void checkFlightsOfAirline() const;
    void checkCountriesAirport() const;
    void checkCountriesCity() const;
    void checkDestinations() const;

    // Auxiliary Functions
    static bool isValidOption(int choice, int numberOfOptions);
    static bool continueQuestion();

private:
    /** @brief Extractor object which keeps all students, schedules, requests and their functions */
    Manager information;
};

#endif //AED2324_PRJ1_G22_APP_H
