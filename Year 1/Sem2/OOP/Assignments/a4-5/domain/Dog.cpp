//
// Created by mures on 3/23/2025.
//

#include "Dog.h"
#include <iostream>
#include <string>

Dog::Dog(): age{0}, name{"Unknown"}, breed{"Unknown"},photography{"Unknown"} {}


Dog::Dog(const std::string &name, const std::string &breed, int age, const std::string &photography)
    : name(name), breed(breed), age(age), photography(photography) {}

Dog:: ~Dog(){}

Dog:: Dog(const Dog &d)
    {
      this -> age = d.age;
      this -> name = d.name;
      this -> breed = d.breed;
      this -> photography = d.photography;
    }
void Dog::setAge(int age){
  if(age<0)
    return;

  this->age = age;
  }

void Dog::setName(const std::string &name){
    this->name = name;
    }
void Dog::setBreed(const std::string &breed){
    this->breed = breed;
    }

void Dog::setPhotography(const std::string &photography){
    this->photography = photography;
    }

int Dog::getAge() const{
    return age;
    }
const std::string &Dog::getName() const {
    return name;
}
const std::string &Dog::getBreed() const {
    return breed;
}
const std::string &Dog::getPhotography() const {
    return photography;
}

bool Dog::operator==(const Dog& d) {
    return this->age == d.age &&
        this->name == d.name &&
            this->breed == d.breed &&
                this->photography == d.photography;
}

