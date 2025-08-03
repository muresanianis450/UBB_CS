#pragma once
#include "Person.h"
#include <vector>
#include <string>

class PersonRepository {
private:
    std::vector<Person> persons;

public:
    PersonRepository();
    const std::vector<Person>& getAllPersons() const;
    std::vector<Person>& getRefferencedPersons();
    void add(const Person& person) {
        persons.push_back(person);
    }
};