#pragma once
#include "Observer.h"
#include <vector>

class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }
protected:
    void  notifyObservers() {
        for (auto obs: observers) {
            obs->update();
        }
    }
};