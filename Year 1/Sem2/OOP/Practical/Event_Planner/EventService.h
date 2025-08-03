#pragma once
#include "EventRepository.h"
#include "PersonRepository.h"
#include "Observer.h"
#include <vector>
#include <string>
#include <map>



class EventService : public Observable{
private:

    EventRepository& eventRepository;
    PersonRepository& personRepository;

    std::map<Event, std::vector<std::string>> attendees;
public:
    EventService(EventRepository& repo, PersonRepository& pr);

    const std::vector<Event>& getAllEvents()const;

    std::vector<Event> getAllEventsSortedByDate() const;

    std::vector<Event> getEventsNear(double lat, double lon,double radius =5.0) const;

    void addEvent(const Event& e);
    void updateEvent(const Event& updatedEvent);

    bool addAttendee(const Event& event, const std::string& attendee);
    const std::vector<std::string>& getAttendees(const Event& event) const;

    std::vector<Event> getMostPopular() const;
    Event* findEventByName(const std::string& name) ;




};