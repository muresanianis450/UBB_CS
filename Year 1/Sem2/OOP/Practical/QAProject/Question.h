#pragma once
#include <string>

class Question {
private:
    int id;
    std::string text;
    std::string user;

public:
    Question(int id, const std::string& text, const std::string& user);
    int getId() const;
    std::string getText() const;
    std::string getUser() const;
};