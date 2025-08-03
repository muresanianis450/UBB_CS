

#include "ParticipantWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
ParticipantWindow::ParticipantWindow(Service& service, const std::string& name) : service(service) , participantName(name){
    service.addObserver(this);
    setWindowTitle(QString::fromStdString(participantName));

    setStyleSheet("background-color: pink; color: black;");
    auto* mainLayout = new QVBoxLayout(this);

    table = new QTableWidget();

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(600, 400);
    table->setColumnCount(3);
    QStringList headers{"ID", "Text", "Score"};
    table->setHorizontalHeaderLabels(headers);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);

    mainLayout->addWidget(table);

    auto* formLayout = new QFormLayout();
    answerEdit = new QLineEdit();
    formLayout->addRow("Your Answer:", answerEdit);
    mainLayout->addLayout(formLayout);

    submitButton = new QPushButton("Answer");
    submitButton->setEnabled(false); // initially disabled
    mainLayout->addWidget(submitButton);

    scoreLable = new QLabel("Score: 0");
    mainLayout->addWidget(scoreLable);

    connect(submitButton, &QPushButton::clicked, this, &ParticipantWindow::handleAnswerButton);
    connect(table->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ParticipantWindow::handleSelectionChanged);
    update();

}
void ParticipantWindow::update() {
    auto questions = service.getQuestionsSortedByScoreDesc();

    // Filter out already answered questions
    std::vector<Question> filtered;
    for (const auto& q : questions) {
        if (answeredQuestions.count(q.getID()) == 0) {
            filtered.push_back(q);
        }
    }

    table->clearContents();
    table->setRowCount((int)filtered.size());

    for (int i = 0; i < (int)filtered.size(); ++i) {
        const auto& q = filtered[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::number(q.getID())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(q.getText())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(q.getScore())));
    }

    submitButton->setEnabled(false);

    int score = service.getScoreForParticipant(participantName);
    scoreLable->setText(QString("Score: %1").arg(QString::number(score)));
}

void ParticipantWindow::handleAnswerButton() {
    if (!table->selectionModel()->hasSelection()) {
        QMessageBox::warning(this, "Selection Error", "Please select a question first.");
        return;
    }

    int row = table->currentRow();
    int id = table->item(row, 0)->text().toInt();
    std::string answer = answerEdit->text().toStdString();

    if (answer.empty()) {
        QMessageBox::warning(this, "Input Error", "enter a text");
        return;
    }

    bool success = service.answerQuestion(participantName, id, answer);
    if (!success) {
        QMessageBox::information(this, "Answer", "this is already answered by you or is wrong");
    } else {
        QMessageBox::information(this, "Answer", "correct answer!");
        answeredQuestions.insert(id);
        update();
    }

    answerEdit->clear();
}
void ParticipantWindow::handleSelectionChanged() {
    submitButton->setEnabled(table->selectionModel()->hasSelection());
}