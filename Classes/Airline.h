#ifndef AED2324_PRJ2_G22_AIRLINE_H
#define AED2324_PRJ2_G22_AIRLINE_H

#include <string>

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callSign;
    string country;
public:
    Airline(string code, string name, string callSign, string country);
    string getCode() const;
    void setCode(string code);
    string getName() const;
    void setName(string name);
    string getCallSign() const;
    void setCallSign(string callSign);
    string getCountry() const;
    void setCountry(string country);
    bool operator<(const Airline& b) const;
};

#endif //AED2324_PRJ2_G22_AIRLINE_H
