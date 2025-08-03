#pragma once
#include "PersonRepository.h"
#include "Person.h"
#include <vector>
#include <string>

#include "Observer.h"

class PersonService : public Observable {
private:
    PersonRepository& personRepository;

public:
    PersonService(PersonRepository& pr)
        : personRepository(pr) {}

    const std::vector<Person>& getAllPersons()const {
        return personRepository.getAllPersons();
    }
    bool add(const Person& person);
    Person* findPersonByName(const std::string& name);



};
