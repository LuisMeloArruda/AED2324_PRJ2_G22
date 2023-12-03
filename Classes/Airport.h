#ifndef AED2324_PRJ2_G22_AIRPORT_H
#define AED2324_PRJ2_G22_AIRPORT_H

#include <string>

using namespace std;

class Airport {
private:
    string code;
    string name;
    string city;
    string country;
    double latitude;
    double longitude;
public:
    Airport(string code, string name, string city, string country, double latitude, double longitude);
    Airport(string code);
    string getCode() const;
    void setCode(string code);
    string getName() const;
    void setName(string name);
    string getCity() const;
    void setCity(string city);
    string getCountry() const;
    void setCountry(string country);
    double getLatitude() const;
    void setLatitude(double latitude);
    double getLongitude() const;
    void setLongitude(double longitude);
    bool operator==(const Airport& b) const;
};

#endif //AED2324_PRJ2_G22_AIRPORT_H
