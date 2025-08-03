
#include "Star.h"
Star::Star(const std::string &name, const std::string &constelation, int RA, int Dec, double diameter) {
    this->name = name;
    this->constelation = constelation;
    this->RA = RA;
    this->Dec = Dec;
    this->diameter = diameter;
}

std::string Star::getName() const {
    return name;
}
std::string Star::getConstelation() const {
    return constelation;

}
int Star::getRA() const {
    return RA;
}
int Star::getDec() const {
    return Dec;
}
double Star::getDiameter() const {
    return diameter;
}

