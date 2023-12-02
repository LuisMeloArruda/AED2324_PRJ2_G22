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
    //information.readFiles();
    //while (true) {
        //int choice = menu();

        //switch (choice) {
        //    case 0:
        //        return;
        //}
    //}
    cout << "Hello World" << endl;
}