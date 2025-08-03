#pragma once

#include <string>

class Participant {
private:
    std::string name;
    int score;
public:
    Participant(const std::string& name,int score);
    std::string getName() const;
    int getScore() const;
    void setScore(int score);
};