#include "CourierCompanyWindow.h"
#include <QHeaderView>
#include <QStandardItem>
#include <QMessageBox>

CourierCompanyWindow::CourierCompanyWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service)
{
    setStyleSheet("background-color: pink; color: black;");
    setWindowTitle("Courier Company");
    service.addObserver(this);

    tableView = new QTableView(this);
    model = new QStandardItemModel(this);

    model->setHorizontalHeaderLabels({ "Recipient", "Street", "Number", "X", "Y", "Delivered" });
    tableView->setModel(model);
    tableView->horizontalHeader()->setStretchLastSection(true);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Inline input widgets:
    recipientEdit = new QLineEdit(this);
    recipientEdit->setPlaceholderText("Recipient");

    streetEdit = new QLineEdit(this);
    streetEdit->setPlaceholderText("Street");

    numberEdit = new QLineEdit(this);
    numberEdit->setPlaceholderText("Number");

    xEdit = new QLineEdit(this);
    xEdit->setPlaceholderText("X coordinate");

    yEdit = new QLineEdit(this);
    yEdit->setPlaceholderText("Y coordinate");

    addPackageButton = new QPushButton("Add Package", this);

    // Layout for inputs and button:
    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(recipientEdit);
    inputLayout->addWidget(streetEdit);
    inputLayout->addWidget(numberEdit);
    inputLayout->addWidget(xEdit);
    inputLayout->addWidget(yEdit);
    inputLayout->addWidget(addPackageButton);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(inputLayout);

    setLayout(mainLayout);

    connect(addPackageButton, &QPushButton::clicked, this, &CourierCompanyWindow::onAddPackage);

    update();
}

void CourierCompanyWindow::populateTable() {
    model->removeRows(0, model->rowCount());

    const auto& packages = service.getPackages();
    for (const auto& p : packages) {
        QList<QStandardItem*> rowItems;
        rowItems << new QStandardItem(QString::fromStdString(p.getRecipient()));
        rowItems << new QStandardItem(QString::fromStdString(p.getStreet()));
        rowItems << new QStandardItem(QString::number(p.getNumber()));
        rowItems << new QStandardItem(QString::number(p.getX()));
        rowItems << new QStandardItem(QString::number(p.getY()));
        rowItems << new QStandardItem(p.isDelivered() ? "Yes" : "No");

        model->appendRow(rowItems);

        if (p.isDelivered()) {
            for (auto& item : rowItems) {
                item->setBackground(QBrush(Qt::green));
            }
        }
    }
}

bool CourierCompanyWindow::validateInputs() {
    bool ok;
    int num = numberEdit->text().toInt(&ok);
    if (!ok || num < 1) {
        QMessageBox::warning(this, "Invalid input", "Number must be a positive integer.");
        return false;
    }

    double x = xEdit->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid input", "X coordinate must be a number.");
        return false;
    }

    double y = yEdit->text().toDouble(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Invalid input", "Y coordinate must be a number.");
        return false;
    }

    if (recipientEdit->text().isEmpty() || streetEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Invalid input", "Recipient and Street cannot be empty.");
        return false;
    }
    return true;
}

void CourierCompanyWindow::onAddPackage() {
    if (!validateInputs())
        return;

    std::string recipient = recipientEdit->text().toStdString();
    std::string street = streetEdit->text().toStdString();
    int number = numberEdit->text().toInt();
    double x = xEdit->text().toDouble();
    double y = yEdit->text().toDouble();

    Package newPackage(recipient, street, number, x, y, false);
    service.addPackage(newPackage);

    // Clear inputs
    recipientEdit->clear();
    streetEdit->clear();
    numberEdit->clear();
    xEdit->clear();
    yEdit->clear();
}

void CourierCompanyWindow::update() {
    populateTable();
}
