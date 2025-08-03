#pragma once
#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QPushButton>
#include "Service.h"
#include "Observable.h"

class PresenterWindow: public QWidget, public Observer {
    Q_OBJECT

private:
    Service& service;
    QTableWidget* table;
    QLineEdit *idEdit, *textEdit,*answerEdit,*scoreEdit;
    QPushButton* addButton;
private slots:
    void handleAddButton();
public:
    PresenterWindow(Service& service);
    void update() override;
};