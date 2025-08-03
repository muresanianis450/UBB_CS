// PersonService.cpp

#include "PersonService.h"

Person* PersonService::findPersonByName(const std::string& name) {
    auto& persons = personRepository.getRefferencedPersons();
    for (auto& p : persons) {
        if (p.getName() == name) {
            return &p;
        }
    }
    return nullptr;
}

bool PersonService::add(const Person& person) {
    for (const auto& p : personRepository.getAllPersons()) {
        if (p.getName() == person.getName())
            return false;
    }
    personRepository.add(person);
    notifyObservers();
    return true;
}