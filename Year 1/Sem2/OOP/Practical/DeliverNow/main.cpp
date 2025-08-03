#include <QApplication>
#include <QMessageBox>
#include <vector>
#include <memory>

#include "Service.h"
#include "PackageRepository.h"
#include "CourierRepository.h"
#include "CourierWindow.h"
#include "CourierCompanyWindow.h"
#include "MapWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    try {
        PackageRepository packageRepo("packages.txt");
        CourierRepository courierRepo("couriers.txt");
        Service service(packageRepo, courierRepo);

        auto couriers = service.getCouriers();

        if (couriers.empty()) {
            QMessageBox::warning(nullptr, "Warning",
                "No couriers found. Please check couriers.txt.");
        }

        //courier windows
        std::vector<std::unique_ptr<CourierWindow>> courierWindows;
        for (const auto& courier : couriers) {
            auto cw = std::make_unique<CourierWindow>(service, courier);
            cw->resize(600, 400);
            cw->move(50 + courierWindows.size() * 50, 50 + courierWindows.size() * 50);
            cw->show();
            courierWindows.push_back(std::move(cw));
        }

        //company window
        auto companyWindow = std::make_unique<CourierCompanyWindow>(service);
        companyWindow->resize(800, 600);
        companyWindow->setWindowTitle("Courier Company");
        companyWindow->show();

        //map
        auto mapWindow = std::make_unique<MapWindow>(service);
        mapWindow->resize(600, 400);
        mapWindow->setWindowTitle("Package Map");
        mapWindow->show();

        return app.exec();

    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Error",
            QString("Failed to start application: %1").arg(e.what()));
        return -1;
    }
}
