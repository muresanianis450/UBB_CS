#include "StarWindow.h"
#include <QHeaderView>
#include <QHBoxLayout>

#include "StarViewWindow.h"
#include "QLabel"
#include "QMessageBox"
StarWindow::StarWindow(Service& service, const Astronomer& astronomer, QWidget* parent)
    : QWidget(parent), service(service), astronomer(astronomer) {

    setStyleSheet("background-color: pink; color: black;");
    this->setWindowTitle(QString::fromStdString(astronomer.getName()));
    service.addObserver(this);


    QVBoxLayout* mainLayout= new QVBoxLayout(this);
    filterCheckBox = new QCheckBox("show only stars in constelation" + QString::fromStdString(astronomer.getConstelation()));
    mainLayout->addWidget(filterCheckBox);

    QHBoxLayout* searchLayout = new QHBoxLayout();
    QLabel* searchLabel = new QLabel("Search: ");
    searchLineEdit = new QLineEdit();
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchLineEdit);
    mainLayout->addLayout(searchLayout);


    starTableView = new QTableView();
    starModel = new StarTableModel({},this);
    starTableView->setModel(starModel);
    starTableView->horizontalHeader() -> setSectionResizeMode(QHeaderView::Stretch);
    starTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    starTableView->setSelectionMode(QAbstractItemView::SingleSelection);
    mainLayout->addWidget(starTableView);


    QFormLayout* formLayout = new QFormLayout();
    nameLineEdit = new QLineEdit();
    raLineEdit = new QLineEdit();
    decLineEdit = new QLineEdit();
    diamterLineEdit = new QLineEdit();

    formLayout->addRow("Name", nameLineEdit);
    formLayout->addRow("RA", raLineEdit);
    formLayout->addRow("Dec", decLineEdit);
    formLayout->addRow("Diameter", diamterLineEdit);
    mainLayout->addLayout(formLayout);

    addStarButton = new QPushButton("Add Star");
    viewButton = new QPushButton("View");
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(addStarButton);
    buttonLayout->addWidget(viewButton);
    mainLayout->addLayout(buttonLayout);

    //load data
    currentStars = service.getAllStars();
    starModel->setStars(currentStars);

    connect(filterCheckBox, &QCheckBox::toggled, this, &StarWindow::handleFilter);
    connect(searchLineEdit, &QLineEdit::textChanged, this, &StarWindow::handleSearchTextChanged);
    connect(addStarButton, &QPushButton::clicked, this, &StarWindow::handleAddStar);
    connect(viewButton, &QPushButton::clicked, this, &StarWindow::handleViewStar);

    update();
}

void StarWindow::update() {
    std::vector<Star> filteredStars;
    if (filterCheckBox->isChecked()) {
        filteredStars = service.getStarsByConstellation(astronomer.getConstelation());
    } else {
        filteredStars = service.getAllStars();
    }

    // Apply search filtering
    QString searchText = searchLineEdit->text();
    if (!searchText.isEmpty()) {
        std::vector<Star> searchedStars;
        for (const auto& star : filteredStars) {
            if (QString::fromStdString(star.getName()).contains(searchText, Qt::CaseInsensitive))
                searchedStars.push_back(star);
        }
        filteredStars = std::move(searchedStars);
    }

    currentStars = filteredStars;
    starModel->setStars(currentStars);
}
void StarWindow::handleFilter(bool checked) {
    Q_UNUSED(checked);
    update();
}
void StarWindow::handleSearchTextChanged(const QString& text) {
    Q_UNUSED(text);
    update();
}
void StarWindow::handleAddStar() {
    try {
        std::string name = nameLineEdit->text().toStdString();
        int ra = raLineEdit->text().toInt();
        int dec = decLineEdit->text().toInt();
        int diameter = diamterLineEdit->text().toInt();

        service.addStar(name,astronomer.getConstelation(),ra,dec,diameter);

        nameLineEdit->clear();
        raLineEdit->clear();
        decLineEdit->clear();
        diamterLineEdit->clear();
        QMessageBox::information(this, "Success", "Star added Succesfully");
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", QString::fromStdString(e.what()));
    }

}


void StarWindow::handleViewStar() {
    QModelIndexList selectedIndexes = starTableView->selectionModel()->selectedRows();
    if (selectedIndexes.empty()) {
        QMessageBox::warning(this, "No selection", "Please select a star to view.");
        return;
    }
    int selectedRow = selectedIndexes.first().row();

    try {
        Star selectedStar = starModel->getStarAt(selectedRow);

        // Get all stars in the same constellation
        std::vector<Star> constellationStars = service.getStarsByConstellation(selectedStar.getConstelation());

        StarViewWindow* viewWindow = new StarViewWindow(constellationStars, selectedStar, this);
        viewWindow->exec();
    }
    catch (const std::exception& ex) {
        QMessageBox::warning(this, "Error", ex.what());
    }
}




