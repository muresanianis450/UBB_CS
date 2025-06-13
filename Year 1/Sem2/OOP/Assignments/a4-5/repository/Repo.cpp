#include "Repo.h"
#include <iostream>
#include <fstream>

/*
 * Constructor for the Repository class
 */
Repository::Repository(){
    // Add 10 example dogs
    this->dogs.append(Dog("Buddy", "Golden Retriever", 3, "https://www.pexels.com/photo/portrait-of-a-dog-257540/?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Max", "German Shepherd", 5, "https://people.com/guy-fieri-snaps-shirtless-selfie-while-poolside-with-his-dog-cash-11708763?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Bella", "Labrador Retriever", 2, "https://www.pexels.com/search/puppy/?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Charlie", "Bulldog", 4, "https://www.gettyimages.com/photos/cute-dog-drawing?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Lucy", "Beagle", 1, "https://www.gettyimages.com/photos/cute-dog-drawing?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Daisy", "Poodle", 6, "https://www.gettyimages.com/photos/cute-dog-drawing?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Rocky", "Rottweiler", 3, "https://www.google.com/url?sa=i&url=https%3A%2F%2Fwww.akc.org%2Fdog-breeds%2Frottweiler%2F&psig=AOvVaw3eKY_s1NI2-rh3qLvhslMT&ust=1742987681780000&source=images&cd=vfe&opi=89978449&ved=0CBQQjRxqFwoTCMDvl6KNpYwDFQAAAAAdAAAAABAE"));
    this->dogs.append(Dog("Molly", "Boxer", 2, "https://unsplash.com/s/photos/happy-dog?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Bailey", "Dachshund", 4, "https://www.pexels.com/search/cat%20and%20dog/?utm_source=chatgpt.com"));
    this->dogs.append(Dog("Lola", "Siberian Husky", 5, "https://unsplash.com/s/photos/dog-in-nature?utm_source=chatgpt.com2"));

}

/*
 * addDog: adds a dog to the repository
 * param: d- Dog - the dog to be added
 */
void Repository::addDog(const Dog& d) {
    TElem* allDogs = this->dogs.get();
    for (int i = 0; i < this->dogs.getLength(); i++) {
        if (allDogs[i] == d) {
            std::cerr << "Error: Dog already exists!\n";
            return;
        }
    }
    this->dogs.append(d);
}
/*
 * removeDog: removes a dog from the repository
 * param: d- Dog - the dog to be removed
 */
bool Repository::removeDog(const Dog& d) {
   for (int i = 0 ; i < this->dogs.getLength(); i++) {
        if (this->dogs[i] == d) {
            this->dogs.remove(i);
            return true;
        }
    }
    return false;
}

/*
 * updateDog: updates a dog in the repository
 * param: oldDog- Dog - the dog to be updated
 * param: newDog- Dog - the new dog
 */
bool Repository::updateDog(const Dog& oldDog, const Dog& newDog) {
    if (dogs.update(oldDog, newDog))
        return true;
    return false;
}


/*
 * getAllDogs: returns all the dogs in the repository
 */
DynamicArray <Dog>& Repository::getAllDogs() {
return this->dogs;
}

DynamicArray<Dog> Repository::getDogs_by_breed(const std::string& breed) {
    DynamicArray<Dog> dogs_breed;
    for (int i = 0; i < this->dogs.getLength(); i++) {
        if (this->dogs[i].getBreed() == breed) {
            dogs_breed.append(this->dogs[i]);
        }
    }
    return dogs_breed;
}
