#pragma once
#include "Observer.h"
#include <vector>

class Observable {
protected:
    std::vector<Observer*> observers;

public:
    void addObserver(Observer* obs);
    void notifyObservers();
};