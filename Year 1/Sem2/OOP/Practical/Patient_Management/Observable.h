#pragma once

#include <vector>
#include <algorithm>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
protected:
    void notifyObservers() {
        for (auto obs: observers)
            obs->update();
    }
};