#pragma once
#include <vector>
#include "Observer.h"
#include <algorithm>
class Observable {
private:
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }
    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notifyObservers() {
        for (Observer* observer : observers) {
            observer->update();
        }
    }
    virtual ~Observable() = default;
};
