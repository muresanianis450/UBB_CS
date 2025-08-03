

#include "Programmer.h"
Programmer::Programmer(const std::string name, int id) {
    this->name = name;
    this->id = id;
}



std::string Programmer::getName() const {
    return name;
}

int Programmer::getId() const {
    return id;
}