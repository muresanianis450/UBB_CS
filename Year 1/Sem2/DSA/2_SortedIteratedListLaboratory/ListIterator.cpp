#include "ListIterator.h"
#include "SortedIteratedList.h"
#include <exception>
using namespace std;

ListIterator::ListIterator(const SortedIteratedList& list, Node* node) : list(list), current(node) {}

ListIterator::ListIterator(const SortedIteratedList& list) : list(list), current(nullptr) {}

void ListIterator::first() {
	this->current = list.head;
}

void ListIterator::next() {
	if (!this->valid()) {
		throw exception();
	}
	this->current = this->current->next;
}

bool ListIterator::valid() const {
	return this->current != nullptr;
}

TComp ListIterator::getCurrent() const {
	if (!this->valid()) {
		throw exception();
	}
	return this->current->data;
}


//ADDITIONAL________________________________________

 void ListIterator::jumpBackward(int k){
	if (!this->valid())
		throw exception(); // Iterator is not valid
	if (k <= 0)
		throw exception(); // k must be positive

	int steps = 0;
	Node* temp = this->current;
	while (temp != nullptr && steps < k) {
		temp = temp->prev;
		steps++;
	}

	if (steps < k)
		throw exception(); // k is larger than the number of elements before current
	else
		this->current = temp;
}

