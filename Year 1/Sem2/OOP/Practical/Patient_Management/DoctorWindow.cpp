#include "DoctorWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>

DoctorWindow::DoctorWindow(HospitalService& service, const std::string& doctorName, QWidget* parent)
    : QWidget(parent), service(service), doctorName(doctorName) {

  service.addObserver(this);
  this->setWindowTitle(QString::fromStdString(doctorName));

  this->setMinimumSize(500, 400);
  QVBoxLayout* mainLayout = new QVBoxLayout(this);

  QLabel* listLabel = new QLabel("Patients:");
  doctorList = new QListWidget(this);
  mainLayout->addWidget(listLabel);
  mainLayout->addWidget(doctorList);

  QLabel* diagnosisLabel = new QLabel("New Diagnosis:");
  diagnosisEdit = new QLineEdit(this);
  mainLayout->addWidget(diagnosisLabel);
  mainLayout->addWidget(diagnosisEdit);

  QLabel* specLabel = new QLabel("New Specialization:");
  specializationEdit = new QLineEdit(this);
  mainLayout->addWidget(specLabel);
  mainLayout->addWidget(specializationEdit);

  updateButton = new QPushButton("Update", this);
  mainLayout->addWidget(updateButton);

  QLabel* nameLabel = new QLabel("New Patient Name:");
  nameEdit = new QLineEdit(this);
  mainLayout->addWidget(nameLabel);
  mainLayout->addWidget(nameEdit);

  QLabel* newDiagnosisLabel = new QLabel("Diagnosis:");
  newDiagnosisEdit = new QLineEdit(this);
  mainLayout->addWidget(newDiagnosisLabel);
  mainLayout->addWidget(newDiagnosisEdit);

  QLabel* newSpecLabel = new QLabel("Specialization Needed:");
  newSpecializationEdit = new QLineEdit(this);
  mainLayout->addWidget(newSpecLabel);
  mainLayout->addWidget(newSpecializationEdit);

  QLabel* admissionDateLabel = new QLabel("Admission Date (YYYY-MM-DD):");
  admissionDateEdit = new QLineEdit(this);
  mainLayout->addWidget(admissionDateLabel);
  mainLayout->addWidget(admissionDateEdit);

  addPatientButton = new QPushButton("Add Patient", this);
  mainLayout->addWidget(addPatientButton);

  connect(addPatientButton, &QPushButton::clicked, this, &DoctorWindow::handleAddPatient);
  connect(updateButton, &QPushButton::clicked, this, &DoctorWindow::handleUpdate);

  update();
}

void DoctorWindow::update(){
  doctorList->clear();

  std::string doctorName = this->windowTitle().toStdString();
  std::string specialization = "";

  for(const auto& doc: service.getAllDoctors()){
    if(doc.getName() == doctorName){
      specialization = doc.getSpecialization();
      break;
    }
  }

  auto patients = service.getPatientsForDoctor(doctorName,specialization,false);
  for(const auto& p : patients){
    QString item = QString::fromStdString(
          p.getName() + " | " + p.getDiagnosis() + " | " +
          p.getCurrentDoctor() + " | " + p.getNeededSpecialization() + " | " +
          p.getAdmissionDate());
    doctorList->addItem(item);}
}

void DoctorWindow::handleUpdate(){
  auto selected = doctorList->currentItem();
  if(!selected) {
    QMessageBox::warning(this, "Warning", "no patient selected");
    return;}

  std::string diagnosis = diagnosisEdit->text().toStdString();
  std::string specialization = specializationEdit->text().toStdString();

  if(diagnosis.empty() || specialization.empty()){
    QMessageBox::warning(this, "Warning", "diagnosis and specialization cannot be empty");

  }
  QString fullText = selected->text();
  QString name = fullText.section("|",0,0).trimmed(); //patient name is first

  try{
    service.updateDiagnosisAndSpecialization(
           name.toStdString(),
           diagnosis,
           specialization,
           this->windowTitle().toStdString()
    );
    diagnosisEdit->clear();
    specializationEdit->clear();

    }catch(std::exception& e){
      QMessageBox::critical(this, "error", e.what());
    }
}
void DoctorWindow::handleAddPatient() {
  std::string name = nameEdit->text().toStdString();
  std::string diagnosis = newDiagnosisEdit->text().toStdString();
  std::string currentDoctor = this->windowTitle().toStdString();

  std::string neededSpecialization = newSpecializationEdit->text().toStdString();
  // find doctor with needed specialization
  for (const auto& doc : service.getAllDoctors()) {
    if (doc.getSpecialization() == neededSpecialization) {
      currentDoctor = doc.getName();
      break;
    }
  }


  std::string admissionDate = admissionDateEdit->text().toStdString();

  // Validate patient name
  if (name.empty()) {
    QMessageBox::warning(this, "Warning", "Patient name cannot be empty");
    return;
  }

  // Validate admission date format (basic check)
  if (admissionDate.size() != 10 || admissionDate[4] != '-' || admissionDate[7] != '-') {
    QMessageBox::warning(this, "Warning", "Admission date must be in YYYY-MM-DD format");
    return;
  }

  // Note: You can choose to validate if admissionDate is >= "2025-01-01" or similar,
  // but your service already checks for past dates and throws exceptions.

  try {
    // Add patient via service
    service.addPatient(name, diagnosis, currentDoctor, neededSpecialization, admissionDate);

    // Clear input fields
    nameEdit->clear();
    newDiagnosisEdit->clear();
    newSpecializationEdit->clear();
    admissionDateEdit->clear();

    // Refresh the patient list view to show the new patient
    update();
  }
  catch (std::exception& e) {
    QMessageBox::critical(this, "Error", e.what());
  }
}

