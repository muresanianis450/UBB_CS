#pragma once
#include <vector>
#include <string>
#include "PackageRepository.h"
#include "CourierRepository.h"
#include "Observable.h"
class Service : public Observable{
private:
    PackageRepository& packageRepo;
    CourierRepository& courierRepo;

public:
    Service(PackageRepository& packageRepo, CourierRepository& courierRepo);
    const std::vector<Package>& getPackages() const;
    const std::vector<Courier>& getCouriers() const;

    std::vector<Package> getPackagesForCourier(const Courier& c) const;

    void deliverPackage(const std::string& recipient);
    void addPackage(const Package& p);

};