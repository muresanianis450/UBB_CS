
#include "Question.h"
Question::Question(int id, const std::string& text, const std::string& user)
    : id(id), text(text), user(user) {}

int Question::getId() const {
return id;}

std::string Question::getText() const {
    return text;
}
std::string Question::getUser() const {
    return user;
}
