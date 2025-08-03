#pragma once
#include "Driver.h"
#include <vector>
#include <string>
class DriverRepo{
private:
    std::vector<Driver> drivers;
public:
    DriverRepo();
    void loadFile(const std::string& filename= "drivers.txt");
    const std::vector<Driver>& getAll() const;
    Driver* findByName(const std::string& name);

};