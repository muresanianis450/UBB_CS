#pragma once
#include <string>
#include <vector>
#include "Repository.h"
#include "Observable.h"

class Service : public Observable {
private:
    Repository repo;

public:
    Service(Repository& r) : repo(r) {}

    const std::vector<User>& getUsers() const {return repo.getUsers();}
    const std::vector<Question>& getQuestions() const {return repo.getQuestions();}
    const std::vector<Answer>& getAnswers() const {return repo.getAnswers();}

    void addQuestion(const std::string& text, const std::string& user);
    void addAnswer(int questionId, const std::string& user, const std::string& text);
    void updateAnswerVotes(int answerId, int newVotes, const std::string& user);

    std::vector<Answer> getAnswersForQuestion(int questionId) const;
};