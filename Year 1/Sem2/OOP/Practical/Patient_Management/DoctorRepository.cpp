
#include "DoctorRepository.h"
#include <fstream>
#include <sstream>

DoctorRepository::DoctorRepository(const std::string &fileName="doctors.txt") {
    std::ifstream fin(fileName);
    std::string line;
    while (std::getline(fin,line)) {
        std::istringstream iss(line);
        std::string name, specialization;
        std::getline(iss,name,',');
        std::getline(iss,specialization);
        doctors.emplace_back(name,specialization);
    }
}

const std::vector<Doctor> &DoctorRepository::getAllDoctors() const {
    return doctors;
}
