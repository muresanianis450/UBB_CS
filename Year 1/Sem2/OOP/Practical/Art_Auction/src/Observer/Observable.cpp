
#include "Observable.h"

void Observable::notifyObservers() {
    for (auto obs: observers) {
        obs->update();
    }
}
