// EventWindow.cpp
#include "EventWindow.h"
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

EventWindow::EventWindow(EventService& s, QWidget* parent)
    : QWidget(parent), service(s) {
    service.addObserver(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    eventList = new QListWidget(this);
    mainLayout->addWidget(new QLabel("All Events:"));
    mainLayout->addWidget(eventList);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Event name");
    attenderInput = new QLineEdit(this);
    attenderInput->setPlaceholderText("Person name");
    addAttenderButton = new QPushButton("Add Attender", this);

    inputLayout->addWidget(nameInput);
    inputLayout->addWidget(attenderInput);
    inputLayout->addWidget(addAttenderButton);
    mainLayout->addLayout(inputLayout);

    connect(addAttenderButton, &QPushButton::clicked, this, &EventWindow::handleAddAttender);

    popularList = new QListWidget(this);
    mainLayout->addWidget(new QLabel("Most Popular Events:"));
    mainLayout->addWidget(popularList);

    update();
}

void EventWindow::handleAddAttender() {
    std::string eventName = nameInput->text().toStdString();
    std::string attenderName = attenderInput->text().toStdString();

    Event* event = service.findEventByName(eventName);
    if (event == nullptr) {
        QMessageBox::warning(this, "Error", "Event not found.");
        return;
    }

    if (!service.addAttendee(*event, attenderName)) {
        QMessageBox::information(this, "Info", "Attender already added.");
        return;
    }

    try {
        service.updateEvent(*event);
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }

    nameInput->clear();
    attenderInput->clear();
    update(); // Refresh UI after adding
}

void EventWindow::updateEventList() {
    eventList->clear();
    for (const auto& e : service.getAllEvents()) {
        QString line = QString("Event: %1 | Attendees: ")
                       .arg(QString::fromStdString(e.getName()));
        const auto& attendees = service.getAttendees(e);
        for (size_t i = 0; i < attendees.size(); ++i) {
            line += QString::fromStdString(attendees[i]);
            if (i < attendees.size() - 1) line += ", ";
        }
        eventList->addItem(line);
    }
}

void EventWindow::updatePopularList() {
    popularList->clear();
    for (const auto& e : service.getMostPopular()) {
        int attendeeCount = static_cast<int>(service.getAttendees(e).size());
        popularList->addItem(
            QString("%1 (%2 attendees)")
                .arg(QString::fromStdString(e.getName()))
                .arg(QString::number(attendeeCount))
        );
    }
}

void EventWindow::update() {
    updateEventList();
    updatePopularList();
}