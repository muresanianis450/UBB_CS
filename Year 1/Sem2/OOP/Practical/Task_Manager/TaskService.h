#pragma once
#include "TaskRepository.h"
#include "Observable.h"
class TaskService : public Observable{
private:
    TaskRepository repo;
public:
    explicit TaskService(TaskRepository& repo);

    const std::vector<Task>& getTasks() const;
    const std::vector<Programmer>& getProgrammers() const;

    void addTask(const std::string& description);
    void removeTask(const std::string& description);
    void startTask(const std::string& description, int programmerId);
    void completeTask(const std::string& description, int programmerId);

    void save();
};