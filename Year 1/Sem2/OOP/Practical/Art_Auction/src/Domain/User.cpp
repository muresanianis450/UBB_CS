#include "User.h"
#include <stdexcept>
#include <algorithm>
#include <cctype>
#include <qwidget.h>

User::User(int id, const std::string& name, const std::string& type)
    : id(id), name(name), type(type)
{
    if (!isValidUserType(type)) {
        throw std::invalid_argument("Invalid user type: " + type);
    }
}

int User::getId() const {
    return id;
}

const std::string& User::getName() const {
    return name;
}

const std::string& User::getType() const {
    return type;
}

bool User::isValidUserType(const std::string& typeStr) {
    std::string lowerType = typeStr;
    std::transform(lowerType.begin(), lowerType.end(), lowerType.begin(), [](unsigned char c){ return std::tolower(c); });
    return (lowerType == "collector" || lowerType == "administrator");
}
