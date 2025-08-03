#pragma once
#include <vector>

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
    };

    virtual ~Observable() = default;
protected:
    void notify() {
        for (auto observer : observers) {
            observer->update();
        }
    }
};
