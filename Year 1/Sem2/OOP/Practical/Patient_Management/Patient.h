#pragma once
#include <string>


class Patient {
private:
    std::string name, diagnosis, currentDoctor, neededSpecialization;
    std::string admissionDate;
public:
    Patient(std::string name, std::string diagnosis, std::string currentDoctor, std::string neededSpecialization, std::string admissionDate);
    const std::string& getName() const;
    const std::string& getDiagnosis() const;
    const std::string& getCurrentDoctor() const;
    const std::string& getNeededSpecialization() const;
    const std::string& getAdmissionDate() const;

    void setDiagnosis(const std::string& diagnosis);
    void setNeededSpecialization(const std::string& neededSpecialization);
    void setAdmissionDate(const std::string& admissionDate);

};