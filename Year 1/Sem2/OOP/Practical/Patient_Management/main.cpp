#include <QApplication>
#include "DoctorWindow.h"
#include "HospitalService.h"
#include "PatientRepository.h"
#include "DoctorRepository.h"
#include "StatisticsWidget.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    DoctorRepository doctorRepo("doctors.txt");
    PatientRepository patientRepo("patients.txt");
    HospitalService service(doctorRepo,patientRepo);

    // Create a window for each doctor
    for (const auto& doc : service.getAllDoctors()) {
        auto* window = new DoctorWindow(service, doc.getName());
        window->show();
    }
    StatisticsWidget* statsWindow = new StatisticsWidget(service);
    statsWindow->setWindowTitle("Patient  Statistics");
    statsWindow->resize(600, 400);
    statsWindow->show();

    return a.exec();
}