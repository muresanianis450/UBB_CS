#pragma once
#include <string>

class Question {
private:
    int id;
    std::string text, correctAnswer;
    int score;
public:
    Question(int id, std::string text, std::string correctAnswer, int score);
    int getID() const;
    std::string getText()const;
    std::string getCorrectAnswer()const;
    int getScore() const;

    void setId(int id);
    void setText(const std::string& text);
    void setCorrectAnswer(const std::string& answer);
    void setScore(int score);
};