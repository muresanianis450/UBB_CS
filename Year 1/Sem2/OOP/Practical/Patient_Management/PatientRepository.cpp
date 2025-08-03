#include "PatientRepository.h"
#include <fstream>
#include <qnamespace.h>
#include <sstream>

PatientRepository::PatientRepository(const std::string &fileName = "patients.txt") {
    std::ifstream fin(fileName);
    std::string line;
    while (std::getline(fin,line)) {
        std::istringstream iss(line);
        std::string name, diagnosis, currentDoctor, neededSpecialization,admisionDate;
        std::getline(iss,name,',');
        std::getline(iss,diagnosis,',');
        std::getline(iss,currentDoctor,',');
        std::getline(iss,neededSpecialization,',');
        std::getline(iss,admisionDate);
        patients.emplace_back(name,diagnosis,currentDoctor,neededSpecialization,admisionDate);
    }

}


const std::vector<Patient>& PatientRepository::getAllPatients() const {
    return patients;
}
std::vector<Patient>& PatientRepository::getAllReferencedPatients() {
    return patients;
}
void PatientRepository::addPatient(const Patient& patient) {
    patients.push_back(patient);
}
void PatientRepository::updatePatient(const Patient& updatedPatient) {
    for (auto& p : patients) {
        if (p.getName() == updatedPatient.getName()) {
            p.setDiagnosis(updatedPatient.getDiagnosis());
            p.setNeededSpecialization(updatedPatient.getNeededSpecialization());
            p.setAdmissionDate(updatedPatient.getAdmissionDate());
            return;


        }
    }
}

void PatientRepository::saveToFile(const std::string& fileName="patients.txt") const {
    std::ofstream fout(fileName);
    for (const auto& p : patients) {
        fout << p.getName() << ","
            << p.getDiagnosis() << ","
            << p.getCurrentDoctor() << ","
            << p.getNeededSpecialization() << ","
            << p.getAdmissionDate() << "\n";
    }
}
