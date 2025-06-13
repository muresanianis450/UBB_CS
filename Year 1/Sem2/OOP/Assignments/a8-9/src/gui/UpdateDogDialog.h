//
// Created by mures on 5/11/2025.
//

#ifndef UPDATEDOGDIALOG_H
#define UPDATEDOGDIALOG_H
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "service/service.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include "MainWindow.h"
#include <QMessageBox>
#include <QDialog>


class UpdateDogDialog :public QDialog {
  Q_OBJECT

    public:
      UpdateDogDialog(Service& service, QWidget *parent = nullptr);

      private slots:
        void handleUpdate();

private:
    Service& service;
    QLineEdit *oldBreedInput;
    QLineEdit *oldNameInput;
    QLineEdit *oldAgeInput;
    QLineEdit *oldLinkInput;
    QLineEdit *newBreedInput;
    QLineEdit *newNameInput;
    QLineEdit *newAgeInput;
    QLineEdit *newLinkInput;

};



#endif //UPDATEDOGDIALOG_H
