
#include "Package.h"
#include "CourierWindow.h"
#include <QMessageBox>

CourierWindow::CourierWindow(Service& service, const Courier& courier, QWidget* parent)
    : QWidget(parent), service(service), courier(courier) {
    setWindowTitle(QString::fromStdString(courier.getName()));

    service.addObserver(this);
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* zoneLabel = new QLabel(
    QString("Zone: center(%1, %2), radius %3")
        .arg(QString::number(courier.getZoneX()))
        .arg(QString::number(courier.getZoneY()))
        .arg(QString::number(courier.getRadius())));

    streetComboBox = new QComboBox(this);
    packageListWidget = new QListWidget(this);
    deliverButton = new QPushButton("Deliver", this);

    layout->addWidget(zoneLabel);
    layout->addWidget(streetComboBox);
    layout->addWidget(packageListWidget);
    layout->addWidget(deliverButton);

    populateStreets();
    loadPackages();

    connect(streetComboBox, &QComboBox::currentTextChanged, this, &CourierWindow::filterPackagesByStreet);
    connect(deliverButton, &QPushButton::clicked, this, &CourierWindow::deliverSelectedPackage);

}

void CourierWindow::populateStreets() {
    streetComboBox->addItem("All Streets");  // Default no filter
    for (const auto& street : courier.getStreets()) {
        streetComboBox->addItem(QString::fromStdString(street));
    }
}

void CourierWindow::loadPackages(const QString& filterStreet) {
    packageListWidget->clear();

    std::vector<Package> packages = service.getPackagesForCourier(courier);

    for (const auto& p : packages) {
        if (p.isDelivered())
            continue;

        if (!filterStreet.isEmpty() && filterStreet != "All Streets" &&
            QString::fromStdString(p.getStreet()) != filterStreet) {
            continue;
            }

        QListWidgetItem* item = new QListWidgetItem(packageToString(p));
        QString key = QString::fromStdString(p.getRecipient()) + "|" +
                      QString::fromStdString(p.getStreet()) + "|" +
                      QString::number(p.getNumber());
        item->setData(Qt::UserRole, key);
        packageListWidget->addItem(item);
    }
}
QString CourierWindow::packageToString(const Package& p) {
    return QString("Recipient: %1, %2 %3, Location: (%4, %5)")
        .arg(QString::fromStdString(p.getRecipient()))
        .arg(QString::fromStdString(p.getStreet()))
        .arg(QString::number(p.getNumber()))
        .arg(QString::number(p.getX()))
        .arg(QString::number(p.getY()));
}


void CourierWindow::filterPackagesByStreet(const QString& filterStreet) {
    loadPackages(filterStreet);
}

void CourierWindow::deliverSelectedPackage() {
    QListWidgetItem* currentItem = packageListWidget->currentItem();
    if (!currentItem) {
        QMessageBox::warning(this, "No selection", "Please select a package to deliver.");
        return;
    }

    // Just get the recipient from the stored data (which you set as recipient|street|number)
    // But only use recipient because service expects that
    QString key = currentItem->data(Qt::UserRole).toString();
    QStringList parts = key.split("|");
    if (parts.size() < 1) {
        QMessageBox::warning(this, "Error", "Invalid package identifier.");
        return;
    }

    std::string recipient = parts[0].toStdString();

    try {
        service.deliverPackage(recipient);  // only recipient param!
        QMessageBox::information(this, "Success", "Package delivered successfully.");
    } catch (const std::exception& ex) {
        QMessageBox::critical(this, "Error", QString::fromStdString(ex.what()));
    }
}
void CourierWindow::update() {
    filterPackagesByStreet(streetComboBox->currentText());
}