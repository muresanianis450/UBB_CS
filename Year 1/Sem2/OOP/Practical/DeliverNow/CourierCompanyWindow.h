#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStandardItemModel>
#include "Service.h"

class CourierCompanyWindow : public QWidget , public Observer{
    Q_OBJECT
private:
    Service& service;
    QTableView* tableView;
    QStandardItemModel* model;

    QLineEdit* recipientEdit;
    QLineEdit* streetEdit;
    QLineEdit* numberEdit;
    QLineEdit* xEdit;
    QLineEdit* yEdit;
    QPushButton* addPackageButton;

    void populateTable();
    bool validateInputs();

public:
    explicit CourierCompanyWindow(Service& service, QWidget* parent = nullptr);
    void update() override;
    private slots:
        void onAddPackage();

};
