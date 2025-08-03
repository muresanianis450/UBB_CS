#pragma once
#include "Event.h"
#include <vector>
#include <string>

class EventRepository {
private:
    std::vector<Event> events;


    void saveToFile();

public:
    EventRepository();
    const std::vector<Event>& getAllEvents() const;
    std::vector<Event>& getRefferencedEvents();
    void addEvent(const Event& e);
    std::vector<std::string> getAtteners(Event& e) const {
        return e.getAttendees();
    };


};