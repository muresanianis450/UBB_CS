#pragma once
#include "SortedIteratedList.h"

// DO NOT CHANGE THIS PART
class ListIterator {
	friend class SortedIteratedList;
private:
	const SortedIteratedList& list;
	Node* current;

	ListIterator(const SortedIteratedList& list, Node* node);
	ListIterator(const SortedIteratedList& list);

public:
	void first(); //O(1)
	void next(); //O(1)
	void jumpBackward(int k); //O(k)
	bool valid() const; //O(1)
	TComp getCurrent() const; //O(1)
};