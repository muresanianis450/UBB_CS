#pragma once

#include "Participant.h"
#include "Question.h"
#include <vector>
#include <string>
#include <fstream>

class Repository {
private:
    std::vector<Participant> participants;
    std::vector<Question> questions;
    std::string participantsFile, questionsFile;

public:
    Repository(std::string participantsFile, std::string questionsFile);

    void saveToFile();
    const std::vector<Participant>& getParticipants() const;
    const std::vector<Question>& getQuestions() const;

    bool addQuestion(const Question& q );
    bool updateParticipantScore(const std::string& name, int score);
};
