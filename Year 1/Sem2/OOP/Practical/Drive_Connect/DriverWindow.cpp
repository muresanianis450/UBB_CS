
#include "DriverWindow.h"
#include <QVBoxLayout>
DriverWindow::DriverWindow(ReportService& service, const Driver& driver, QWidget* parent)
    : QWidget(parent), service(service), driver(driver) {
    setWindowTitle(QString::fromStdString(driver.getName()));
    service.addObserver(this);

    auto* layout = new QVBoxLayout(this);

    infoLabel = new QLabel(this);
    layout->addWidget(infoLabel);

    reportList = new QListWidget(this);
    layout-> addWidget(reportList);

    auto* formLayout = new QHBoxLayout;
    descriptionInput = new QLineEdit(this);
    descriptionInput->setPlaceholderText("Description");
    latInput = new QLineEdit(this);
    latInput->setPlaceholderText("Latitude");

    lonInput=new QLineEdit(this);
    lonInput->setPlaceholderText("Longitude");

    addButton = new QPushButton("Add Repotr", this);
    formLayout->addWidget(descriptionInput);
    formLayout->addWidget(latInput);
    formLayout->addWidget(lonInput);
    formLayout->addWidget(addButton);
    layout->addLayout(formLayout);

    //chat box
    chatBox = new QTextEdit(this);
    chatInput = new QLineEdit(this);
    chatInput->setPlaceholderText("Send message...");
    sendButton = new QPushButton("Send",this);

    layout->addWidget(chatBox);
    layout->addWidget(chatInput);
    layout->addWidget(sendButton);

    connect(addButton, &QPushButton::clicked,this,&DriverWindow::handleAddReport);
    connect(sendButton,&QPushButton::clicked,this,&DriverWindow::handleSendMessage);
    connect(reportList,&QListWidget::itemDoubleClicked,this,&DriverWindow::handleValidateReport);

    update();
}


void DriverWindow::update() {
    qDebug()<<"update";
infoLabel->setText(QString::fromStdString(
        "Location: ("+ std::to_string(driver.getLatitude())+", "+
        std::to_string(driver.getLongitude())+") | Scoer: "+ std::to_string(driver.getScore())));
  reportList->clear();

    for (const auto& report : service.getReports()) {
        if (driver.distanceTo(report.getLatitude(),report.getLongitude()) <= 10.0) {
            QString text = QString::fromStdString(report.toString());
            auto* item = new QListWidgetItem(text);

            if (report.getIsValid()) {
                QFont font;
                font.setBold(true);
                item->setFont(font);
            }
            reportList->addItem(item);
        }
    }
    chatBox->clear();
    for (const auto& msg: service.getChatMessages()) {
        chatBox->append(QString::fromStdString(msg));
    }
}
void DriverWindow::handleAddReport() {
    std::string description = descriptionInput->text().toStdString();
    double lat = latInput->text().toDouble();
    double lon = lonInput->text().toDouble();

    service.addReport(description,driver.getName(),lat,lon);

    descriptionInput->clear();
    latInput->clear();
    lonInput->clear();

   //    update();
}

void DriverWindow::handleSendMessage() {
    std::string message = chatInput->text().toStdString();
    if (message.empty()) return;

    std::string formatted= driver.getName()+ ": "+message;
    service.sendMessage(formatted);
    chatInput->clear();
}

void DriverWindow::handleValidateReport(QListWidgetItem* item) {
    if (!item) return;
    QString itemText = item->text();

    // Example of parsing description from item text
    QString prefix = "Description: ";
    int start = itemText.indexOf(prefix);
    if (start == -1) return;

    start += prefix.length();
    int end = itemText.indexOf(',', start);
    if (end == -1) return;

    QString description = itemText.mid(start, end - start);
    std::string reportDescription = description.toStdString();

    service.validateReport(reportDescription, driver.getName());
    update();
}