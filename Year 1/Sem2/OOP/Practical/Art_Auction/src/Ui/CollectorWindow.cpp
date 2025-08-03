#include "CollectorWindow.h"
#include <QMessageBox>
#include <QIntValidator>

CollectorWindow::CollectorWindow(Service& service,int userId, QWidget* parent)
    : QMainWindow(parent),userId(userId), service(service) {
    service.addObserver(this);

    centralWidget = new QWidget(this);
    mainLayout = new QVBoxLayout(centralWidget);

    categoryComboBox = new QComboBox(centralWidget);
    mainLayout->addWidget(categoryComboBox);

    itemListWidget = new QListWidget(centralWidget);
    mainLayout->addWidget(itemListWidget);

    QHBoxLayout* bidLayout = new QHBoxLayout();

    bidAmountEdit = new QLineEdit(centralWidget);
    bidAmountEdit->setPlaceholderText("Bid Amount");
    bidAmountEdit->setValidator(new QIntValidator(1, 1000000, this));

    bidDateEdit = new QLineEdit(centralWidget);
    bidDateEdit->setPlaceholderText("Date (YYYY-MM-DD)");

    placeBidButton = new QPushButton("Place Bid", centralWidget);

    bidLayout->addWidget(bidAmountEdit);
    bidLayout->addWidget(bidDateEdit);
    bidLayout->addWidget(placeBidButton);

    mainLayout->addLayout(bidLayout);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    setWindowTitle("Collector Panel - Art Auction Platform");

    populateCategories();
    populateItemList();

    connect(categoryComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &CollectorWindow::handleCategoryChanged);
    connect(placeBidButton, &QPushButton::clicked, this, &CollectorWindow::handlePlaceBid);
}

void CollectorWindow::populateCategories() {
    categoryComboBox->clear();
    categoryComboBox->addItem("All Categories");

    for (const auto& category : service.getCategories()) {
        categoryComboBox->addItem(QString::fromStdString(category));
    }
}

void CollectorWindow::populateItemList(const std::string& category) {
    itemListWidget->clear();

    std::vector<Item> items;
    if (category.empty() || category == "All Categories") {
        items = service.getSortedItems();
    } else {
        items = service.getItemsByCategory(category);
    }

    for (const auto& item : items) {
        QString text = QString::fromStdString(item.getName() + " | " +
                                       item.getCategory() + " | " +
                                       std::to_string(item.getCurrentPrice()));
        itemListWidget->addItem(text);
    }
}

void CollectorWindow::handleCategoryChanged(int index) {
    QString selectedCategory = categoryComboBox->currentText();
    if (selectedCategory == "All Categories")
        populateItemList();
    else
        populateItemList(selectedCategory.toStdString());
}

void CollectorWindow::handlePlaceBid() {
    QListWidgetItem* selectedItem = itemListWidget->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No Selection", "Please select an item to place a bid.");
        return;
    }

    QString bidAmountStr = bidAmountEdit->text();
    QString bidDateStr = bidDateEdit->text();

    if (bidAmountStr.isEmpty() || bidDateStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill bid amount and date.");
        return;
    }

    bool ok = false;
    int bidAmount = bidAmountStr.toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Input Error", "Bid amount must be a number.");
        return;
    }

    // Extract item name from the selected list item text (assumes "Name | Category | Price")
    QString selectedText = selectedItem->text();
    QString itemName = selectedText.split('|').at(0).trimmed();

    try {

        service.bid(userId, itemName.toStdString(), bidAmount, bidDateStr.toStdString());

        QMessageBox::information(this, "Bid Placed", "Your bid has been placed successfully.");
        populateItemList(categoryComboBox->currentText().toStdString());

        // Clear inputs
        bidAmountEdit->clear();
        bidDateEdit->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
    update();

}
void CollectorWindow::update() {
populateCategories();
    populateItemList();
}