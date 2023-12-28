#include "Manager.h"

/**
 * @brief Standard Constructor, sets all the attributes to their respective empty values.
 * @details Time complexity: O(1)
 */
Manager::Manager() {
    airlines = set<Airline>();
}

/**
 * @brief Runs read methods and fills Manager's attributes.
 * @see readAirlines()
 * @see readAirports()
 * @see readFlights()
 */
void Manager::readFiles() {
    readAirlines();
    readAirports();
    readFlights();
}

/**
 * @brief Read the "airlines.csv" file and fills Manager's airlines with code, name, callSign and country.
 * @details Time complexity:
 */
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

/**
 * @brief Read the "airports.csv" file and fills Manager's network with code, name, city, country, latitude, longitude.
 * @details Time complexity:
 */
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

/**
 * @brief Read the "flights.csv" file and fill each Manager's network vertex with edges.
 * @details Time complexity:
 */
void Manager::readFlights() {
    fstream  file("../data/flights.csv");

    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
    }

    string line;
    getline(file, line); // Ignore header

    string previousSource = "";
    string previousTarget = "";

    while (getline(file, line)) {
        // Exracting Info
        istringstream ss(line);
        string source, target, airline;
        getline(ss, source, ',');
        getline(ss, target, ',');
        getline(ss, airline, ',');

        Airport sourceAirport = Airport(source);
        Airport targetAirport = Airport(target);

        Vertex<Airport> *v1 = nullptr;
        Vertex<Airport>* v2 = nullptr;

        if (previousSource != source) v1 = network.findVertex(sourceAirport);
        if (previousTarget != target) v2 = network.findVertex(targetAirport);

        v2->setInDegree(v2->getInDegree()+1);

        if(!network.addEdge(v1, v2, airline)) {
           cout << "SOMETHING WENT WRONG ADDING EDGE FROM AIRPORT " << source << " TO AIRPORT " << target << endl;
        }

    }
}

/**
 * @brief Returns the number of network's vertices.
 * @details Time complexity: O(1)
 * @return the number of network's vertices.
 */
int Manager::getAirportNumber() const {
    return network.getNumVertex();
}

/**
 * @brief Returns the number of network's flights.
 * @details Time complexity: O(n), where n is the number of vertices
 * @return the number of network's flights.
 */
int Manager::getGlobalFlightNumber() const {
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        count += airport->getAdj().size();
    }
    return count;
}

/**
 * @brief Search for outbound flights from a specified airport.
 * @details Time complexity:
 * @param airport The airport where we will search for outbound flights.
 */
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

/**
 * @brief Search for inbound and outbounds flights to a specified city.
 * @details Time complexity:
 * @param city The city where we will search for flights passing through it
 * @param country The country to avoid ambiguous searches
 */
void Manager::getFlightsInCity(string city, string country) const {
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        // If airport is outside target city then we only count flights that go into target city
        if (airport->getInfo().getCity() != city || airport->getInfo().getCountry() != country) {
            for (Edge<Airport> edge : airport->getAdj()) {
                if (edge.getDest()->getInfo().getCity() != city && edge.getDest()->getInfo().getCountry() != country) continue;
                count++;
            }
        }
        // Else then airport is inside the city, and we count all its flights
        else if (airport->getInfo().getCity() == city && airport->getInfo().getCountry() == country) {
            count += airport->getAdj().size();
        }
    }

    cout << "INFORMATION REGARDING " << city << endl;
    cout << "NUMBER OF FLIGHTS THAT PASS TROUGH IT: " << count << endl;
}

/**
 * @brief Provides the number of flights by a specified airline.
 * @details Time complexity:
 * @param airline The airline where we will search for flights.
 */
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

/**
 * @brief Provides the number of countries by a specified airport.
 * @details Time complexity:
 * @param airport The airport where we will search for countries.
 */
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

/**
 * @brief Provides the number of countries by a specified city.
 * @details Time complexity:
 * @param city
 * @param country
 */
void Manager::getCountriesCity(string city, string country) const {
    unordered_set<string> countries;
    int count = 0;
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        if (airport->getInfo().getCity() != city && airport->getInfo().getCountry() != country) continue;
        for (Edge<Airport> edge : airport->getAdj()) {
            auto it = countries.insert(edge.getDest()->getInfo().getCountry());
            if (it.second) count++;
        }
    }

    cout << "INFORMATION REGARDING " << city << endl;
    cout << "NUMBER OF COUNTRIES IT HAS FLIGHTS TO: " << count << endl;
}

/**
 * @brief Auxiliar depth-first search to count the number of airports, cities and countries for a vertice.
 * @details Time complexity:
 * @param v
 * @param airportCount
 * @param cityCount
 * @param countryCount
 * @param airports
 * @param cities
 * @param countries
 */
void Manager::dfsGetDestinations(Vertex<Airport> *v, int &airportCount, int &cityCount, int &countryCount,
                                 unordered_set<string> &airports, set<pair<string, string>> &cities, unordered_set<string> &countries) const {
    v->setVisited(true);
    for (Edge<Airport> edge : v->getAdj()) {
        auto airportIt = airports.insert(edge.getDest()->getInfo().getCode());
        pair<string, string> aux = make_pair(edge.getDest()->getInfo().getCity(), edge.getDest()->getInfo().getCountry());
        auto cityIt = cities.insert(aux);
        auto countryIt = countries.insert(edge.getDest()->getInfo().getCountry());

        if(airportIt.second)  {
            airportCount++;
            Vertex<Airport>* w = network.findVertex(edge.getDest()->getInfo());
            if (!w->isVisited()) dfsGetDestinations(w, airportCount, cityCount, countryCount,
                                                    airports, cities, countries);
        }
        if(cityIt.second) cityCount++;
        if(countryIt.second) countryCount++;
    }
}

/**
 * @brief Method to count the number of airports, cities and countries for a given airport.
 * @details Time complexity:
 * @param airport Given airport
 * @see dfsGetDestinations()
 */
void Manager::getDestinations(Airport airport) const {
    Vertex<Airport>* airportPtr = network.findVertex(airport);
    if (airportPtr == NULL) {
        cout << "Airport Code not found/valid" << endl;
        return;
    }
    for (Vertex<Airport> *v : network.getVertexSet()) {
        v->setVisited(false);
    }

    unordered_set<string> airports;
    set<pair<string, string>> cities;
    unordered_set<string> countries;
    int airportCount = 0, cityCount = 0, countryCount = 0;

    if (!airportPtr->isVisited()) dfsGetDestinations(airportPtr, airportCount, cityCount, countryCount,
                                                     airports, cities, countries);


    cout << "INFORMATION REGARDING AIRPORT " << airportPtr->getInfo().getName()
         << " WITH CODE " << airportPtr->getInfo().getCode() << endl;
    cout << "NUMBER OF DESTINATION AIRPORTS: " << airportCount << endl;
    cout << "NUMBER OF DESTINATION CITIES: " << cityCount << endl;
    cout << "NUMBER OF DESTINATION COUNTRIES: " << countryCount  << endl;
}

/**
 * @brief A method to count the number of airports, cities, and countries for a given airport within a limit
 * @details Time complexity:
 * @param startAirport Given airport
 * @param stops limit
 */
void Manager::getReachableDestinations(const Airport &startAirport, int stops) const {
    Vertex<Airport>* sourceVertex;

    // Initialize sets to keep track of visited airports, cities, and countries
    unordered_set<string> visitedAirports;
    set<pair<string, string>> visitedCities;
    unordered_set<string> visitedCountries;

    for (Vertex<Airport>* vertex : network.getVertexSet()) {
        vertex->setVisited(false);
        if (vertex->getInfo() == startAirport) sourceVertex = vertex;
    }

    queue<pair<Vertex<Airport>*, int>> vertexToVisit;
    vertexToVisit.push({sourceVertex, stops});

    while (!vertexToVisit.empty()) {
        Vertex<Airport>* currentVertex = vertexToVisit.front().first;
        // If node has alredy been visited then skip it
        if (currentVertex->isVisited()) {
            vertexToVisit.pop();
            continue;
        }
        // Mark node as visited and add to visited sets
        vertexToVisit.front().first->setVisited(true);
        visitedAirports.insert(currentVertex->getInfo().getCode());
        visitedCities.insert(make_pair(currentVertex->getInfo().getCity(), currentVertex->getInfo().getCountry()));
        visitedCountries.insert(currentVertex->getInfo().getCountry());
        // If node is last stop then don't add its adjacent to queue
        if (vertexToVisit.front().second == 0) {
            vertexToVisit.pop();
            continue;
        }
        for (Edge<Airport> edge: currentVertex->getAdj()) {
            vertexToVisit.push({edge.getDest(), vertexToVisit.front().second - 1});
        }
        vertexToVisit.pop();
    }

    // Display the results
    cout << "Reachable destinations from "
         << startAirport.getCode()
         << " with a maximum of "
         << stops << " stop(s):" << endl;

    cout << "Airports: " << visitedAirports.size() << endl;
    cout << "Cities: " << visitedCities.size() << endl;
    cout << "Countries: " << visitedCountries.size() << endl;
}

/*void Manager::getReachableDestinations(const Airport& startAirport, int maxStops) const {
    // Find the starting vertex in the graph using the provided airport information
    Vertex<Airport>* startVertex = network.findVertex(startAirport);

    // Set all nodes as unvisited
    for (Vertex<Airport>* vertex : network.getVertexSet()) {
        vertex->setVisited(false);
    }

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
    currentVertex->setVisited(true);
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
        if (!neighborVertex->isVisited()) {
            dfsReachableDestinations(neighborVertex, maxStops, currentStops + 1,
                                     visitedAirports, visitedCities, visitedCountries);
        }
    }
}*/

/**
 * @brief Prints the maximum trip and corresponding pair of source-destination airports
 * @details Time complexity:
 * @see getMaximumDistance();
 */
void Manager::getDiameterPairs() const {
    list<pair<string, string>> diameterPairs;
    unsigned int maximumDistance = 0;

    for (Vertex<Airport>* vertex : network.getVertexSet()) {
        list<pair<string, string>> tempPairs;
        int temp = getMaximumDistance(vertex, tempPairs);
        if (temp > maximumDistance) {
            maximumDistance = temp;
            diameterPairs = tempPairs;
        } else if (temp == maximumDistance) {
            diameterPairs.splice(diameterPairs.end(), tempPairs);
        }
    }

    cout << "The maximum distance (maximum number of lay-overs) between two airports is: "
         << maximumDistance << endl
         << "And is made between the following pair(s) of airports: " << endl;

    for (pair<string, string> e : diameterPairs) {
        cout << "Source: " << e.first << " - Target: " << e.second << endl;
    }
}

/**
 * @brief Auxiliar breadth-First Search
 * @details Time complexity:
 * @param sourceVertex,trips A vertex and pair of source-destination airports
 * @return The number of maximum distance for a vertex
 */
int Manager::getMaximumDistance(Vertex<Airport> *sourceVertex, list<pair<string, string>> &trips) const{
    int maximumDistance = 0;

    for (Vertex<Airport>* vertex : network.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    queue<pair<Vertex<Airport>*, int>> vertexToVisit;
    vertexToVisit.push({sourceVertex, 0});
    sourceVertex->setProcessing(true);

    while (!vertexToVisit.empty()) {
        Vertex<Airport>* currentVertex = vertexToVisit.front().first;

        if (vertexToVisit.front().second > maximumDistance) {
            maximumDistance = vertexToVisit.front().second;
            trips = {{sourceVertex->getInfo().getCode(), currentVertex->getInfo().getCode()}};
        } else if (vertexToVisit.front().second  == maximumDistance) {
            trips.insert(trips.end(), {sourceVertex->getInfo().getCode(), currentVertex->getInfo().getCode()});
        }

        for (Edge<Airport> edge: currentVertex->getAdj()) {
            if (edge.getDest()->isVisited()) continue;
            if (edge.getDest()->isProcessing()) continue;
            vertexToVisit.push({edge.getDest(), vertexToVisit.front().second + 1});
            edge.getDest()->setProcessing(true);
        }

        vertexToVisit.pop();
        currentVertex->setVisited(true);
        currentVertex->setProcessing(false);
    }

    return maximumDistance;
}

/**
 * @brief Method that Identify the top-k airport with the greatest air traffic capacity
 * @details Time complexity:
 * @param K
 */
void Manager::getTopKAirport(const int& K) const {
    // Create a vector to store airports and their flight counts
    vector<pair<Vertex<Airport>*, int>> airportFlightsCount;

    // Iterate over all airports and count their total flights
    for (Vertex<Airport>* airport : network.getVertexSet()) {
        int flightCount = airport->getAdj().size() + airport->getInDegree();
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

/**
 * @brief Prints the amount of essential airports (articulation vertices) and their names
 * @details Time complexity:
 * @see dfs_art();
 */
void Manager::getEssentialAirports() const {
    unsigned int index = 1;
    unordered_set<string> essentialAirports;

    for (Vertex<Airport>* vertex : network.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    for (Vertex<Airport>* v : network.getVertexSet()) {
        if (!v->isVisited()) {
            dfs_art(v, essentialAirports, index);
        }
    }

    // Displaying the Essential airports
    cout << "ESSENTIAL AIRPORTS: " << endl;
    for (string e : essentialAirports) {
        cout << "- " << e << endl;
    }
    cout << "There are a total of " << essentialAirports.size() << " essential airports in the network" << endl;
}

/**
 * @brief Auxiliar Depth-first search to find essential airports
 * @details Time complexity:
 * @param v
 * @param essentialAirports
 * @param index
 */
void Manager::dfs_art(Vertex<Airport> *v, unordered_set<string>& essentialAirports, unsigned int index) const {
    int children = 0;
    v->setNum(index);
    v->setLow(index);
    index++;
    v->setProcessing(true);
    v->setVisited(true);

    for (const Edge<Airport>& e : v->getAdj()) {
        Vertex<Airport>* w = e.getDest();
        if (!w->isVisited()) {
            children++;
            dfs_art(w, essentialAirports, index);
            if (v->getLow() > w->getLow()) v->setLow(w->getLow());
            if (w->getLow() >= v->getNum() and v->getNum() != 1) essentialAirports.insert(v->getInfo().getCode());
            if (v->getNum() == 1 and children > 1) essentialAirports.insert(v->getInfo().getCode());
        } else if (w->isProcessing()) {
            if (v->getLow() > w->getNum()) v->setLow(w->getNum());
        }
    }

    v->setProcessing(false);
}

/**
 * @brief Print the optimal path between a specified starting airport and a target airport, considering optional filters
 * @details Time complexity:
 * @param sourceAirports
 * @param targetAirports
 * @param airlines
 * @param minimumOn
 * @see getMinimumPath();
 */
void Manager::getBestFlight(list<Vertex<Airport> *> sourceAirports, list<Vertex<Airport> *> targetAirports, list<string> airlines, bool minimumOn) const {
    unsigned int minimumPath = network.getVertexSet().size() + 1;
    list<list<pair<string, string>>> flightOptions;

    for (Vertex<Airport>* source : sourceAirports) {
        for (Vertex<Airport>* target : targetAirports) {
            list<list<pair<string, string>>> temp;
            unsigned int currentPath = getMinimumPath(source, target, temp, airlines);
            if (currentPath < minimumPath) {
                minimumPath = currentPath;
                flightOptions = temp;
            } else if (currentPath == minimumPath) {
                flightOptions.splice(flightOptions.end(), temp);
            }
        }
    }

    if (minimumOn) {
        list<list<pair<string, string>>> minimumOptions;
        unsigned int minAirlines = INT32_MAX;

        for (list<pair<string, string>> option: flightOptions) {
            list<pair<string, string>> currentMinimumOption;
            unsigned int currentMinAirlines = 0;
            set<string> currentAirlines;
            for (pair<string, string> flight: option) {
                currentMinimumOption.push_back(flight);
                auto it = currentAirlines.insert(flight.second);
                if (it.second) currentMinAirlines++;
            }
            if (currentMinAirlines < minAirlines) {
                minAirlines = currentMinAirlines;
                minimumOptions.clear();
                minimumOptions.push_back(currentMinimumOption);
            }
            else if (currentMinAirlines == minAirlines) {
                minimumOptions.push_back(currentMinimumOption);
            }
        }
        flightOptions = minimumOptions;
    }
    cout << "There are " << flightOptions.size() << " flights that only take " << minimumPath << " layover(s)"
        << endl;
    for (list<pair<string, string>> option: flightOptions) {
        for (pair<string, string> flight: option) {
            if (flight.second != "") cout << " -> " << flight.first << " (" << flight.second << ") ";
            else cout << flight.first;
        }
        cout << endl;

    }
}

/**
 * @brief Auxiliar breadth-first search
 * @details Time complexity:
 * @param source
 * @param target
 * @param options Path options
 * @param airlines A list of user's preferred airlines
 * @return The number of minimum path
 */
unsigned int Manager::getMinimumPath(Vertex<Airport>* source, Vertex<Airport>* target, list<list<pair<string, string>>>& options, list<string> airlines) const {
    unsigned int minimumPath = network.getVertexSet().size() + 1;

    for (Vertex<Airport>* vertex : network.getVertexSet()) {
        vertex->setVisited(false);
    }

    // Each element in the queue has a vertex and a pair with the current step information
    // The information pair contains the number of the step and a list of flights taken from the source airport to get there
    queue<pair<Vertex<Airport>*, pair<int, list<pair<string, string>>>>> vertexToVisit;
    vertexToVisit.push({source, {0, {{source->getInfo().getCode(), ""}}}});

    while (!vertexToVisit.empty()) {
        Vertex<Airport>* currentVertex = vertexToVisit.front().first;
        int currentStep = vertexToVisit.front().second.first;
        if (currentStep > minimumPath) {
            vertexToVisit.pop();
            currentVertex->setVisited(true);
            continue;
        }
        list<pair<string, string>> currentPath = vertexToVisit.front().second.second;

        if (currentVertex == target) {
            if (currentStep < minimumPath) {
                minimumPath = currentStep;
                options = {currentPath};
            }
            else if (currentStep == minimumPath) options.push_back(currentPath);
            vertexToVisit.pop();
            continue;
        }

        for (Edge<Airport> edge: currentVertex->getAdj()) {
            if (edge.getDest()->isVisited()) continue;
            if (airlines.size() >= 1) {
                auto it = std::find(airlines.begin(), airlines.end(), edge.getAirline());
                if (it == airlines.end()) continue;
            }
            list<pair<string, string>> temp = currentPath;
            temp.emplace_back(edge.getDest()->getInfo().getCode(), edge.getAirline());
            vertexToVisit.push({edge.getDest(), {vertexToVisit.front().second.first + 1, temp}});
            if (edge.getDest() != target) edge.getDest()->setProcessing(true);
        }

        vertexToVisit.pop();
        currentVertex->setVisited(true);
    }

    return minimumPath;
}

/**
 * @brief Converts a airport code on a list of airport vertices.
 * @details Time complexity:
 * @param code
 * @return A list of airport vertices
 */
list<Vertex<Airport> *> Manager::getAirportsByCode(string code) const {
    list<Vertex<Airport> *> res;
    res.insert(res.begin(), network.findVertex(Airport(code)));
    return res;
}

/**
 * @brief Converts a airport name on a list of airport vertices.
 * @details Time complexity:
 * @param name
 * @return A list of airport vertices.
 */
list<Vertex<Airport> *> Manager::getAirportsByName(string name) const {
    list<Vertex<Airport> *> res;
    for (Vertex<Airport> * vertex : network.getVertexSet()) {
        if (vertex->getInfo().getName() == name) {
            res.push_back(vertex);
        }
    }
    return res;
}

/**
 * @brief Converts a city and its country on a list of airport vertices.
 * @details Time complexity:
 * @param city
 * @param country
 * @return A list of airport vertices.
 */
list<Vertex<Airport> *> Manager::getAirportsByCity(string city, string country) const {
    list<Vertex<Airport> *> res;
    for (Vertex<Airport> * vertex : network.getVertexSet()) {
        if (vertex->getInfo().getCity() == city and vertex->getInfo().getCountry() == country) {
            res.push_back(vertex);
        }
    }
    return res;
}

/**
 * @brief Converts latitude and longitude on a list of airport vertices.
 * @details Time complexity:
 * @param latitude
 * @param longitude
 * @return A list of airport vertices.
 */
list<Vertex<Airport> *> Manager::getAirportsByCoordinates(double latitude, double longitude) const {
    list<Vertex<Airport> *> res;
    auto minDistance = DBL_MAX;
    for (Vertex<Airport> * vertex : network.getVertexSet()) {
        double distance = haversine(latitude, longitude, vertex->getInfo().getLatitude(), vertex->getInfo().getLongitude());
        if (distance < minDistance) {
            minDistance = distance;
            res = {vertex};
        } else if (distance == minDistance) {
            res.push_back(vertex);
        }
    }
    return res;
}

/**
 * @brief Calculates distance between coordinates of latitude and longitude using Haversine Distance method
 * @details Time complexity:
 * @param lat1
 * @param lon1
 * @param lat2
 * @param lon2
 * @return Distance between coordinates of latitude and longitude
 */
double Manager::haversine(double lat1, double lon1, double lat2, double lon2) {
    // distance between latitudes
    // and longitudes
    double dLat = (lat2 - lat1) *
                  M_PI / 180.0;
    double dLon = (lon2 - lon1) *
                  M_PI / 180.0;

    // convert to radians
    lat1 = (lat1) * M_PI / 180.0;
    lat2 = (lat2) * M_PI / 180.0;

    // apply formulae
    double a = pow(sin(dLat / 2), 2) +
               pow(sin(dLon / 2), 2) *
               cos(lat1) * cos(lat2);
    double rad = 6371;
    double c = 2 * asin(sqrt(a));
    return rad * c;
}
