#include "Service.h"
#include <algorithm>
#include <math.h>
#include <valarray>

Service::Service(PackageRepository &packageRepo, CourierRepository &courierRepo)
    :packageRepo(packageRepo), courierRepo(courierRepo){}

const std::vector<Package> &Service::getPackages() const {
    return packageRepo.getPackages();
}
const std::vector<Courier> &Service::getCouriers() const {
    return courierRepo.getCouriers();

}

std::vector<Package> Service::getPackagesForCourier(const Courier &c) const {
    std::vector<Package> result;
    for (const auto& p : packageRepo.getPackages()) {
        if (p.isDelivered()) continue;

        bool inStreetList = std::find(c.getStreets().begin(), c.getStreets().end(),
            p.getStreet()) != c.getStreets().end();

        double dx = c.getZoneX() - p.getX();
        double dy = c.getZoneY() - p.getY();
        double distance = sqrt(dx * dx + dy * dy);

        if (distance <= c.getRadius() || inStreetList) {
            result.push_back(p);
        }

    }
    return result;
}
void Service::deliverPackage(const std::string& recipient) {
    auto& packages = packageRepo.getAllMutable();
    for (auto& p : packages) {
        if (p.getRecipient() == recipient) {
            p.setDelivered(true);
            break;
        }
    }
    notifyObservers();
}
void Service::addPackage(const Package& p) {
    packageRepo.addPackage(p);
    notifyObservers();

}



