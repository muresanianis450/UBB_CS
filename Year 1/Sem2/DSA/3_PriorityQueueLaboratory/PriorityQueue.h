#pragma once
#include <utility>
#include <stdexcept>

using namespace std;

// DO NOT CHANGE THIS PART
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);
#define NULL_TELEM pair<TElem, TPriority> (-11111,-11111);

class PriorityQueue {
private:
    struct DLLANode {
        Element info;
        int next;
        int prev;
    };

    DLLANode* nodes;
    int capacity;
    int size;
    int head;
    int tail;
    int firstEmpty;
    Relation relation;

    // Doubles the capacity of the array when full
    // BC: Θ(n), WC: Θ(n), AC: Θ(n)
    void resize();

    // Allocates a free position from the list
    // BC: Θ(1), WC: Θ(1) , AC: Θ(1)
    int allocate();

    // Frees a position and returns it to the free list
    // BC: Θ(1), WC: Θ(1), AC: Θ(1)
    void free(int pos);

    // Inserts an element in the correct position based on priority
    // BC: Θ(1), WC: Θ(n), AC: Θ(n/2) = Θ(n)
    void insertOrdered(Element e);

public:
    // Constructor: initializes the priority queue with a given relation
    // BC: Θ(n), WC: Θ(n), AC: Θ(n)
    //Explanation: Initializes the array and sets
    //up the free list, which involves iterating through the array.
    PriorityQueue(Relation r);

    // Adds an element to the queue based on its priority
    // BC: Θ(1), WC: Θ(n), AC: Θ(n)
    void push(TElem e, TPriority p);

    // Returns the element with the highest priority
    // BC: Θ(1), WC: Θ(1), AC: Θ(1)
    // Throws an exception if the queue is empty
    Element top() const;

    // Removes and returns the element with the highest priority
    // BC: Θ(1), WC: Θ(1), AC: Θ(1)
    // Throws an exception if the queue is empty
    Element pop();

    // Checks if the queue is empty
    // BC: Θ(1), WC: Θ(1), AC: Θ(1)
    bool isEmpty() const;

    // Destructor: deallocates the memory used by the queue
    // BC: Θ(1), WC: Θ(1), AC: Θ(1)
    ~PriorityQueue();


    TPriority priorityOf(TElem elem) const;
};
