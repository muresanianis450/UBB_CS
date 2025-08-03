#pragma once
#include "Astronomer.h"
#include <vector>
#include <string>

class AstronomerRepository {
private:
    std::vector<Astronomer> astronomers;

public:
    AstronomerRepository(const std::string& fileName);
    const std::vector<Astronomer>& getAll() const;

};