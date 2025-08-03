#include "TaskRepository.h"
#include <sstream>
#include <algorithm>

TaskRepository::TaskRepository(const std::string &programmersFile = "programmers.txt", const std::string &tasksFile= "tasks.txt")
    :programmersFile(programmersFile), tasksFile(tasksFile){

    std::ifstream finProg(programmersFile);

    std::string name;
    int id;
    while (finProg >> name >> id) {
        programmers.emplace_back(name, id);
    }
    finProg.close();

    std::ifstream finTask(tasksFile);
    std::string line;
    while (std::getline(finTask, line)) {
        std::istringstream iss(line);
        std::string description, status,progIdStr;
        std::getline(iss,description, ',');
        std::getline(iss,status, ',');
        std::getline(iss,progIdStr);
        int progId = std::stoi(progIdStr);

        tasks.emplace_back(description, status, progId);
    }
    finTask.close();
}
void TaskRepository::saveTaskToFile() const {
    std::ofstream fout(tasksFile);
    for (const auto& task : tasks) {
        fout << task.getDescription() << ',' << task.getStatus() << ',' << task.getProgrammerId() << '\n';
    }
    fout.close();

}

const std::vector<Programmer>& TaskRepository::getProgrammers() const {
    return programmers;
}
const std::vector<Task>& TaskRepository::getTasks() const {
    return tasks;
}

void TaskRepository::addTask(const Task& task) {
    tasks.push_back(task);
}
void TaskRepository::removeTask(const Task& task) {
    auto it = std::remove_if(tasks.begin(), tasks.end(), [&task](const Task& t) {
        return t.getDescription() == task.getDescription();
    });
    if (it !=tasks.end())
        tasks.erase(it,tasks.end());
}

void TaskRepository::updateTask(const Task& oldTask,const Task& newTask) {
    for (auto& task : tasks) {
        if (task.getDescription() == oldTask.getDescription()) {
            task = newTask;
            return;
        }
    }
}

