#include "PriorityQueue.h"
#include <iostream>

// Constructor: Initializes the priority queue with a given relation
PriorityQueue::PriorityQueue(Relation r) {
    capacity = 10; // Initial capacity of the array
    nodes = new DLLANode[capacity]; // Allocate memory for the array
    size = 0; // Initialize size to 0
    head = -1; // Head of the list is initially invalid
    tail = -1; // Tail of the list is initially invalid
    relation = r; // Store the relation function

    // Initialize the free list
    for (int i = 0; i < capacity - 1; i++) {
        nodes[i].next = i + 1; // Point each node to the next
    }
    nodes[capacity - 1].next = -1; // Last node points to -1
    firstEmpty = 0; // First free position is at index 0
}

// Allocates a free position from the free list
int PriorityQueue::allocate() {
    if (firstEmpty == -1) throw runtime_error("Out of memory"); // No free positions available
    int newPos = firstEmpty; // Get the first free position
    firstEmpty = nodes[firstEmpty].next; // Update the free list
    return newPos; // Return the allocated position
}

// Frees a position and returns it to the free list
void PriorityQueue::free(int pos) {
    nodes[pos].next = firstEmpty; // Point the freed position to the current first free
    firstEmpty = pos; // Update the first free position
}

// Resizes the array when it is full
void PriorityQueue::resize() {
    int newCapacity = capacity * 2; // Double the capacity
    DLLANode* newNodes = new DLLANode[newCapacity]; // Allocate a new array

    // Copy existing elements to the new array
    for (int i = 0; i < capacity; i++) {
        newNodes[i] = nodes[i];
    }

    // Initialize the new free list
    for (int i = capacity; i < newCapacity - 1; i++) {
        newNodes[i].next = i + 1;
    }
    newNodes[newCapacity - 1].next = -1; // Last node points to -1

    firstEmpty = capacity; // Update the first free position
    capacity = newCapacity; // Update the capacity

    delete[] nodes; // Deallocate the old array
    nodes = newNodes; // Update the nodes pointer
}

// Inserts an element in the correct position based on priority
void PriorityQueue::insertOrdered(Element e) {
    if (firstEmpty == -1) resize(); // Resize if no free positions are available
    int newPos = allocate(); // Allocate a new position
    nodes[newPos].info = e; // Store the element
    nodes[newPos].next = -1; // Initialize next and prev
    nodes[newPos].prev = -1;

    if (head == -1) {
        // If the list is empty, set the new element as head and tail
        head = tail = newPos;
        return;
    }

    int current = head;
    // Traverse the list to find the correct position
    while (current != -1 && relation(nodes[current].info.second, e.second)) {
        current = nodes[current].next;
    }

    if (current == -1) {
        // Insert at the tail
        nodes[newPos].prev = tail;
        nodes[tail].next = newPos;
        tail = newPos;
    } else {
        // Insert before the current position
        nodes[newPos].next = current;
        nodes[newPos].prev = nodes[current].prev;

        if (nodes[current].prev != -1) {
            nodes[nodes[current].prev].next = newPos;
        } else {
            head = newPos; // Update head if inserting at the beginning
        }
        nodes[current].prev = newPos;
    }
}

// Adds an element to the queue based on priority
void PriorityQueue::push(TElem e, TPriority p) {
    insertOrdered({e, p}); // Insert the element in the correct position
    size++; // Increment the size
}

// Returns the element with the highest priority
Element PriorityQueue::top() const {
    if (isEmpty()) throw runtime_error("Queue is empty."); // Throw exception if the queue is empty
    return nodes[head].info; // Return the element at the head
}

// Removes and returns the element with the highest priority
Element PriorityQueue::pop() {
    if (isEmpty()) throw runtime_error("Queue is empty."); // Throw exception if the queue is empty
    int oldHead = head; // Store the current head
    Element elem = nodes[head].info; // Get the element at the head

    head = nodes[head].next; // Update the head to the next element
    if (head != -1) {
        nodes[head].prev = -1; // Update the prev pointer of the new head
    } else {
        tail = -1; // If the queue is now empty, reset the tail
    }

    free(oldHead); // Free the old head position
    size--; // Decrement the size
    return elem; // Return the removed element
}

// Checks if the queue is empty
bool PriorityQueue::isEmpty() const {
    return size == 0; // Return true if size is 0
}

// Destructor: Deallocates the memory used by the queue
PriorityQueue::~PriorityQueue() {
    delete[] nodes; // Deallocate the array
}


//________________________


// BC: 0(1), WC: O(n), AC: O(n)
TPriority PriorityQueue::priorityOf(TElem elem) const {
    int current = head; // Start from the head of the list
    while (current != -1) { // Traverse the list
        if (nodes[current].info.first == elem) {
            return nodes[current].info.second; // Return the priority if the element is found
        }
        current = nodes[current].next; // Move to the next node
    }
    return -1; // Return -1 if the element is not found
}