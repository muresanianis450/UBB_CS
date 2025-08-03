#include "Idea.h"

Idea::Idea(const std::string& desc, const std::string& creator, int act, const std::string& status)
    : description(desc), creator(creator), act(act), status(status) {}

std::string Idea::getDescription() const { return description; }
std::string Idea::getStatus() const { return status; }
std::string Idea::getCreator() const { return creator; }
int Idea::getAct() const { return act; }

void Idea::setStatus(const std::string& newStatus) {
    status = newStatus;
}
