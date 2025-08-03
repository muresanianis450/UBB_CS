#pragma once
#include "Writer.h"
#include <vector>

class WriterRepository {
    std::vector<Writer> writers;
public:
    WriterRepository(const std::string fileName);
    const std::vector<Writer>& getAll() const;
};
