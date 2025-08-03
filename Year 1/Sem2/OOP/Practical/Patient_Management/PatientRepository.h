#pragma once

#include "Patient.h"
#include <vector>
#include <string>

class PatientRepository {
private:
    std::vector<Patient> patients;

public:
    PatientRepository(const std::string& fileName);
    const std::vector<Patient>& getAllPatients() const;
    std::vector<Patient>&  getAllReferencedPatients() ;

    void addPatient(const Patient& patient);
    void updatePatient(const Patient& updatedPatient);
    void saveToFile(const std::string& fileName) const;

};