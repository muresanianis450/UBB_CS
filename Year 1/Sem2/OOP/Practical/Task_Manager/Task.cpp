

#include "Task.h"
Task::Task(const std::string &desc, const std::string &status, int programmerId) {
    this->description = desc;
    this->status = status;
    this->programmerId = programmerId;
}

std::string Task::getDescription() const {
    return description;
}
std::string Task::getStatus() const {

    return status;
}
int Task::getProgrammerId() const {
    return programmerId;
}
void Task::setStatus(const std::string &newStatus) {
    status = newStatus;
}
void Task::setProgrammerId(int newProgrammerId) {
    programmerId = newProgrammerId;
}
