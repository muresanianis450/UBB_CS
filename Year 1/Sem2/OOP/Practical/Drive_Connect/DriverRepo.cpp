
#include "DriverRepo.h"
#include <fstream>
#include <sstream>

DriverRepo::DriverRepo() {
    loadFile("drivers.txt");
}

void DriverRepo::loadFile(const std::string &filename) {
    std::ifstream fin(filename);
    std::string name;
    double lat,lon;
    int score;

    while (fin >> name >> lat >> lon >> score) {
        drivers.emplace_back(name,lat,lon,score);
    }
    fin.close();
}

const std::vector<Driver>& DriverRepo::getAll() const {
    return drivers;
}
Driver* DriverRepo::findByName(const std::string& name) {
    for (auto& driver : drivers) {
        if (driver.getName()==name) {
            return &driver;
        }    }
    return nullptr;
}


