#pragma once
#include <QWidget>
#include "Service.h"
#include "Observer.h"
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>

class UserWindow : public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;
    User currentUser;

    QListWidget* questionList;
    QListWidget* answerList;
    QLineEdit* questionInput;
    QPushButton* addQuestionButton;
    QLineEdit* answerInput;
    QPushButton* addAnswerButton;
    QSpinBox* voteSpinBox;


    void reloadQuestions();
    void reloadAnswers(int questionId);
private slots:
   void handleAddQuestion();
    void handleAddAnswer();
    void handleQuestionSelectionChanged();
    void handleVoteChanged(int newValue);
    void handleAnswerSelectionChanged();


public:
    UserWindow(Service& s, User u);
    void update() override;
};
