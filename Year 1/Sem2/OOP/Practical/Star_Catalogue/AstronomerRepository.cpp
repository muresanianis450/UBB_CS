

#include "AstronomerRepository.h"
#include <fstream>
#include <sstream>

AstronomerRepository::AstronomerRepository(const std::string &fileName= "astronomers.txt") {
std::ifstream fin(fileName);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream iff(line);
        std::string name, constelation;
        getline(iff, name, ',');
        getline(iff, constelation, ',');
        astronomers.emplace_back(name, constelation);
    }
}

const std::vector<Astronomer> &AstronomerRepository::getAll() const {
    return astronomers;
}



