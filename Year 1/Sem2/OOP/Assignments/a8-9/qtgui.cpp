//
// Created by mures on 5/22/2025.
//

// You may need to build the project (run Qt uic code generator) to get "ui_QTGUI.h" resolved

#include "qtgui.h"
#include "ui_QTGUI.h"


QTGUI::QTGUI(QWidget *parent) :
    QWidget(parent), ui(new Ui::QTGUI) {
    ui->setupUi(this);
    connect_push_buttons();
}

QTGUI::~QTGUI() {
    delete ui;
}

void QTGUI::connect_push_buttons() {
    QObject::connect(ui->pushButton1, &QPushButton::clicked, this, &QTGUI::function);
}

void QTGUI::function() {
    ui->buttonLineEdit->setText("HELP");
}


