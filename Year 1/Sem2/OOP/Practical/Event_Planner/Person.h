#pragma once
#include <string>

class Person {
private:
    std::string name;
    double latitude;
    double longitude;
    bool isOrganizer;

public:
    Person(): name(""), latitude(0), longitude(0), isOrganizer(false) {}
    Person(std::string name, double lat,double lon, bool isOrg);
    explicit Person(const std::string& name): Person(name,0,0,false){}


    std::string getName() const;
    double getLatitude() const;
    double getLongitude() const;
    bool getIsOrganizer() const;

    friend std::istream& operator>>(std::istream& is, Person& person);
    friend std::ostream& operator<<(std::ostream& os, const Person& person);
};
