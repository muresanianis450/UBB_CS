#pragma once
#include <string>

class Idea {
    std::string description;
    std::string status;   // "proposed" or "accepted"
    std::string creator;
    int act;

public:
    Idea(const std::string& desc, const std::string& creator, int act, const std::string& status = "proposed");

    std::string getDescription() const;
    std::string getStatus() const;
    std::string getCreator() const;
    int getAct() const;

    void setStatus(const std::string& newStatus);
};
