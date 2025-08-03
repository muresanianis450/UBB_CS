#pragma once
#include <string>

class Star {
private:
    std::string name, constelation;
    int RA, Dec;
    double diameter;
public:
    Star(const std::string& name , const std::string& constelation, int RA, int Dec, double diameter);
    std::string getName() const;
    std::string getConstelation() const;
    int getRA() const;
    int getDec() const;
    double getDiameter() const;
};