#pragma once
#include <string>

class Writer {
    std::string name;
    std::string expertise; //assitant junior sau senior

public:
    Writer(const std::string& name, const std::string& expertise);
    std::string getName() const;
    std::string getExpertise() const;
};