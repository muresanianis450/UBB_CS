#pragma once
#include <string>
class Astronomer {
    std::string name;
    std::string constelation;
public:
    Astronomer(std::string name, std::string constelation);
    std::string getName() const ;
    std::string getConstelation() const;
};