#include "Repository.h"
#include <sstream>
#include <algorithm>
#include <iostream>

Repository::Repository(std::string participantsFile, std::string questionsFile) {
    this->participantsFile = participantsFile;
    this->questionsFile = questionsFile;

    std::ifstream finP(participantsFile);
    std::string name;
    while (getline(finP,name)) {
        if (!name.empty())
            participants.emplace_back(name,0);
    }

    finP.close();

    std::ifstream finQ(questionsFile);
    std::string line;
    while (getline(finQ,line)) {
        std::stringstream ss(line);
        std::string idString,text,correct,scoreString;
        getline(ss,idString,';');
        getline(ss,text,';');
        getline(ss,correct,';');
        getline(ss,scoreString,';');
        try {
            int id = std::stoi(idString);
            int score = std::stoi(scoreString);
            questions.emplace_back(id,text,correct,score);
        }catch (const std::exception& e) {
            std::cout << e.what() << idString<<std::endl;
            continue;
        }
    }
    finQ.close();

}

void Repository::saveToFile() {
    std::ofstream fout(questionsFile);

    for (const auto& q : questions) {
        fout << q.getID()<< ";"
        << q.getText()<< ";"
             << q.getCorrectAnswer()<< ";"
             << q.getScore()<<"\n";
    }
    fout.close();
}

const std::vector<Participant>& Repository::getParticipants() const {
    return participants;
}
const std::vector<Question>& Repository::getQuestions() const {
    return questions;
}

bool Repository::addQuestion(const Question &q) {
    auto it = std::find_if(questions.begin(),questions.end(),[&q](const Question& q2) {
        return q2.getID() == q.getID();
    });
    if (it != questions.end())
        return false;
    questions.push_back(q);
    return true;
}


bool Repository::updateParticipantScore(const std::string& name, int score) {
    for (auto& participant : participants) {
        if (participant.getName() == name) {
            participant.setScore(participant.getScore() + score);
            return true;
        }
    }
    return false;
}





