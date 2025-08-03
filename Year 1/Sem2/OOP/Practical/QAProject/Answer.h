#pragma once
#include <string>

class Answer {
private:
    int id;
    int questionId;
    std::string user;
    std::string text;
    int votes;
public:
    Answer(int id, int questionId, const std::string& user, const std::string& text, int votes = 0);
    int getId() const;
    int getQuestionId() const;
    std::string getUser() const;
    std::string getText() const;
    int getVotes() const;
    void setVotes(int votes);
};