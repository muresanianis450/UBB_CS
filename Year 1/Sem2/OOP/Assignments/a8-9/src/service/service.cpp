//
// Created by mures on 3/25/2025.
//

#include "service.h"
#include "../validator/validator.h"
#include "../exceptions/CustomExceptions.h"


//Constructor
Service::Service(): repo(TextFileRepository("dogs.txt")) {
    this->adoptedDogs = std::vector<Dog>();
    //this->repo.loadFromFile();
    //this->repo.saveToFile();
}

/*
 *addDog- adds a dog to the repository
 *param: d- Dog - the dog to be added
 */

bool Service::invalidDog(const Dog& d) {
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
        this->repo.add(d);
    } catch (const ValidationException& e) {
        throw; // Re-throw validation exception
    } catch (const RepositoryException& e) {
        throw; // Re-throw repository exception
    }
}
/*removeDog- removes a dog from the repository
 *param: d- Dog - the dog to be removed
 */
bool Service::removeDog(const Dog& d) {
    return this->repo.remove(d);
}
/*updateDog- updates a dog from the repository
 *param: oldDog- Dog - the dog to be updated
 *param: newDog- Dog - the new dog
 */
bool Service::updateDog(const Dog& oldDog, const Dog& newDog) {
    return this->repo.update(oldDog, newDog);
}

std::vector<Dog> Service::getAdoptedDogs() const {
    return this->adoptedDogs;
}


/*getAllDogs- returns all the dogs in the repository
 */
std::vector<Dog> Service::getAllDogs() const {
    return this->repo.getAll();
}

std::vector<Dog> Service::getDogsByBreed(const std::string& breed) const {
    std::vector<Dog> dogs = this->repo.getAll();
    std::vector<Dog> dogsByBreed;
    for (const Dog& dog : dogs) {
        if (dog.getBreed() == breed) {
            dogsByBreed.push_back(dog);
        }
    }
    return dogsByBreed;

}

void Service::adoptDog(const Dog& d) {
    this->adoptedDogs.push_back(d);
}
