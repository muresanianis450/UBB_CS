#include "PersonWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

PersonWindow::PersonWindow(PersonService& s, QWidget* parent)
    : QWidget(parent), service(s) {

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    personList = new QListWidget(this);
    mainLayout->addWidget(new QLabel("All Persons:"));
    mainLayout->addWidget(personList);

    QHBoxLayout* inputLayout = new QHBoxLayout();
    nameInput = new QLineEdit(this);
    nameInput->setPlaceholderText("Person name");
    addPersonButton = new QPushButton("Add Person", this);

    inputLayout->addWidget(nameInput);
    inputLayout->addWidget(addPersonButton);
    mainLayout->addLayout(inputLayout);

    connect(addPersonButton, &QPushButton::clicked, this, &PersonWindow::handleAddPerson);

    service.addObserver(this);
    update();
}

void PersonWindow::handleAddPerson() {
    std::string personName = nameInput->text().toStdString();

    if (personName.empty()) {
        QMessageBox::warning(this, "Error", "Name cannot be empty.");
        return;
    }

    Person p(personName);  // Construct person object

    if (!service.add(p)) {
        QMessageBox::information(this, "Info", "Person already exists.");
        return;
    }

    nameInput->clear();
}

void PersonWindow::update() {
    personList->clear();
    for (const auto& p : service.getAllPersons()) {
        personList->addItem(QString::fromStdString(p.getName()));
    }
}
