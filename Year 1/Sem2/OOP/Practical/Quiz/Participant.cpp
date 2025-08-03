#include "Participant.h"

Participant::Participant(const std::string &name,int score = 0) {
    this->name = name;
    this->score = score;
}

std::string Participant::getName() const {
    return name;
}
int Participant::getScore() const {
    return score;
}
void Participant::setScore(int score) {
    Participant::score = score;
}


