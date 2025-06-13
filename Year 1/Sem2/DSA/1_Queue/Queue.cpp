#include "Queue.h"
#include <exception>
#include <iostream>

using namespace std;


Queue::Queue() {
    // No need to implement the vector, it is done automatically
}


void Queue::push(TElem elem) {
    elements.push_back(elem);

}


TElem Queue::top() const {
    if (elements.empty())
        throw runtime_error("Queue is empty");
    return elements.front();
}

TElem Queue::pop() {
    if(elements.empty())
        throw runtime_error("Queue is empty");
    TElem frontElem = elements.front();
    elements.erase(elements.begin());
    return frontElem;
}

bool Queue::isEmpty() const {
    if (elements.empty())
        return true;
    return false;
}


Queue::~Queue() {
    // No need to implement the vector, it is done automatically
}
