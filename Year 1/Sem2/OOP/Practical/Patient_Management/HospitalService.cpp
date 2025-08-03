
#include "HospitalService.h"
#include <ctime>
#include <stdexcept>
#include <iostream>
HospitalService::HospitalService(DoctorRepository& dRepo, PatientRepository& pRepo)
    : doctorRepo(dRepo), patientRepo(pRepo) {}

const std::vector<Doctor>& HospitalService::getAllDoctors() const {
    return doctorRepo.getAllDoctors();
}
const std::vector<Patient>& HospitalService::getAllPatients() const {
    return patientRepo.getAllPatients();
}

std::vector<Patient> HospitalService::getPatientsBySpecialization(const std::string& specialization) const {
    std::vector<Patient> result;

    for (const auto& p : patientRepo.getAllPatients()) {
        if (p.getNeededSpecialization() == specialization || p.getDiagnosis() == "undiagnosed") {
            result.push_back(p);
        }
    }
    return result;
}
std::vector<Patient> HospitalService::getPatientsForDoctor(const std::string& doctorName,
                                                           const std::string& specialization,
                                                           bool onlyOwnPatients) const {
    std::vector<Patient> result;

    for (const auto& p : patientRepo.getAllPatients()) {
        if (onlyOwnPatients) {
            if (p.getCurrentDoctor() == doctorName) {
                result.push_back(p);
            }
        }else {
            if (p.getNeededSpecialization() == specialization || p.getDiagnosis() == "undiagnosed"){
                result.push_back(p);
            }
        }
    }
    std::sort(result.begin(),result.end(),
        [](const Patient& p1, const Patient& p2) {
        return p1.getAdmissionDate() < p2.getAdmissionDate();
    });
    return result;
}
void HospitalService::addPatient(const std::string& name, const std::string& diagnosis, const std::string& currentDoctor,
                                 const std::string& neededSpecialization, const std::string& admissionDate) {
    if (name.empty())
        throw std::runtime_error("patient name cannot be empty!!!");

    std::string diag = diagnosis;
    std::string spec = neededSpecialization;

    if (diag.empty()) {
        diag = "undiagnosed";
    }

    if (spec.empty()) {
        spec = "";
    }

    std::string today = "2025-01-01";
    if (admissionDate < today)
        throw std::runtime_error("admission date cannot be in the past!!!");

    patientRepo.addPatient(Patient(name, diag, currentDoctor, spec, admissionDate));
    notifyObservers();
    patientRepo.saveToFile("patients.txt");
    std::cout<<"Added patient into the file;";
}



void HospitalService::updateDiagnosisAndSpecialization(const std::string& patientName,
                                                       const std::string& newDiagnosis,
                                                       const std::string& newSpecialization,
                                                       const std::string& doctorName) {
    if (newDiagnosis == "undiagnosed")
        throw std::runtime_error("Diagnosis cannot be 'undiagnosed'!");

    //find the doctor specialization
    std::string currentDoctorSpecialization;
    bool foundDoctor = false;
    for (const auto& doc : doctorRepo.getAllDoctors()) {
        if (doc.getName() == doctorName) {
            currentDoctorSpecialization = doc.getSpecialization();
            foundDoctor = true;
            break;
        }
    }
    if (!foundDoctor)
        throw std::runtime_error("Doctor not found!");



    auto& allPatients = patientRepo.getAllReferencedPatients();
    for (auto& p : allPatients) {
        if (p.getName() == patientName) {
            if (p.getDiagnosis() == "undiagnosed" || p.getCurrentDoctor() == doctorName) {
                // update diagnossi and specialization
                p.setDiagnosis(newDiagnosis);
                p.setNeededSpecialization(newSpecialization);

                //if specialization is not the same with the current doc
                if (newSpecialization != currentDoctorSpecialization) {
                    for (const auto& doc : doctorRepo.getAllDoctors()) {
                        if (doc.getSpecialization() == newSpecialization) {
                            //assignt it to the new doctor
                            p = Patient(p.getName(), newDiagnosis, doc.getName(), newSpecialization, p.getAdmissionDate());
                            notifyObservers();
                            return;
                        }
                    }
                    throw std::runtime_error("No doctor found with the new specialization!");
                }

                //if specialization remains the same then assign it to the same doctor
                p = Patient(p.getName(), newDiagnosis, doctorName, newSpecialization, p.getAdmissionDate());
            patientRepo.saveToFile("patients.txt");
                notifyObservers();
                return;
            } else {
                throw std::runtime_error("Cannot update patient that you are not responsible for!");
            }
        }
    }

    throw std::runtime_error("Patient not found!");
}