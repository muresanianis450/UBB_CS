
#include "Driver.h"
#include <cmath>

Driver::Driver(const std::string& name, double lat, double lon,int score)
    : name(name), latitude(lat), longitude(lon), score(score){}

std::string Driver::getName() const {
    return name;
}
double Driver::getLatitude() const {
    return latitude;
}
double Driver::getLongitude() const {
    return longitude;

}
int Driver::getScore() const {
    return score;

}
void Driver::setLatitude(double lat) {
    latitude = lat;
}
void Driver::setLongitude(double lon) {
    longitude = lon;
}

double Driver::distanceTo(double lat, double lon) const {
    return std::sqrt(std::pow(lat - latitude, 2) + std::pow(lon - longitude, 2));
}
