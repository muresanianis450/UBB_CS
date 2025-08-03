#include "ProgrammerWindow.h"
#include <QMessageBox>
#include <QHeaderView>
ProgrammerWindow::ProgrammerWindow(TaskService& service, Programmer prog, QWidget* parent)
    : QWidget(parent), service(service), programmer(std::move(prog)) {
    service.addObserver(this);

    this->setStyleSheet("background-color: pink; color: black;");
    table = new QTableView(this);
    addButton = new QPushButton("Add Task", this);
    startButton = new QPushButton("Start", this);
    doneButton = new QPushButton("Done", this);
    inputLineEdit = new QLineEdit(this);

    model = new TaskModel(this);
    model->setTasks(service.getTasks());
    table->setModel(model);
    //for stretching
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setMinimumSize(600, 400);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    table->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);



    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel(QString("Programmer: %1").arg(QString::fromStdString(programmer.getName())), this);
    mainLayout->addWidget(titleLabel);

    mainLayout->addWidget(table);
    mainLayout->addWidget(inputLineEdit);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(doneButton);

    mainLayout->addLayout(buttonsLayout);


    setLayout(mainLayout);

    connect(addButton, &QPushButton::clicked, this, &ProgrammerWindow::handleAddButton);
    connect(startButton, &QPushButton::clicked, this, &ProgrammerWindow::handleStartButton);
    connect(doneButton, &QPushButton::clicked, this, &ProgrammerWindow::handleDoneButton);


    update();
}

void ProgrammerWindow::update() {
    model->refresh(service.getTasks());
}


void ProgrammerWindow::handleAddButton() {
    QString desc = inputLineEdit->text().trimmed();
    if (desc.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Please enter a task description.");
        return;
    }
    try {
        service.addTask(desc.toStdString());
        inputLineEdit->clear();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
void ProgrammerWindow::handleStartButton() {
    QModelIndexList selected = table->selectionModel()->selectedRows();
    if (selected.empty()) {
        QMessageBox::warning(this, "Warning", "please select a task");
        return;
    }
    int row = selected.first().row();
    QString desc = model->data(model->index(row, 0)).toString();
    try {
        service.startTask(desc.toStdString(), programmer.getId());
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
void ProgrammerWindow::handleDoneButton() {
    QModelIndexList selected = table->selectionModel()->selectedRows();
    if (selected.empty()) {
        QMessageBox::warning(this, "Warning", "please select a task");
        return;
    }
    int row = selected.first().row();
    QString desc = model->data(model->index(row, 0)).toString();
    try {
        service.completeTask(desc.toStdString(), programmer.getId());
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
