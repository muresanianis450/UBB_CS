#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIteratedList::SortedIteratedList(Relation r) {
this->relation = r;
	this->head = nullptr;
	this->tail = nullptr;
	this->length = 0;
}

int SortedIteratedList::size() const {
	return this->length;
}

bool SortedIteratedList::isEmpty() const {
	return this->length == 0 ;
}

ListIterator SortedIteratedList::first() const {

	return ListIterator(*this,this->head);
}

TComp SortedIteratedList::getElement(ListIterator poz) const {
	if (!poz.valid()) {
		throw exception();
	}
	return poz.getCurrent();
}

TComp SortedIteratedList::remove(ListIterator& poz) {
	if (!poz.valid()) {
		throw exception();
	}
	Node* nodeToDelete = poz.current;
	TComp data = nodeToDelete->data;

	// Save the pointer to the next node before deleting
	Node* nextNode = nodeToDelete->next;

	// Unlink the node from the list
	if (nodeToDelete->prev == nullptr) { // Removing the head
		if (nodeToDelete->next != nullptr) { // More than one element
			this->head = nodeToDelete->next;
			nodeToDelete->next->prev = nullptr;
		} else { // Only one element in the list
			this->head = nullptr;
			this->tail = nullptr;
		}
	} else if (nodeToDelete->next == nullptr) { // Removing the tail
		this->tail = nodeToDelete->prev;
		nodeToDelete->prev->next = nullptr;
	} else { // Removing from the middle
		nodeToDelete->prev->next = nodeToDelete->next;
		nodeToDelete->next->prev = nodeToDelete->prev;
	}

	// Free the memory of the node
	delete nodeToDelete;
	this->length--;

	// Instead of calling poz.next(), directly update the iterator:
	poz.current = nextNode;

	return data;
}

ListIterator SortedIteratedList::search(TComp e) const {
    Node* current = this->head;
    while (current != nullptr) {
        if (current->data == e) {
            return ListIterator(*this, current);
        }
        current = current->next;
    }
    return ListIterator(*this);
}

void SortedIteratedList::add(TComp e) {
	Node* newNode = new Node{e, nullptr, nullptr}; // Create a new node
	if (this->head == nullptr || !this->relation(this->head->data, e)) { // Insert at the beginning
		newNode->next = this->head;
		if (this->head != nullptr) {
			this->head->prev = newNode;
		}
		this->head = newNode; // Update head
		if (this->tail == nullptr) {
			this->tail = newNode;
		}
	} else { // Insert in the middle or end
		Node* current = this->head;
		while (current->next != nullptr && this->relation(current->next->data, e)) {
			current = current->next;
		} // Move to the right position
		newNode->next = current->next;
		if (current->next != nullptr) {
			current->next->prev = newNode;
		} else {
			this->tail = newNode;
		} // Update tail if needed
		current->next = newNode;
		newNode->prev = current;
	}
	this->length++; // Increment the list size
}

SortedIteratedList::~SortedIteratedList() {
	Node* current = this->head;
	while (current != nullptr) {
		Node* toDelete = current;
		current = current->next;
		delete toDelete;
	}
}

ListIterator SortedIteratedList::iterator() const {
	return ListIterator(*this, head);
}
