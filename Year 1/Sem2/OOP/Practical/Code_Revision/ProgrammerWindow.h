#pragma once
#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include  <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>

#include "Service.h"
#include "Observable.h"


class ProgrammerWindow : public QWidget, public Observer{
Q_OBJECT
private:
    Programmer programmer;
    Service& service;

    QListWidget* fileList;
    QLabel* revisedLabel;
    QLabel* remainingLabel;
    QLineEdit* addLineEdit;
    QPushButton* addButton;
    QPushButton* reviseButton;
    QVBoxLayout* layout;

    void update();
public slots:
    void handleAdd();
    void handleRevise();
public:
    ProgrammerWindow(Service& s, const Programmer& p, QWidget* parent = nullptr);

};



