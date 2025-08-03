#include "Observable.h"

void Observable::addObserver(Observer* observer) {
    observers.push_back(observer);
}
void Observable::notifyObservers() {
    for (auto obs: observers) {
        if (obs)
            obs->update();
    }
}