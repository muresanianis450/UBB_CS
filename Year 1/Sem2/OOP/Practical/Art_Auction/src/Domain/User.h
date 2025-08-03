#pragma once


#include <qwidget.h>
#include <string>

class User {
private:
    int id;
    std::string name;
    std::string type;

public:
    User(int id, const std::string& name, const std::string& type);

    int getId() const;
    const std::string& getName() const;
    const std::string& getType() const;

    // Optionally, validate if type is valid
    static bool isValidUserType(const std::string& typeStr);
};

