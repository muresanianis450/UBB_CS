#pragma once
#include <string>

class User {
private:
    std::string name;
public:
    User(const std::string& name);
    std::string getName() const;
};