#pragma once
#include <vector>
#include <algorithm>

#include "Observer.h"


class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* obs) {
        observers.push_back(obs);
    };
protected:
    void notifyObservers();
};

