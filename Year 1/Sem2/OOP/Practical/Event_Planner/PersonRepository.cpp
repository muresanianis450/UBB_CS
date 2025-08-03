
#include "PersonRepository.h"
#include <fstream>
PersonRepository::PersonRepository() {
    std::ifstream fin("people.txt");
    Person p;
    while ( fin >> p ) {
        persons.push_back(p);

    }
    fin.close();
}

const std::vector<Person>& PersonRepository::getAllPersons() const {
    return persons;
}
std::vector<Person>& PersonRepository::getRefferencedPersons() {
    return persons;
}

