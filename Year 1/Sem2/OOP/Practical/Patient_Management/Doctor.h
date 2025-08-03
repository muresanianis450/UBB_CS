#pragma once
#include <string>
class Doctor {
private:
    std::string name, specialization;

public:
    Doctor(const std::string& name, const std::string& specialization);
    const std::string& getName() const;
    const std::string& getSpecialization() const;
};