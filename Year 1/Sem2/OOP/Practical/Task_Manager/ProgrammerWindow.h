#pragma once
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTableView>
#include <QVBoxLayout>
#include <QLabel>
#include "TaskService.h"
#include "Observable.h"
#include "TaskModel.h"
class ProgrammerWindow : public QWidget, public Observer {
    Q_OBJECT

    Programmer programmer;
    TaskService& service;
    TaskModel* model;

    QTableView* table;
    QPushButton* addButton;
    QPushButton* startButton;
    QPushButton* doneButton;
    QLineEdit* inputLineEdit;
public:
    ProgrammerWindow(TaskService& service, Programmer prog, QWidget* parent = nullptr);
    void update() override;
    private slots:
    void handleAddButton();
    void handleStartButton();
    void handleDoneButton();
};