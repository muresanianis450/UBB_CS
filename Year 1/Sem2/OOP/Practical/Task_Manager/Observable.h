#pragma once
#include <vector>
#include <functional>

class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() = default;
};

class Observable {
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
protected:
    void notify() {
        for (auto obs: observers) {
            if (obs)
                obs->update();
        }
    }
    virtual ~Observable() = default;
};