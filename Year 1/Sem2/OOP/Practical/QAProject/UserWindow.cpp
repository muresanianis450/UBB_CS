#include "UserWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

UserWindow::UserWindow(Service& s, User u) : service(s), currentUser(u) {
    service.addObserver(this);

    this->setWindowTitle(QString::fromStdString(currentUser.getName()));
    auto* layout = new QVBoxLayout(this);

    questionList = new QListWidget;
    layout->addWidget(new QLabel("Questions"));
    layout->addWidget(questionList);

    questionInput = new QLineEdit;
    addQuestionButton = new QPushButton("Add Question");
    layout->addWidget(new QLabel("Add a question:"));
    layout->addWidget(questionInput);
    layout->addWidget(addQuestionButton);

    answerList = new QListWidget;
    layout->addWidget(new QLabel("Answers"));
    layout->addWidget(answerList);

    answerInput = new QLineEdit;
    addAnswerButton = new QPushButton("Add Answer");
    layout->addWidget(new QLabel("Answer selected question:"));
    layout->addWidget(answerInput);
    layout->addWidget(addAnswerButton);

    voteSpinBox = new QSpinBox;
    voteSpinBox->setMinimum(-1000);
    voteSpinBox->setMaximum(1000);
    layout->addWidget(new QLabel("Vote for selected answer:"));
    layout->addWidget(voteSpinBox);

    connect(addQuestionButton, &QPushButton::clicked, this, &UserWindow::handleAddQuestion);
    connect(addAnswerButton, &QPushButton::clicked, this, &UserWindow::handleAddAnswer);
    connect(questionList, &QListWidget::itemSelectionChanged, this, &UserWindow::handleQuestionSelectionChanged);
    connect(voteSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &UserWindow::handleVoteChanged);
    connect(answerList, &QListWidget::itemSelectionChanged, this, &UserWindow::handleAnswerSelectionChanged);

    update(); // Initial call to populate answers
}



void UserWindow::handleAddQuestion() {
    try {
        service.addQuestion(questionInput->text().toStdString(), currentUser.getName());
        questionInput->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::handleAddAnswer() {
    auto currentItem = questionList->currentItem();
    if (!currentItem) return;

    int qid = currentItem->data(Qt::UserRole).toInt();
    try {
        service.addAnswer(qid, currentUser.getName(), answerInput->text().toStdString());
        answerInput->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::handleQuestionSelectionChanged() {
    auto item = questionList->currentItem();
    if (!item) return;

    int qid = item->data(Qt::UserRole).toInt();
    reloadAnswers(qid);
}

void UserWindow::handleVoteChanged(int newValue) {
    auto item = answerList->currentItem();
    if (!item) return;

    int aid = item->data(Qt::UserRole).toInt();
    service.updateAnswerVotes(aid, newValue, currentUser.getName());
}

void UserWindow::handleAnswerSelectionChanged() {
    auto item = answerList->currentItem();
    if (!item) return;

    int aid = item->data(Qt::UserRole).toInt();
    for (const auto& answer : service.getAnswers()) {
        if (answer.getId() == aid) {
            voteSpinBox->blockSignals(true);
            voteSpinBox->setValue(answer.getVotes());
            voteSpinBox->blockSignals(false);
            return;
        }
    }
}

void UserWindow::reloadQuestions() {
    questionList->clear();
    auto questions = service.getQuestions();
    std::sort(questions.begin(), questions.end(), [this](const Question& q1, const Question& q2) {
        return service.getAnswersForQuestion(q1.getId()).size() > service.getAnswersForQuestion(q2.getId()).size();
    });

    for (const auto& q : questions) {
        QString text = QString::fromStdString(q.getText()) + " (" + QString::number(service.getAnswersForQuestion(q.getId()).size()) + ")";
        auto* item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, q.getId());
        questionList->addItem(item);
    }
}

void UserWindow::reloadAnswers(int questionId) {
    answerList->clear();
    auto answers = service.getAnswersForQuestion(questionId);
    std::sort(answers.begin(), answers.end(), [](const Answer& a1, const Answer& a2) {
        return a1.getVotes() > a2.getVotes();
    });

    for (const auto& a : answers) {
        QString text = QString("[%1] %2 - %3 (%4 votes)")
                .arg(QString::number(a.getId()))
                .arg(QString::fromStdString(a.getUser()))
                .arg(QString::fromStdString(a.getText()))
                .arg(QString::number(a.getVotes()));

        auto* item = new QListWidgetItem(text);
        item->setData(Qt::UserRole, a.getId());
        if (a.getUser() == currentUser.getName())
            item->setBackground(Qt::yellow);

        answerList->addItem(item);
    }
}
void UserWindow::update() {
    reloadQuestions();
    reloadAnswers(0); // Clear answers when questions are reloaded
    if (auto item = questionList->currentItem()) {
        reloadAnswers(item->data(Qt::UserRole).toInt());
    } else {
        answerList->clear();
    }
}
