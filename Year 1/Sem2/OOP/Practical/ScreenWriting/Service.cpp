#include "Service.h"
#include <stdexcept>

const std::vector<Writer>& Service::getAllWriters() const {
    return writerRepo.getAll();
}

const std::vector<Idea>& Service::getAllIdeas() const {
    return ideaRepo.getAll();
}

void Service::addIdea(const std::string& description, const std::string& creator, int act) {
    if (description.empty())
        throw std::runtime_error("Description cannot be empty.");
    if (act < 1 || act > 3)
        throw std::runtime_error("Act must be 1, 2, or 3.");

    // Check for duplicate description in the same act
    for (const auto& idea : ideaRepo.getAll()) {
        if (idea.getDescription() == description && idea.getAct() == act)
            throw std::runtime_error("Idea with this description already exists in the same act.");
    }

    ideaRepo.addIdea(Idea(description, creator, act, "proposed"));
    ideaRepo.saveToFile("ideas.txt");
    notifyObservers();
}

void Service::acceptIdea(const std::string& description, int act, const std::string& writerName) {
    bool isSenior = false;
    for (const auto& writer : writerRepo.getAll()) {
        if (writer.getName() == writerName && writer.getExpertise() == "Senior") {
            isSenior = true;
            break;
        }
    }

    if (!isSenior)
        throw std::runtime_error("Only Senior writers can accept ideas.");

    ideaRepo.updateStatus(description, act, "accepted");
    ideaRepo.saveToFile("ideas.txt");
    notifyObservers();
}



void Service::saveIdeasToFile(const std::string& filename) {
    ideaRepo.saveToFile(filename);
}
std::vector<Idea> Service::getIdeasByAct(int act) const {
    std::vector<Idea> result;
    for (const auto& idea : ideaRepo.getAll()) {
        if (idea.getAct() == act)
            result.push_back(idea);
    }
    return result;
}

std::vector<Idea> Service::getAcceptedIdeasByWriter(const std::string& writerName) const {
    std::vector<Idea> result;
    for (const auto& idea : ideaRepo.getAll()) {
        if (idea.getStatus() == "accepted" && idea.getCreator() == writerName)
            result.push_back(idea);
    }
    return result;
}
