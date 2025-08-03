#pragma once
#include <string>

class Programmer {
    std::string name;
    int id;
public:
    Programmer(const std::string name, int id);

    std::string getName() const;
    int getId() const;

};