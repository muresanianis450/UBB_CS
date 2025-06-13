//
// Created by mures on 3/25/2025.
//

#ifndef SERVICE_H
#define SERVICE_H
#include <vector>
#include <string>
#include "../repository/Repo.h"
#include "../domain/Dog.h"



class Service {
private:
    TextFileRepository repo;

public:
    std::vector<Dog> adoptedDogs;

    Service();

    void addDog(const Dog& d);
    bool removeDog(const Dog& d);
    bool updateDog(const Dog& oldDog, const Dog& newDog);

    std::vector<Dog> getAllDogs() const;
    std::vector<Dog> getDogsByBreed (const std::string& breed) const;
    void adoptDog(const Dog& d);
    static bool invalidDog(const Dog& d) ;

    std::vector<Dog> getAdoptedDogs() const;
};

//ioabsdubas

#endif //SERVICE_H
