#pragma once
#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Service.h"

class AdminWindow : public QMainWindow , public Observer{
    Q_OBJECT
private:
    Service& service;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;
    QListWidget* itemListWidget;

    QLineEdit* nameEdit;
    QLineEdit* categoryEdit;
    QLineEdit* priceEdit;
    QPushButton* addItemButton;
    QPushButton* manageUsersButton;

    void populateItemList();

    private slots:
        void handleAddItem();
    void handleManageUsers(); // placeholder slot

public:
    explicit AdminWindow(Service& service, QWidget* parent = nullptr);
    void update() override;
};
