#pragma once
#include "Observable.h"
#include "Question.h"
#include "Participant.h"
#include "Repository.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class Service : public Observable{
private:
    Repository& repo ;

    std::unordered_map<std::string, std::set<int>> answered; //keep count of which answer each participant answered to

public:
    Service(Repository& repo);

    std::vector<Question> getQuestionSortedById() const;
    bool addQuestion(int id, const std::string& text, const std::string& correctAnswer, int score);

    std::vector<Question> getQuestionsSortedByScoreDesc() const;


    std::vector<Participant> getParticipantsSortedByScore() const;
    bool answerQuestion(const std::string& participant, int questionId, const std::string& answer);

    const std::vector<Participant>& getParticipants() const;
    int getScoreForParticipant(const std::string& name) const;

    void saveToFile();
};