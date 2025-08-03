#pragma once
#include "Idea.h"
#include <vector>

class IdeaRepository {
    std::vector<Idea> ideas;
public:
    IdeaRepository(const std::string fileName);

    void saveToFile(const std::string& filename);

    const std::vector<Idea>& getAll() const;
    void addIdea(const Idea& idea); // validate for duplicates
    void updateStatus(const std::string& description, int act, const std::string& status);
};
