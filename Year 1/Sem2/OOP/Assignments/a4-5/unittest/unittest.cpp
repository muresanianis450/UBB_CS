//
// Created by mures on 3/25/2025.
//
#include <iostream>
#include <vector>
#include <cassert>
#include "../domain/Dog.h"
#include "../repository/DynamicVector.h"
#include "../repository/Repo.h"
#include "../service/service.h"
#include "DynamicVector_01.h"
#include "Validator.h"
#include <sstream>

void testDog() {
    // Constructor and getters
    Dog d1("Rex", "Pitbull", 4, "url.com/rex.jpg");
    assert(d1.getName() == "Rex");
    assert(d1.getBreed() == "Pitbull");
    assert(d1.getAge() == 4);
    assert(d1.getPhotography() == "url.com/rex.jpg");

    // Setters
    d1.setAge(5);
    d1.setName("Rexie");
    d1.setBreed("Boxer");
    d1.setPhotography("new-url.com");
    assert(d1.getAge() == 5);
    assert(d1.getName() == "Rexie");
    assert(d1.getBreed() == "Boxer");
    assert(d1.getPhotography() == "new-url.com");

    // Negative age (should not update)
    d1.setAge(-10);
    assert(d1.getAge() == 5); // Still 5

    // Copy constructor
    Dog d2 = d1;
    assert(d2 == d1);

    // Equality with different dog
    Dog dDiff("Rexie", "Boxer", 5, "different-url.com");
    assert(!(d1 == dDiff));

    // Default constructor
    Dog d3;
    assert(d3.getName() == "Unknown");

    // Assignment operator
    d3 = d1;
    assert(d3 == d1);

    // Self-assignment (just to be safe)
    d3 = d3;
    assert(d3 == d1);


}


void testDynamicArray() {
    DynamicArray<int> arr(2);
    assert(arr.getLength() == 0);
    assert(arr.getCapacity() == 2);

    arr.append(1);
    arr.append(2);
    assert(arr.getLength() == 2);

    arr.append(3); // triggers resize
    assert(arr.getCapacity() >= 3);
    assert(arr[2] == 3);

    arr.remove(1); // remove 2
    assert(arr.getLength() == 2);
    assert(arr[0] == 1);
    assert(arr[1] == 3);

    arr.update(1, 10);
    assert(arr[0] == 10);

    DynamicArray<int> copyArr = arr;
    assert(copyArr.getLength() == arr.getLength());

    DynamicArray<int> assigned;
    assigned = arr;
    assert(assigned.getLength() == arr.getLength());

    arr.remove(-1); // should do nothing, not crash
    arr.remove(100); // should do nothing
    assert(arr.getLength() == 2); // length unchanged

    arr = arr; // self-assignment
    assert(arr.getLength() == 2); // no change, no crash

    arr[1] = 99;
    assert(arr[1] == 99);

    bool updated = arr.update(123456, 0); // element doesn't exist
    assert(!updated);


}

void testRepo() {
    Repository repo;
    Dog testDog("Bolt", "Husky", 3, "url");

    repo.addDog(testDog);
    assert(repo.getAllDogs().getLength() == 11); // Includes the 10 predefined dogs + 1 added

    assert(!repo.removeDog(Dog("Ghost", "Wolf", 10, "none")));
    assert(repo.removeDog(testDog));

    Dog newDog("Bolt", "Husky", 4, "updated-url");
    repo.addDog(testDog);
    assert(repo.updateDog(testDog, newDog));
    assert(!repo.updateDog(Dog("Not", "Found", 2, "none"), newDog));

    DynamicArray<Dog> huskies = repo.getDogs_by_breed("Husky");
    for (int i = 0; i < huskies.getLength(); ++i)
        assert(huskies[i].getBreed() == "Husky");
}


void testService() {
    Service service;
    Dog dog("Milo", "Corgi", 2, "photo.jpg");

    service.addDog(dog);
    DynamicArray<Dog>& all = service.getAllDogs();
    bool found = false;
    for (int i = 0; i < all.getLength(); ++i)
        if (all[i] == dog)
            found = true;
    assert(found);

    Dog updatedDog("Milo", "Corgi", 3, "updated.jpg");
    assert(service.updateDog(dog, updatedDog));
    assert(service.removeDog(updatedDog));

    service.adoptDog(updatedDog);
    auto adopted = service.getAdoptedDogs();

    assert(adopted.size() == 1 && adopted[0] == updatedDog);


    Dog nonExistent("Ghost", "Spirit", 5, "ghost.jpg");
    Dog newVersion("Ghost", "Spirit", 6, "spirit.jpg");
    assert(service.updateDog(nonExistent, newVersion) == false);

    assert(service.removeDog(nonExistent) == false);

    DynamicArray<Dog> huskies = service.getDogsByBreed("Husky");
    assert(huskies.getLength() == 0);

    service.addDog(Dog("Nina", "Labrador", 3, "nina.jpg"));
    service.addDog(Dog("Bo", "Labrador", 4, "bo.jpg"));
    DynamicArray<Dog> labs = service.getDogsByBreed("Labrador");
    assert(labs.getLength() == 2);

    int lenBefore = service.getAllDogs().getLength();
    service.addDog(Dog("Spike", "Bulldog", 6, "spike.jpg"));
    assert(service.getAllDogs().getLength() == lenBefore + 1);


    Dog invalidDog("", "", -1, "");  // invalid dog (empty fields, negative age)
    try {
        service.addDog(invalidDog);  // should be caught by Validator, no throw
    } catch (const std::exception&) {
        // Exception is caught but not displayed
    }
    DynamicArray<Dog>& afterInvalid = service.getAllDogs();
    for (int i = 0; i < afterInvalid.getLength(); ++i) {
        assert(!(afterInvalid[i] == invalidDog));  // dog shouldn't be added
    }

    // -- Adopt multiple dogs and check order
    Dog a("A", "Akita", 2, "a.jpg");
    Dog b("B", "Beagle", 4, "b.jpg");

    service.adoptDog(a);
    service.adoptDog(b);

    auto adoptedDogs = service.getAdoptedDogs();
    assert(adoptedDogs.size() == 3);  // previously 1, now +2
    assert(adoptedDogs[1] == a);
    assert(adoptedDogs[2] == b);

    // Valid dog (should return false)
    Dog validDog("Buddy", "Golden Retriever", 3, "photo.jpg");
    assert(service.invalidDog(validDog) == false);

    // Invalid dog: empty name
    Dog invalidDog1("", "Bulldog", 2, "img.jpg");
    assert(service.invalidDog(invalidDog1) == true);

    // Invalid dog: empty breed
    Dog invalidDog2("Max", "", 4, "img.jpg");
    assert(service.invalidDog(invalidDog2) == true);

    // Invalid dog: negative age
    Dog invalidDog3("Max", "Husky", -5, "img.jpg");
    assert(service.invalidDog(invalidDog3) == true);

    // Invalid dog: empty photo
    Dog invalidDog4("Max", "Husky", 3, "");
    assert(service.invalidDog(invalidDog4) == true);

    // Completely invalid dog
    Dog invalidDog5("", "", -1, "");
    assert(service.invalidDog(invalidDog5) == true);
}



void runUnitTest() {
    testDog();
    testDynamicArray();
    testRepo();
    testService();
    std::cout << "All tests passed!" << std::endl;
}

