//
// Created by mures on 3/25/2025.
//

#include "service.h"
#include "../validator/validator.h"


//Constructor
Service::Service() {
    this->repo = Repository();
}

/*
 *addDog- adds a dog to the repository
 *param: d- Dog - the dog to be added
 */

bool Service::invalidDog(const Dog& d) const {
    try {
        Validator::validateDog(d);  // Try to validate the dog
        return false;  // If no exception, dog is valid
    } catch (const std::invalid_argument& e) {
        return true;  // If validation fails, dog is invalid
    }
}


void Service::addDog(const Dog& d) {
    try {
        Validator::validateDog(d);
        this->repo.addDog(d);
    } catch (const std::invalid_argument&) {
        // Exception is caught but no message is displayed
        return;
    }
}
/*removeDog- removes a dog from the repository
 *param: d- Dog - the dog to be removed
 */
bool Service::removeDog(const Dog& d) {
    return this->repo.removeDog(d);
}
/*updateDog- updates a dog from the repository
 *param: oldDog- Dog - the dog to be updated
 *param: newDog- Dog - the new dog
 */
bool Service::updateDog(const Dog& oldDog, const Dog& newDog) {
    return this->repo.updateDog(oldDog, newDog);
}

std::vector<Dog> Service::getAdoptedDogs() const {
    return this->adoptedDogs;
}


/*getAllDogs- returns all the dogs in the repository
 */
DynamicArray <Dog>& Service::getAllDogs() {
    return this->repo.getAllDogs();
}

DynamicArray<Dog> Service::getDogsByBreed(const std::string& breed) {
    return this->repo.getDogs_by_breed(breed);
}

void Service::adoptDog(const Dog& d) {
    this->adoptedDogs.push_back(d);
}
