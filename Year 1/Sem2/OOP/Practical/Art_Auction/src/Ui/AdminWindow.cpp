#include "AdminWindow.h"
#include <QIntValidator>
#include <QMessageBox>

AdminWindow::AdminWindow(Service& service, QWidget* parent)
    : QMainWindow(parent), service(service) {
    service.addObserver(this);
    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    itemListWidget = new QListWidget(centralWidget);
    mainLayout->addWidget(itemListWidget);

    QHBoxLayout* inputLayout = new QHBoxLayout();

    nameEdit = new QLineEdit(centralWidget);
    nameEdit->setPlaceholderText("Name");

    categoryEdit = new QLineEdit(centralWidget);
    categoryEdit->setPlaceholderText("Category");

    priceEdit = new QLineEdit(centralWidget);
    priceEdit->setPlaceholderText("Price");
    priceEdit->setValidator(new QIntValidator(0, 1000000, this));

    addItemButton = new QPushButton("Add Item", centralWidget);


    inputLayout->addWidget(nameEdit);
    inputLayout->addWidget(categoryEdit);
    inputLayout->addWidget(priceEdit);
    inputLayout->addWidget(addItemButton);


    mainLayout->addLayout(inputLayout);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Admin Panel - Art Auction Platform");

    populateItemList();

    connect(addItemButton, &QPushButton::clicked, this, &AdminWindow::handleAddItem);
}

void AdminWindow::populateItemList() {
    itemListWidget->clear();
    for (const auto& item : service.getSortedItems()) {
        QString text = QString::fromStdString(item.getName() + " | " +
                                              item.getCategory() + " | " +
                                              std::to_string(item.getCurrentPrice()));
        itemListWidget->addItem(text);
    }
}

void AdminWindow::handleAddItem() {
    QString name = nameEdit->text();
    QString category = categoryEdit->text();
    QString priceStr = priceEdit->text();

    if (name.isEmpty() || category.isEmpty() || priceStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill all fields.");
        return;
    }

    bool ok = false;
    int price = priceStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Price must be a valid number.");
        return;
    }

    try {
        if (service.addItem(name.toStdString(), category.toStdString(), price)) {
            populateItemList();
            nameEdit->clear();
            categoryEdit->clear();
            priceEdit->clear();
        }
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void AdminWindow::handleManageUsers() {
    // Placeholder: You can open a ManageUsersWindow or dialog here later
    QMessageBox::information(this, "Manage Users", "This feature is coming soon!");
}
void AdminWindow::update() {
    populateItemList();
}
