#include "Writer.h"

Writer::Writer(const std::string& name, const std::string& expertise)
    : name(name), expertise(expertise) {}

std::string Writer::getName() const {
    return name;
}
std::string Writer::getExpertise() const {
    return expertise;
}