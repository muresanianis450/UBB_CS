#include "Package.h"
#include "PackageRepository.h"
#include <fstream>

PackageRepository::PackageRepository(const std::string &filename="packages.txt") {
    std::ifstream fin(filename);

    Package p;
    while (fin >> p) {
        packages.push_back(p);
    }
}

const std::vector<Package>& PackageRepository::getPackages() const {
    return packages; // returns read-only packages
}
std::vector<Package>& PackageRepository::getAllMutable() {
    return packages; // returns direct refference to them,allows me to modify their status in gui

}
void PackageRepository::addPackage(const Package& p) {
    packages.push_back(p);
}
void PackageRepository::saveToFile(const std::string &filename) const {
    std::ofstream fout(filename);
    for (const auto& p : packages) {
        fout << p;
    }
}




