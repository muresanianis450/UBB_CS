#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "PersonService.h"

class PersonWindow : public QWidget ,public Observer {
    Q_OBJECT
private:
    PersonService& service;
    QListWidget* personList;
    QLineEdit* nameInput;
    QPushButton* addPersonButton;

public:
    PersonWindow(PersonService& s, QWidget* parent = nullptr);
    ~PersonWindow() override = default;

    void update() override;

    private slots:
        void handleAddPerson();
};