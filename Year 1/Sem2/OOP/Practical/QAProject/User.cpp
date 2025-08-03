
#include "User.h"
User::User(const std::string &name) {
    this->name = name;
}
std::string User::getName() const {
    return name;
}

