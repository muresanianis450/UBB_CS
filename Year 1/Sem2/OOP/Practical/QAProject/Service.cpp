#include "Service.h"

void Service::addQuestion(const std::string& text, const std::string& user) {
    if (text.empty())
        throw std::runtime_error("Question text cannot be empty.");

    int id = repo.getQuestions().empty() ? 1 : repo.getQuestions().back().getId() + 1;
    Question q(id, text, user);
    repo.addQuestion(q);
    repo.saveQuestions();
    notifyObservers();
}

void Service::addAnswer(int questionId, const std::string& user, const std::string& text) {
    if (text.empty())
        throw std::runtime_error("Answer text cannot be empty.");

    int id = repo.getAnswers().empty() ? 1 : repo.getAnswers().back().getId() + 1;
    Answer a(id, questionId, user, text, 0);
    repo.addAnswer(a);
    repo.saveAnswers();
    notifyObservers();
}

void Service::updateAnswerVotes(int answerId, int newVotes, const std::string& currentUser) {
    auto answers = repo.getAnswers();
    for (auto& answer : answers) {
        if (answer.getId() == answerId) {
            if (answer.getUser() == currentUser)
                return; // Do not allow user to vote their own answer

            answer.setVotes(newVotes);
            break;
        }
    }
    repo.updateAnswer(answers);
    repo.saveAnswers();
    notifyObservers();
}

std::vector<Answer> Service::getAnswersForQuestion(int questionId) const {
    std::vector<Answer> result;
    for (const auto& answer : repo.getAnswers()) {
        if (answer.getQuestionId() == questionId)
            result.push_back(answer);
    }
    return result;
}