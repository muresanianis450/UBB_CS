#pragma once
#include "DoctorRepository.h"
#include "PatientRepository.h"
#include <vector>
#include <string>
#include <functional>
#include "Observable.h"

class HospitalService : public Observable{
private:
    DoctorRepository& doctorRepo;
    PatientRepository& patientRepo;

public:
    HospitalService(DoctorRepository& dRepo, PatientRepository& pRepo);
    const std::vector<Doctor>& getAllDoctors() const;
    const std::vector<Patient>& getAllPatients() const;
    std::vector<Patient> getPatientsBySpecialization(const std::string& specialization) const;
    std::vector<Patient> getPatientsForDoctor (const std::string& doctorName, const std::string& specialization, bool onlyOwnPatients) const;

    void addPatient(const std::string& name, const std::string& diagnosis, const std::string& currentDoctor,
                    const std::string& neededSpecialization, const std::string& admissionDate);
    void updateDiagnosisAndSpecialization(const std::string& patientName, const std::string& newDiagnosis,
                                         const std::string& newSpecialization, const std::string& doctorName);
    void save() const;
};