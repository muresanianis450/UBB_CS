#include "Service.h"
#include <algorithm>
#include <stdexcept>

Service::Service(StarRepository &starRepo, AstronomerRepository &astronomerRepo)
    :starRepo(starRepo),astronomerRepo(astronomerRepo){
}

const std::vector<Star>& Service::getAllStars() const {
    return starRepo.getAll();
}

const std::vector<Astronomer>& Service::getAllAstronomers() const {
    return astronomerRepo.getAll();
}


std::vector<Star> Service::getStarsByConstellation(const std::string& constelation) const {
    std::vector<Star> result;
    for (const auto& star : starRepo.getAll()) {
        if (star.getConstelation() == constelation)
            result.push_back(star);
    }
    return result;
}

void Service::addStar(const std::string& name, const std::string& constelation, int ra, int dec, double diameter) {
    if (name.empty())
        throw std::invalid_argument("name cannot be empty");
    if (diameter <= 0)
        throw std::invalid_argument("diameter must be positive");

    for (const auto& s : starRepo.getAll()) {
        if (s.getName() == name)
            throw std::invalid_argument("star with this name already exists");
    }
    Star star(name, constelation, ra, dec, diameter);
    starRepo.addStar(star);
    notify();
    saveStarsToFile();

}

void Service::saveStarsToFile() const {
    starRepo.saveToFile();
}
std::vector<Star> Service::searchStarsByName(const std::string &substring) const {
    std::vector<Star> result;
    for (const auto& star: starRepo.getAll()) {
        if (star.getName().find(substring) != std::string::npos)
            result.push_back(star);
    }
    return result;
}

