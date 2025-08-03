
#include "Person.h"
#include <sstream>
Person::Person(std::string name, double lat, double lon, bool isOrg) {
    this->name = name;
    this->latitude = lat;
    this->longitude = lon;
    this->isOrganizer = isOrg;
}

double Person::getLatitude() const {
    return latitude;
}
double Person::getLongitude() const {
    return longitude;
}
bool Person::getIsOrganizer() const {
    return isOrganizer;
}
std::string Person::getName() const {
    return name;
}

std::istream& operator>>(std::istream& is, Person& p) {
    std::string line;
    if (!std::getline(is, line)) return is;

    std::stringstream ss(line);
    std::string name;

    double lat,lon;
    int organiserStatus;

    std::getline(ss,name,',');
    ss >>lat;
    ss.ignore();
    ss >> lon;
    ss.ignore();
    ss >> organiserStatus;

    p = Person(name,lat,lon,organiserStatus!=0);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Person& person) {
    os << person.getName()<<","
        <<person.getLatitude()<<","
        <<person.getLongitude()<<","
        <<(person.getIsOrganizer() ? "1":"0");
    return os;
}


