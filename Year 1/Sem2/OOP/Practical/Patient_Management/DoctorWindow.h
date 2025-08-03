#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include "Observable.h"
#include "HospitalService.h"
#include <QPushButton>
#include <QLabel>
class DoctorWindow : public QWidget, public Observer {
  Q_OBJECT

private:
  HospitalService& service;
  QListWidget* doctorList;
  QLineEdit* diagnosisEdit;
  QLineEdit* specializationEdit;
  QLineEdit* nameEdit;
  QPushButton* updateButton;
  std::string doctorName;


  QLineEdit* newDiagnosisEdit;
  QLineEdit* newSpecializationEdit;
  QLineEdit* admissionDateEdit;
  QPushButton* addPatientButton;


public:
  explicit DoctorWindow(HospitalService& service,const std::string& doctorName, QWidget* parent = nullptr);
  void update() override;

  private slots:
      void handleUpdate();
      void handleAddPatient();
};