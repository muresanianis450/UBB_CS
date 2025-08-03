
#include "Service.h"

Service::Service(Repository &repo) : repo(repo) {}

std::vector<Question> Service::getQuestionSortedById() const {
    std::vector<Question> result = repo.getQuestions();
    std::sort(result.begin(), result.end(), [](const Question &q1, const Question &q2) {
        return q1.getID() < q2.getID();
    });
    return result;
}

bool Service::addQuestion(int id, const std::string& text, const std::string& correctAnswer, int score) {
    Question q (id, text, correctAnswer, score);
    bool ok = repo.addQuestion(q);
    if (ok)
        notify();

    return ok;
}

std::vector<Question> Service::getQuestionsSortedByScoreDesc() const {
    std::vector<Question> result = repo.getQuestions();
    std::sort(result.begin(), result.end(), [](const Question& q1, const Question& q2) {
        return q1.getScore() > q2.getScore();
    });
    return result;
}

bool Service::answerQuestion(const std::string &name, int id, const std::string &answer) {
    if (answered[name].count(id)) // check if already answered
        return false;

    //find question
    auto questions = repo.getQuestions();
    auto it = std::find_if(questions.begin(), questions.end(), [id](const Question& q) {
        return q.getID() == id;
    });
    if (it == questions.end())
        return false;

    if (it->getCorrectAnswer() == answer) {
        repo.updateParticipantScore(name, it->getScore());
        answered[name].insert(id);
        notify();
        return true;
    }

    return false;
}

const std::vector<Participant>& Service::getParticipants() const {
    return repo.getParticipants();
}
int Service::getScoreForParticipant(const std::string &name) const {
    for (const auto& p : repo.getParticipants()) {
        if (p.getName() == name)
            return p.getScore();
    }
    return 0;
}

void Service::saveToFile() {
    repo.saveToFile();
}


