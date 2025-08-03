#include "Repository.h"
#include <fstream>
#include <sstream>

// Constructor: Load users, questions, and answers
Repository::Repository(const std::string& usersFile, const std::string& questionsFile, const std::string& answersFile)
    : usersFile(usersFile), questionsFile(questionsFile), answersFile(answersFile) {

    // Load users
    std::ifstream fin(usersFile);
    std::string line;
    while (getline(fin, line)) {
        if (!line.empty()) {
            users.emplace_back(line);
        }
    }
    fin.close();

    // Load questions
    std::ifstream finQuestions(questionsFile);
    std::string questionLine;
    while (getline(finQuestions, questionLine)) {
        if (!questionLine.empty()) {
            std::istringstream iss(questionLine);
            std::string idStr, text, user;
            std::getline(iss, idStr, '|');
            std::getline(iss, text, '|');
            std::getline(iss, user, '|');
            questions.emplace_back(std::stoi(idStr), text, user);
        }
    }
    finQuestions.close();

    // Load answers
    std::ifstream finAnswers(answersFile);
    std::string lineAnswer;
    while (getline(finAnswers, lineAnswer)) {
        if (!lineAnswer.empty()) {
            std::istringstream iss(lineAnswer);
            std::string idStr, questionIdStr, user, text, votesStr;
            std::getline(iss, idStr, '|');
            std::getline(iss, questionIdStr, '|');
            std::getline(iss, user, '|');
            std::getline(iss, text, '|');
            std::getline(iss, votesStr, '|');
            answers.emplace_back(std::stoi(idStr), std::stoi(questionIdStr), user, text, std::stoi(votesStr));
        }
    }
    finAnswers.close();
}

// Getters
const std::vector<User>& Repository::getUsers() const {
    return users;
}
const std::vector<Question>& Repository::getQuestions() const {
    return questions;
}
const std::vector<Answer>& Repository::getAnswers() const {
    return answers;
}

// Mutators
void Repository::addQuestion(const Question& question) {
    questions.push_back(question);
}
void Repository::addAnswer(const Answer& answer) {
    answers.push_back(answer);
}
void Repository::updateAnswer(const std::vector<Answer>& updatedAnswers) {
    answers = updatedAnswers;
}

// Save to files
void Repository::saveQuestions() const {
    std::ofstream fout(questionsFile);
    for (const auto& question : questions) {
        fout << question.getId() << "|" << question.getText() << "|" << question.getUser() << "\n";
    }
    fout.close();
}

void Repository::saveAnswers() const {
    std::ofstream fout(answersFile);
    for (const auto& answer : answers) {
        fout << answer.getId() << "|" << answer.getQuestionId() << "|"
             << answer.getUser() << "|" << answer.getText() << "|"
             << answer.getVotes() << "\n";
    }
    fout.close();
}
