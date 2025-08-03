#pragma once
#include "Doctor.h"
#include <vector>
#include <string>

class DoctorRepository {
private:
    std::vector<Doctor> doctors;
public:
    DoctorRepository(const std::string& fileName);
    const std::vector<Doctor>& getAllDoctors() const;
};