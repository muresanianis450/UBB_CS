
#include "Event.h"
#include <sstream>
Event::Event(const std::string &organiser, const std::string &name, const std::string &description,
             double latitude, double longitude, const std::string &date,
             const std::vector<std::string> &attendees)
        : organiser(organiser), name(name), description(description),
          latitude(latitude), longitude(longitude), date(date), attendees(attendees) {}

std::string Event::getDate() const {
    return date;
}
std::string Event::getDescription() const {
    return description;
}
std::string Event::getName() const {
    return name;
}
std::string Event::getOrganiser() const {
    return organiser;
}
double Event::getLatitude() const {
    return latitude;
}
double Event::getLongitude() const {
    return longitude;
}


std::istream& operator>>(std::istream& is, Event& e) {
    std::string header;
    if (!std::getline(is, header)) return is;

    std::stringstream ss(header);
    std::string organiser, name, description, date, latStr, lonStr;
    double lat = 0.0, lon = 0.0;

    std::getline(ss, organiser, ',');
    std::getline(ss, name, ',');
    std::getline(ss, description, ',');
    std::getline(ss, latStr, ',');
    std::getline(ss, lonStr, ',');
    std::getline(ss, date);

    try {
        lat = std::stod(latStr);
        lon = std::stod(lonStr);
    } catch (...) {
        lat = 0.0;
        lon = 0.0;
    }

    std::vector<std::string> attendees;
    std::string line;
    while (std::getline(is, line)) {
        if (line == "END") break;
        if (!line.empty()) {
            attendees.push_back(line);
        }
    }

    e = Event(organiser, name, description, lat, lon, date, attendees);
    return is;
}
std::ostream& operator<<(std::ostream& os, const Event& event) {
    os << event.getOrganiser() << ","
       << event.getName() << ","
       << event.getDescription() << ","
       << event.getLatitude() << ","
       << event.getLongitude() << ","
       << event.getDate() << "\n";

    for (const auto& attendee : event.getAttendees()) {
        os << attendee << "\n";
    }
    os << "END\n";
    return os;
}

const std::vector<std::string>& Event::getAttendees() const {
    return attendees;
}

void Event::setAttendees(const std::vector<std::string>& attendees) {
    this->attendees = attendees;
}

bool Event::operator<(const Event& other) const {
    if (name != other.name) return name < other.name;
    if (latitude != other.latitude) return latitude < other.latitude;
    return longitude < other.longitude;
}

bool Event::operator==(const Event& other) const {
    return name == other.name && latitude == other.latitude && longitude == other.longitude;
}