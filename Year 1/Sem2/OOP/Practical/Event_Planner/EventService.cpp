

#include "EventService.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

EventService::EventService(EventRepository& repo, PersonRepository& personRepo)
    : eventRepository(repo), personRepository(personRepo) {
    for (const auto& event : eventRepository.getAllEvents()) {
        attendees[event] = event.getAttendees();

    }
//
}
const std::vector<Event>& EventService::getAllEvents() const {
    return eventRepository.getAllEvents();
}
std::vector<Event>EventService::getAllEventsSortedByDate()const  {
    std::vector<Event> sortedEvents = eventRepository.getAllEvents();

    std::sort(sortedEvents.begin(), sortedEvents.end(),
        [](const Event& e1, const Event& e2) {
            return e1.getDate() < e2.getDate();
        });
    return sortedEvents;
}
std::vector<Event> EventService::getEventsNear(double lat, double lon, double radius) const {
    std::vector<Event> eventsNear;
    for (const auto& e : eventRepository.getAllEvents()) {
        if (std::sqrt((lat - e.getLatitude())*(lat - e.getLatitude()) + (lon - e.getLongitude())*(lon - e.getLongitude()) )<= radius)
            eventsNear.push_back(e);
    }
    return eventsNear;
}

void EventService::addEvent(const Event& event) {
    for (const auto& e : eventRepository.getAllEvents()) {
        if (e.getName() == event.getName() &&
            e.getLatitude() == event.getLatitude() &&
            e.getLongitude() == event.getLongitude()) {
            throw std::runtime_error("Event with same name and location already exists");
            }
    }
    eventRepository.addEvent(event);
    attendees[event] = {};
    notifyObservers();
}

void EventService::updateEvent(const Event& updatedEvent) {
    auto& events = eventRepository.getRefferencedEvents();

    bool found = false;

    for (auto& e : events) {
        if (e.getName() == updatedEvent.getName()) {
            e= updatedEvent;
            found = true;
            break;
        }
    }
if (!found) {
    throw std::runtime_error("event to update couldnt be found");

}
    notifyObservers();
}

bool EventService::addAttendee(const Event &event, const std::string &atender) {
    for (auto& [e,attenders]:attendees) {
        if (e.getName() == event.getName()) {
            auto it = std::find(attenders.begin(), attenders.end(), atender);
            if (it != attenders.end()) {
                return false;
            }
            attenders.push_back(atender);
            notifyObservers();
            return true;
        }
    }
    attendees[event].push_back(atender);
    notifyObservers();
    return true;
}
const std::vector<std::string>& EventService::getAttendees(const Event& event) const {
    static std::vector<std::string> empty;
    auto it = attendees.find(event);
    return (it != attendees.end()) ? it->second : empty;
}


std::vector<Event> EventService::getMostPopular() const {
    std::vector<std::pair<Event, int>> eventPopularity;

    for (const auto& e : eventRepository.getAllEvents()) {
        int count = getAttendees(e).size();
        eventPopularity.emplace_back(e, count);
    }

    std::sort(eventPopularity.begin(), eventPopularity.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });

    std::vector<Event> popularEvents;
    for (const auto& pair : eventPopularity) {
        popularEvents.push_back(pair.first);
    }
    return popularEvents;
}


Event* EventService::findEventByName(const std::string& name) {
    for (auto& event : eventRepository.getRefferencedEvents()) {
        if (event.getName() == name) {
            return &event;
        }
    }
    return nullptr;
}