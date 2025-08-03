#pragma once
#include <string>
#include <vector>

class Event {
private:
    std::string organiser;
    std::string name;
    std::string description;
    double latitude;
    double longitude;
    std::string date;
    std::vector<std::string> attendees;

public:
    Event(): organiser(""), name(""), description(""), latitude(0.0), longitude(0.0), date(""),attendees{""} {}

    Event(const std::string& organiser, const std::string& name, const std::string& description,
         double latitude, double longitude, const std::string& date,
         const std::vector<std::string>& attendees);

    std::string getOrganiser() const;
    std::string getName() const;
    std::string getDescription() const;
    double getLatitude() const;
    double getLongitude() const;
    std::string getDate() const;

    friend std::istream& operator>>(std::istream& is, Event& e);
    friend std::ostream& operator<<(std::ostream& os, const Event& e);
    bool operator<(const Event& other) const;
    bool operator==(const Event& other) const;
    const std::vector<std::string>& getAttendees() const;
    void setAttendees(const std::vector<std::string>& attendees);

};