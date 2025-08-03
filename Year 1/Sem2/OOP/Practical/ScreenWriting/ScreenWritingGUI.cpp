#include "ScreenwritingGUI.h"
#include <QMessageBox>
#include <QHeaderView>

ScreenwritingGUI::ScreenwritingGUI(Service& service, const Writer& writer, QWidget* parent)
    : QWidget(parent), service(service), writer(writer)
{
    service.addObserver(this);
    model = new IdeaTableModel(service.getAllIdeas(), this);
    setStyleSheet("background-color: pink; color: black;");
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    descEdit = new QLineEdit(this);
    actEdit = new QLineEdit(this);

    addButton = new QPushButton("Add Idea", this);
    acceptButton = new QPushButton("Accept Idea", this);
    developButton = new QPushButton("Develop Idea", this);
    savePlotButton = new QPushButton("Save Plot", this);

    QHBoxLayout* formLayout = new QHBoxLayout;
    formLayout->addWidget(new QLabel("Description:", this));
    formLayout->addWidget(descEdit);
    formLayout->addWidget(new QLabel("Act (1-3):", this));
    formLayout->addWidget(actEdit);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(addButton);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(developButton);
    buttonsLayout->addWidget(savePlotButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
    setWindowTitle(QString::fromStdString("Screenwriting - ") + QString::fromStdString(writer.getName()));
    resize(800, 600);

    connect(addButton, &QPushButton::clicked, this, &ScreenwritingGUI::handleAddIdea);
    connect(acceptButton, &QPushButton::clicked, this, &ScreenwritingGUI::handleAcceptIdea);
    connect(savePlotButton, &QPushButton::clicked, this, &ScreenwritingGUI::handleSavePlot);


    update();
}





void ScreenwritingGUI::update() {
    model->setIdeas(service.getAllIdeas());
}
void ScreenwritingGUI::handleAddIdea() {
    try {
        std::string desc = descEdit->text().toStdString();
        int act = actEdit->text().toInt();
        service.addIdea(desc, writer.getName(), act);
        descEdit->clear();
        actEdit->clear();
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error adding idea", ex.what());
    }
}
void ScreenwritingGUI::handleAcceptIdea() {
    QModelIndex index = tableView->currentIndex();
    if (!index.isValid()) {
        QMessageBox::warning(this, "Select idea", "Please select an idea to accept.");
        return;
    }

    int row = index.row();
    const Idea& idea = service.getAllIdeas().at(row);
    try {
        service.acceptIdea(idea.getDescription(), idea.getAct(), writer.getName());
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error accepting idea", ex.what());
    }
}
void ScreenwritingGUI::handleSavePlot() {
    try {
        service.saveIdeasToFile("ideas.txt");
        QMessageBox::information(this, "Saved", "Plot saved successfully.");
    } catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error saving plot", ex.what());
    }
}
