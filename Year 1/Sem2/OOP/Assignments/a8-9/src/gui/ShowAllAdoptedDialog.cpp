#include "ShowAllAdoptedDialog.h"
#include <QHeaderView>
#include <QLabel>

ShowAllAdoptedDialog::ShowAllAdoptedDialog(std::unique_ptr<AdoptionList> adoptionList, QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("All Adopted Dogs");
    resize(600, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QTableWidget* table = new QTableWidget(this);
    table->setColumnCount(4);
    table->setHorizontalHeaderLabels({"Name", "Breed", "Age", "Photography"});
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    populateTable(adoptionList->getAdoptedDogs());
    layout->addWidget(table);
}

void ShowAllAdoptedDialog::populateTable(const std::vector<Dog>& dogs) {
    auto* table = findChild<QTableWidget*>();
    if (!table) return;

    table->setRowCount(static_cast<int>(dogs.size()));
    for (int i = 0; i < dogs.size(); ++i) {
        const Dog& dog = dogs[i];
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(dog.getName())));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(dog.getBreed())));
        table->setItem(i, 2, new QTableWidgetItem(QString::number(dog.getAge())));
        table->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(dog.getPhotography())));
    }
}