
#include "EventRepository.h"
#include <fstream>
EventRepository::EventRepository() {
    std::ifstream fin("events.txt");
    Event e;
    while (fin >> e) {
        events.push_back(e);
    }
    fin.close();

}
void EventRepository::saveToFile() {
    std::ofstream fout("events.txt");
    for (auto& e : events) {
        fout << e << "\n";
    }
    fout.close();
}

const std::vector<Event>& EventRepository::getAllEvents() const {
    return events;
}
std::vector<Event> &EventRepository::getRefferencedEvents() {
    return events; // this will not be constant, therefore i can modify it usign the serv
}

void EventRepository::addEvent(const Event& e) {
   events.push_back(e);
    saveToFile();
}
