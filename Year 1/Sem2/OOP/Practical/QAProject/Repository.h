#pragma once
#include <string>
#include <vector>
#include "Question.h"
#include "Answer.h"
#include "User.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

class Repository {
private:
    std::string usersFile;
    std::string questionsFile;
    std::string answersFile;

    std::vector<User> users;
    std::vector<Question> questions;
    std::vector<Answer> answers;

public:
    Repository(const std::string& usersFile, const std::string& questionsFile, const std::string& answersFile);

    const std::vector<User>& getUsers() const;
    const std::vector<Question>& getQuestions() const;
    const std::vector<Answer>& getAnswers() const;

    void addQuestion(const Question& question);
    void addAnswer(const Answer& answer);
    void updateAnswer(const std::vector<Answer>& updatedAnswers);

    void saveQuestions() const;
    void saveAnswers() const;
};