#pragma once
#include <vector>
#include "Observer.h"

class Subject {
protected:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    }



    void notifyObservers() {
        for (auto obs : observers) {
            obs->update();
        }
    }

    virtual ~Subject() = default;
};
