#include <QApplication>
#include "ReportRepository.h"
#include "DriverRepo.h"
#include "ReportService.h"
#include "DriverWindow.h"
#include "MapWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);


    DriverRepo driverRepo;
    ReportRepository reportRepo;
    ReportService service(reportRepo, driverRepo);


    MapWindow* mapWindow = new MapWindow(service);
    mapWindow->show();

    for (const auto& driver : driverRepo.getAll()) {
        DriverWindow* win = new DriverWindow(service, driver);
        win->show();
    }

    return app.exec();
}
