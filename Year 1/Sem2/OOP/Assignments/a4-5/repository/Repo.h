//
// Created by mures on 3/24/2025.
//

#ifndef REPO_H
#define REPO_H
#include"DynamicVector_01.h"
#include"../domain/Dog.h"

typedef Dog TElem;

class Repository {
private:
    DynamicArray <Dog> dogs{}   ;

public:
    Repository();
    void addDog(const Dog& d);
    bool removeDog(const Dog& d);
    bool updateDog(const Dog& oldDog, const Dog& newDog);
    DynamicArray <Dog>& getAllDogs() ;
    DynamicArray <Dog> getDogs_by_breed(const std::string& breed);

};

#endif //REPO_H
