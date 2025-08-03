

#include "CourierRepository.h"
#include <fstream>
#include <sstream>

CourierRepository::CourierRepository(const std::string &filename = "couriers.txt") {
    std::ifstream fin(filename);

    std::string line;

    while (std::getline(fin,line)) {

        std::string name = line;

        std::getline(fin,line);
        std::vector<std::string> streets;
        std::stringstream ss(line);
        std::string street;
        while (std::getline(ss,street,',')) {
            streets.push_back(street);
        }

        double x,y,radius;
        fin >> x >> y >> radius;
        fin.ignore(); // ignore newline after radius

        couriers.emplace_back(name,streets,x,y,radius);
    }
}

const std::vector<Courier>& CourierRepository::getCouriers() const {
    return couriers;
}

