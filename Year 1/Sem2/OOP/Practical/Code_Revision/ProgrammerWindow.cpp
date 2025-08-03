
#include "ProgrammerWindow.h"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>
ProgrammerWindow::ProgrammerWindow(Service& s, const Programmer& p , QWidget* parent)
    : QWidget(parent), service(s), programmer(p) {
    this->setWindowTitle(QString::fromStdString(programmer.getName()));
    this->setStyleSheet("background-color: pink;");


    fileList = new QListWidget(this);
    revisedLabel = new QLabel(this);
    remainingLabel = new QLabel(this);
    addLineEdit = new QLineEdit(this);
    addButton = new QPushButton("Add", this);
    reviseButton = new QPushButton("Revise", this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(fileList);
    layout->addWidget(revisedLabel);
    layout->addWidget(remainingLabel);
    layout->addWidget(addLineEdit);
    layout->addWidget(addButton);
    layout->addWidget(reviseButton);

    this->setLayout(layout);

    QObject::connect(addButton,&QPushButton::clicked,this,&ProgrammerWindow::handleAdd);
    QObject::connect(reviseButton,&QPushButton::clicked,this,&ProgrammerWindow::handleRevise);
    update();
}

void ProgrammerWindow::update() {
//filelistupdate
    fileList->clear();
    std::vector<SourceFile> files = service.getSortedFiles();

    for (const auto& file: files) {
        QString itemString = QString::fromStdString(file.getName() + " " + (file.isRevised() ? "revised" : "not_revised")
            + " " +file.getCreator() + " " + file.getReviewer());

        QListWidgetItem* item = new QListWidgetItem(itemString);
        if (file.isRevised()) {
            QFont boldFont;
            boldFont.setBold(true);
            item->setFont(boldFont);
        }else {
            item->setBackground(Qt::red);
        }
        fileList->addItem(item);
    }
//countUpdate
    for (const auto& p : service.getProgrammers()) {
        if (p.getName() == programmer.getName()) {
            revisedLabel->setText("Revised: "+ QString::number(p.getRevised()));
            remainingLabel->setText("Remaining: "+ QString::number(p.getRemaining()));
            if (p.getRemaining() == 0) {
                QMessageBox::information(this, "Done", "All files revised!)");
            }

        }
    }
}
void ProgrammerWindow::handleAdd() {
    std::string name = addLineEdit->text().toStdString();
    try {
        service.addFile(name, programmer.getName());
        addLineEdit->clear();

     } catch (std::exception& e) {
         QMessageBox::information(this, "Error", e.what());
     }
}
void ProgrammerWindow::handleRevise() {
    QListWidgetItem* item = fileList->currentItem();
    if (!item) return;
    std::string line = item->text().toStdString();
    std::string fileName = line.substr(0,line.find(' '));
    try {
        service.reviseFile(fileName, programmer.getName());
        update();
    }catch (std::exception& e) {
        QMessageBox::information(this, "Error", e.what());
    }


}
