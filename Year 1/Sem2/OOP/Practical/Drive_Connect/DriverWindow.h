#pragma once
#include <QWidget>
#include "Observer.h"
#include "ReportService.h"

#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushBUtton>
#include <QPushBUtton>
#include  <QLineEdit>



class DriverWindow : public QWidget , public Observer {
    Q_OBJECT

private:
    ReportService& service;
    const Driver& driver;

    QLabel* infoLabel;
    QListWidget* reportList;
    QLineEdit* descriptionInput;
    QLineEdit* latInput;
    QLineEdit* lonInput;
    QPushButton* addButton;
    QTextEdit* chatBox;
    QLineEdit* chatInput;
    QPushButton* sendButton;





public:
    DriverWindow(ReportService& service, const Driver& driver, QWidget* parent = nullptr);
    void update() override;
private slots:
    void handleAddReport();
    void handleSendMessage();
    void handleValidateReport(QListWidgetItem* item);


};