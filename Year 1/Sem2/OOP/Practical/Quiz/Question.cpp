#include "Question.h"

Question::Question(int id, std::string text, std::string correctAnswer, int score) {
    this->id = id;
    this->text = text;
    this->correctAnswer = correctAnswer;
    this->score = score;
}

int Question::getScore() const {
    return score;
}
std::string Question::getText() const {

    return text;
}
std::string Question::getCorrectAnswer() const {
    return correctAnswer;
}
int Question::getID() const {
    return id;
}

void Question::setScore(int score) {
    Question::score = score;
}
void Question::setText(const std::string& text) {
    Question::text = text;
}
void Question::setId(int id) {
    Question::id = id;
}
void Question::setCorrectAnswer(const std::string& correctAnswer) {
    Question::correctAnswer = correctAnswer;
}







