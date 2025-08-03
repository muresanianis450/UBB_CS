#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"
#include "Observable.h"
#include "QLabel"

class ParticipantWindow: public QWidget, public Observer {
    Q_OBJECT
private:
    Service& service;
    std::string participantName;

    QTableWidget* table;
    QLineEdit *answerEdit;
    QPushButton* submitButton;
    QLabel* scoreLable;

    std::set<int> answeredQuestions;
private slots:
    void handleAnswerButton();
    void handleSelectionChanged();
public:
    ParticipantWindow(Service& service, const std::string& participantName);
    void update() override;

};