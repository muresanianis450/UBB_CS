// validator/validator.cpp
#include "validator.h"
#include "ValidationException.h"

void Validator::validateDog(const Dog& dog) {
    if (dog.getName().empty()) {
        throw ValidationException("Dog name cannot be empty!");
    }
    if (dog.getBreed().empty()) {
        throw ValidationException("Dog breed cannot be empty!");
    }
    if (dog.getAge() < 0) {
        throw ValidationException("Dog age cannot be negative!");
    }
    if (dog.getPhotography().empty()) {
        throw ValidationException("Dog photography URL cannot be empty!");
    }
}