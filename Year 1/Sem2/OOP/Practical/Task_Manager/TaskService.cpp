
#include "TaskService.h"
#include <algorithm>
#include <stdexcept>

TaskService::TaskService(TaskRepository &repo):repo(repo) {}

const std::vector<Task>& TaskService::getTasks() const {
    return repo.getTasks();
}
const std::vector<Programmer>& TaskService::getProgrammers() const {
    return repo.getProgrammers();
}
void TaskService::addTask(const std::string& description){
    Task tesk (description, "open",-1);
    repo.addTask(tesk);
    notify();
    repo.saveTaskToFile();
}
void TaskService::removeTask(const std::string &description) {
    const auto &tasks = repo.getTasks();

    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task &t) {
        return t.getDescription() == description;
    });



    if (it != tasks.end()) {
        repo.removeTask(*it);
        notify();
        repo.saveTaskToFile();
    } else {
        throw std::invalid_argument("task was not found");
    }
}

void TaskService::startTask(const std::string &description, int programmerId) {
    auto tasks = repo.getTasks();
    auto it = std::find_if(tasks.begin(),tasks.end(),[&](const Task& t) {
        return t.getDescription() == description;
    });
    if (it == tasks.end()) {
        throw std::invalid_argument("task was not found");
    }
    if (it->getStatus() != "open") {
        throw std::invalid_argument("task is not open");
    }
   Task updated(description, "in progress", programmerId);
    repo.updateTask(*it, updated);
    notify();
    repo.saveTaskToFile();
}

void TaskService::completeTask(const std::string& description,int programerId) {
    std::vector<Task> tasks = repo.getTasks();

    auto it = std::find_if(tasks.begin(), tasks.end(), [&](const Task& t) {
        return t.getDescription() == description;
    });
    if (it == tasks.end()) {
        throw std::invalid_argument("task was not found");
    }
    if (it->getStatus() != "in progress") {
        throw std::invalid_argument("cannot close tasks that are not in progress");
    }
    if (it->getProgrammerId() != programerId) {
        throw std::invalid_argument("task is not assigned to you");
    }
    Task updated(description, "closed", programerId);
    repo.updateTask(*it, updated);
    notify();
    repo.saveTaskToFile();
}


