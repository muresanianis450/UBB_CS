#pragma once
#include "Star.h"
#include <vector>
#include <string>

class StarRepository {
private:
    std::vector<Star> stars;
    std::string fileName;
public:
    StarRepository(const std::string& fileName);
    const std::vector<Star>& getAll() const;
    void addStar(const Star& star);
    void saveToFile() const;
};