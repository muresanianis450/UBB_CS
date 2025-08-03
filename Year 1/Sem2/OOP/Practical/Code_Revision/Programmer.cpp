
#include "Programmer.h"

std::string Programmer::getName()const {
    return name;
}
int Programmer::getRevised() const{
    return revised;
}
int Programmer::getRemaining() const {
    return total - revised;
}
void Programmer::incrementRevised() {
    revised++;
}
Programmer::Programmer(const std::string& name, int rev, int total)
    : name(name), revised(rev), total(total) {}



