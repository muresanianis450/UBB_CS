
#include "Astronomer.h"

Astronomer::Astronomer(std::string name, std::string constelation) {
    this->name = name;
    this->constelation = constelation;

}

std::string Astronomer::getName() const {
    return name;
}
std::string Astronomer::getConstelation() const {
    return constelation;

}

