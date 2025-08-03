
#include "Doctor.h"

Doctor::Doctor(const std::string &name, const std::string &specialization) {
    this->name = name;
    this->specialization = specialization;
}
const std::string &Doctor::getName() const {
    return name;
}
const std::string &Doctor::getSpecialization() const {
    return specialization;
}


