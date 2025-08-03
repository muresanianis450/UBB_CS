#pragma once
#include "Task.h"
#include "Programmer.h"
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>


class TaskRepository {
    std::vector<Programmer> programmers;
    std::vector<Task> tasks;
    std::string programmersFile;
    std::string tasksFile;

public:
    TaskRepository(const std::string& programmersFile, const std::string& tasksFile);

    void saveTaskToFile() const;

    const std::vector<Programmer>& getProgrammers() const;
    const std::vector<Task>& getTasks() const;

    void addTask(const Task& task);
    void removeTask(const Task& task);
    void updateTask(const Task& oldTask, const Task& newTask);

};