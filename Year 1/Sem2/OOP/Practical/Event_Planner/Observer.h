#pragma once
#include <vector>

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
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