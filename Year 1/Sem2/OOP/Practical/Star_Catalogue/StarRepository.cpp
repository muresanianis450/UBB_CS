

#include "StarRepository.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <sstream>

StarRepository::StarRepository(const std::string &fileName): fileName(fileName) {
    std::ifstream fin(fileName);
    std::string line;
    while (getline(fin,line)) {
        std::istringstream iss(line);
        std::string name, constellation;
        int ra, dec;
        double diameter;
        getline(iss, name, ',');
        getline(iss,constellation,',');
        iss >> ra >> dec >> diameter;

        stars.emplace_back(name, constellation, ra, dec, diameter);
    }
}
const std::vector<Star>& StarRepository::getAll() const {
    return stars;
}
void StarRepository::addStar(const Star& star) {
    stars.push_back(star);
}
void StarRepository::saveToFile()const {
    std::vector<Star> sortedStars = stars;
    std::sort(sortedStars.begin(),sortedStars.end(),
    [](const Star& a, const Star& b) {
        return a.getConstelation() < b.getConstelation();
    });

    std::ofstream fout(fileName);
    for (const auto& s: sortedStars)
        fout << s.getName() << "," << s.getConstelation() << ","
            << s.getRA() << " " << s.getDec() << " " << s.getDiameter() << "\n";
}

