#include "Airport.h"

Airport::Airport(string code, string name, string city, string country, double latitude, double longitude) {
    this->code = code;
    this->name = name;
    this->city = city;
    this->country = country;
    this->latitude = latitude;
    this->longitude = longitude;
}

string Airport::getCode() const {
    return code;
}

void Airport::setCode(string code) {
    this->name = name;
}

string Airport::getName() const {
    return name;
}

void Airport::setName(string name) {
    this->name = name;
}

string Airport::getCity() const {
    return city;
}

void Airport::setCity(string city) {
    this->city = city;
}

string Airport::getCountry() const {
    return country;
}

void Airport::setCountry(string country) {
    this->country = country;
}

double Airport::getLatitude() const {
    return latitude;
}

void Airport::setLatitude(double latitude) {
    this->latitude = latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

void Airport::setLongitude(double longitude) {
    this->longitude = longitude;
}
