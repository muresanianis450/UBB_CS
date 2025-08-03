#include "Answer.h"
Answer::Answer(int id, int questionId, const std::string& user, const std::string& text, int votes)
    : id(id), questionId(questionId), user(user), text(text), votes(votes) {}
std::string Answer::getUser() const {
    return user;
}
std::string Answer::getText() const {
    return text;
}
int Answer::getId() const {
    return id;
}
int Answer::getQuestionId() const {
    return questionId;
}
int Answer::getVotes() const {
    return votes;
}
void Answer::setVotes(int votes) {
    this->votes = votes;
}
