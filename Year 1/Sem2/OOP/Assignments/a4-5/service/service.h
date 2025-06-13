//
// Created by mures on 3/25/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>
#include "../repository/Repo.h"
#include "../repository/DynamicVector_01.h"
#include "../domain/Dog.h"



class Service {
private:
    Repository repo;

public:
    std::vector<Dog> adoptedDogs;

    Service();

    void addDog(const Dog& d);
    bool removeDog(const Dog& d);
    bool updateDog(const Dog& oldDog, const Dog& newDog);
    DynamicArray <Dog>& getAllDogs() ;
    DynamicArray <Dog> getDogsByBreed (const std::string& breed);
    void adoptDog(const Dog& d);
    bool invalidDog(const Dog& d) const;

    std::vector<Dog> getAdoptedDogs() const;
};

//ioabsdubas

#endif //SERVICE_H
