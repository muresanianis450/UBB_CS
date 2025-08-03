#include <QApplication>
#include "PersonRepository.h"
#include "EventRepository.h"
#include "PersonService.h"
#include "EventService.h"
#include "PersonWindow.h"
#include "EventWindow.h"
#include <iostream>
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    PersonRepository personRepo;
    EventRepository eventRepo;

    PersonService personService(personRepo);
    EventService eventService(eventRepo,personRepo);

    // Launch EventWindow and hold it
    std::unique_ptr<EventWindow> eventWindow = std::make_unique<EventWindow>(eventService);
    eventWindow->show();
    std::cout << "Persons count: " << personRepo.getAllPersons().size() << std::endl;
    std::cout << "Events count: " << eventRepo.getAllEvents().size() << std::endl;
    // Launch PersonWindows
    std::vector<std::unique_ptr<PersonWindow>> windows;
    for (const auto& person : personRepo.getAllPersons()) {
        auto window = std::make_unique<PersonWindow>(personService, nullptr);
        window->show();
        windows.push_back(std::move(window));
    }

    return app.exec();
}