#include "IdeaRepository.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

IdeaRepository::IdeaRepository(const std::string fileName= "ideas.txt") {
    ideas.clear();
    std::ifstream fin(fileName);

    std::string line;
    while (std::getline(fin, line)) {
        std::istringstream iss(line);
        std::string description, status, creator;
        int act;

        std::getline(iss, description, ',');
        std::getline(iss, status, ',');
        std::getline(iss, creator, ',');
        iss >> act;

        if (!description.empty() && !status.empty() && !creator.empty() && act >= 1 && act <= 3) {
            ideas.emplace_back(description, creator, act, status);
        }
    }
    fin.close();
}


void IdeaRepository::saveToFile(const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout.is_open())
        throw std::runtime_error("Cannot write to file: " + filename);

    for (const auto& idea : ideas) {
        fout << idea.getDescription() << ","
             << idea.getStatus() << ","
             << idea.getCreator() << ","
             << idea.getAct() << "\n";
    }

    fout.close();
}

const std::vector<Idea>& IdeaRepository::getAll() const {
    return ideas;
}

void IdeaRepository::addIdea(const Idea& idea) {
    for (const auto& existing : ideas) {
        if (existing.getDescription() == idea.getDescription() && existing.getAct() == idea.getAct()) {
            throw std::runtime_error("Duplicate idea with same description and act already exists.");
        }
    }
    ideas.push_back(idea);
}

void IdeaRepository::updateStatus(const std::string& description, int act, const std::string& status) {
    for (auto& idea : ideas) {
        if (idea.getDescription() == description && idea.getAct() == act) {
            idea.setStatus(status);
            return;
        }
    }
    throw std::runtime_error("Idea not found to update status.");
}
