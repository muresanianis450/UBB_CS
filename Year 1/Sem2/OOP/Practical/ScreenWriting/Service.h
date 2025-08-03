#pragma once
#include "WriterRepository.h"
#include "IdeaRepository.h"
#include "Subject.h"

class Service: public Subject {
    WriterRepository& writerRepo;
    IdeaRepository& ideaRepo;

public:
    Service(WriterRepository& wr, IdeaRepository& ir) : writerRepo(wr), ideaRepo(ir) {}

    const std::vector<Writer>& getAllWriters() const;
    const std::vector<Idea>& getAllIdeas() const;

    void addIdea(const std::string& description, const std::string& creator, int act);
    void acceptIdea(const std::string& description, int act, const std::string& writerName);

    void saveIdeasToFile(const std::string &filename);


    std::vector<Idea> getIdeasByAct(int act) const;
    std::vector<Idea> getAcceptedIdeasByWriter(const std::string& writerName) const;
};
