#include "PresenterWindow.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>

PresenterWindow::PresenterWindow(Service& service) : service(service) {
    service.addObserver(this);

    this->setWindowTitle("Presenter");

    this->setStyleSheet("background-color: darkblue; color: white;");
    auto* mainLayout = new QVBoxLayout(this);


    table = new QTableWidget();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(600, 400);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);

    table->setColumnCount(4);
    QStringList headers{"ID", "Text", "Correct Answer", "Score"};
    table->setHorizontalHeaderLabels(headers);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(table);


    auto* formLayout = new QFormLayout();
    idEdit = new QLineEdit();
    textEdit = new QLineEdit();
    answerEdit = new QLineEdit();
    scoreEdit = new QLineEdit();

    formLayout->addRow("ID:", idEdit);
    formLayout->addRow("Text:", textEdit);
    formLayout->addRow("Correct Answer:", answerEdit);
    formLayout->addRow("Score:", scoreEdit);
    mainLayout->addLayout(formLayout);

    // Add button
    addButton = new QPushButton("Add Question");
    mainLayout->addWidget(addButton);


    connect(addButton, &QPushButton::clicked, this, &PresenterWindow::handleAddButton);
    update();
}

void PresenterWindow::handleAddButton() {
    bool ok1, ok2;
    int id = idEdit->text().toInt(&ok1);
    int score = scoreEdit->text().toInt(&ok2);
    std::string text = textEdit->text().toStdString();
    std::string correctAnswer = answerEdit->text().toStdString();

    if (!ok1 || !ok2 || text.empty() || correctAnswer.empty()) {
        QMessageBox::warning(this, "Input Error", "Invalid input data!");
        return;
    }

    bool success = service.addQuestion(id, text, correctAnswer, score);
    if (!success) {
        QMessageBox::warning(this, "Error", "Question with this ID already exists.");
    }

    idEdit->clear();
    textEdit->clear();
    answerEdit->clear();
    scoreEdit->clear();

}

void PresenterWindow::update() {
    auto questions = service.getQuestionSortedById();

    table->clearContents();
    table->setRowCount((int)questions.size());

    for (int i = 0; i < questions.size(); ++i) {
        const auto& q = questions[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::number(q.getID())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(q.getText())));
        table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(q.getCorrectAnswer())));
        table->setItem(i, 3, new QTableWidgetItem(QString::number(q.getScore())));
    }
}
