#pragma once
#include "Package.h"
#include <vector>
#include <string>
class PackageRepository {
private:
    std::vector<Package> packages;

public:
    PackageRepository(const std::string& filename);
    const std::vector<Package>& getPackages() const;
    void addPackage(const Package& p);
    void saveToFile(const std::string& filename) const;

    std::vector<Package>& getAllMutable();
};