#pragma once

#include <string>

class Task {
    std::string description, status; // open, in progress or closed
    int programmerId;


public:
    Task(const std::string& desc, const std::string& status = "open", int programmerId = -1);

    std::string getDescription() const;
    std::string getStatus() const;
    int getProgrammerId() const;

    void setStatus(const std::string& Newstatus);
    void setProgrammerId(int newId)
    ;

};