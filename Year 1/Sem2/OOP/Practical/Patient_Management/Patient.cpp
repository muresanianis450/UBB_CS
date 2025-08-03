
#include "Patient.h"

Patient::Patient(std::string name, std::string diagnosis, std::string currentDoctor, std::string neededSpecialization, std::string admissionDate) {
    this->name = name;
    this->diagnosis = diagnosis;
    this->currentDoctor = currentDoctor;
    this->neededSpecialization = neededSpecialization;
    this->admissionDate = admissionDate;
}
const std::string &Patient::getName() const {
    return name;
}
const std::string &Patient::getDiagnosis() const {
    return diagnosis;
}
const std::string &Patient::getCurrentDoctor() const {
    return currentDoctor;
}
const std::string &Patient::getNeededSpecialization() const {
    return neededSpecialization;
}
const std::string &Patient::getAdmissionDate() const {
    return admissionDate;
}

void Patient::setDiagnosis(const std::string &diagnosis) {
    Patient::diagnosis = diagnosis;

}
void Patient::setAdmissionDate(const std::string &admissionDate) {
    Patient::admissionDate = admissionDate;
}
void Patient::setNeededSpecialization(const std::string &neededSpecialization) {
    Patient::neededSpecialization = neededSpecialization;
}



