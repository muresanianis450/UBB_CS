#pragma once

#include <QWidget>
#include <QListWidget>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "Service.h"

class CourierWindow: public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;
    Courier courier;

    QListWidget* packageListWidget;
    QComboBox* streetComboBox;
    QPushButton* deliverButton;

public:
    CourierWindow(Service& service, const Courier& courier, QWidget* parent = nullptr);

    void update() override;

private slots:
    void filterPackagesByStreet(const QString& street);
    void deliverSelectedPackage();

private:
    void populateStreets();
    void loadPackages(const QString& filterStreet = "");
    QString packageToString(const Package& p);

};