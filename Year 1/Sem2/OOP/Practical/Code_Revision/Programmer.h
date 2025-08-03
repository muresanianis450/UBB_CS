#pragma once
#include <string>

class Programmer {
private:
    std::string name;
    int revised;
    int total; // total to be revised
public:
    Programmer(const std::string& name, int rev, int total);
    std::string getName() const;
    int getRevised() const;
    int getRemaining() const ;
    void incrementRevised();
};