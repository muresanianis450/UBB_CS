#pragma once

#include <QMainWindow>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "Service.h"

class CollectorWindow : public QMainWindow , public Observer{
    Q_OBJECT
private:
    Service& service;
    int userId;

    QWidget* centralWidget;
    QVBoxLayout* mainLayout;

    QComboBox* categoryComboBox;
    QListWidget* itemListWidget;

    QLineEdit* bidAmountEdit;
    QLineEdit* bidDateEdit;
    QPushButton* placeBidButton;

    void populateCategories();
    void populateItemList(const std::string& category = "");

    private slots:
        void handleCategoryChanged(int index);
    void handlePlaceBid();

public:
    explicit CollectorWindow(Service& service,int userId, QWidget* parent = nullptr);
    void update() override;
};
