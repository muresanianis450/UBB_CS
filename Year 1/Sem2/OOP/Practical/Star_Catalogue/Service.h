#pragma once
#include "StarRepository.h"
#include "AstronomerRepository.h"
#include "Observable.h"
class Service : public Observable{
private:
    StarRepository starRepo;
    AstronomerRepository astronomerRepo;
public:
    Service(StarRepository& starRepo, AstronomerRepository& astronomerRepo);

    const std::vector<Star>& getAllStars() const;
    const std::vector<Astronomer>& getAllAstronomers() const;

    std::vector<Star> getStarsByConstellation(const std::string& constellation ) const;

    void addStar(const std::string& name, const std::string& constelation, int RA, int Dec, double diameter);

    void saveStarsToFile() const;
    std::vector<Star> searchStarsByName(const std::string& substring) const ;

};

