#include "Airline.h"

Airline::Airline(string code, string name, string callSign, string country) {
    this->code = code;
    this->name = name;
    this->callSign = callSign;
    this->country = country;
}

string Airline::getCode() const {
    return code;
}

void Airline::setCode(string Code) {
    this->code = code;
}

string Airline::getName() const {
    return name;
}

void Airline::setName(string name) {
    this->name = name;
}

string Airline::getCallSign() const {
    return callSign;
}

void Airline::setCallSign(string callSign) {
    this->callSign;
}

string Airline::getCountry() const {
    return country;
}

void Airline::setCountry(string country) {
    this->country = country;
}

bool Airline::operator<(const Airline& b) const {
    return this->code < b.code;
}