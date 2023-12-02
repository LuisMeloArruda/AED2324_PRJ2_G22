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

    // Lookup functions

    // Auxiliary Functions

private:
    /** @brief Extractor object which keeps all students, schedules, requests and their functions */
    Manager information;
};

#endif //AED2324_PRJ1_G22_APP_H
