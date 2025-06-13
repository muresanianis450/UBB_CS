//
// Created by mures on 5/11/2025.
//
#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "../adoption/AdoptionListFactory.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include "service/service.h"
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Service& service ,QWidget *parent = nullptr);
    private slots:
        void goToModePage() const;
    void goToAdminPage() const;

private:
    Service& service;
    QStackedWidget *stackedWidget;
    std::string whereToSaveFile;
    std::unique_ptr<AdoptionList> adoptionList;

    QWidget  *createStartPage();
    QWidget *createModePage();
    QWidget *createUserPage(); // TODO userPage
    QWidget *createAdminPage();

    void goToUserPage() const;
};



#endif //MAINWINDOW_H
