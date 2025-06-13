#include <assert.h>

#include "SortedIteratedList.h"
#include "ListIterator.h"
#include <iostream>

#include <exception>
using namespace std;

bool relation1(TComp e1, TComp e2) {
	if (e1 <= e2) {
		return true;
	}
	else {
		return false;
	}
}

void testAll(){
	SortedIteratedList list = SortedIteratedList(relation1);
	assert(list.size() == 0);
	assert(list.isEmpty());
    list.add(1);
    assert(list.size() == 1);
    assert(!list.isEmpty());
    ListIterator it = list.search(1);
    assert(it.valid());
    assert(it.getCurrent() == 1);
    it.next();
    assert(!it.valid());
    it.first();
    assert(it.valid());
    ListIterator itFirst = list.first();
    assert(itFirst.valid());
    assert(itFirst.getCurrent() == 1);
    assert(list.remove(it) == 1);
    assert(list.size() == 0);
    assert(list.isEmpty());
}
void testJumpBackward() {
	// Create a sorted list and populate it
	cout<<"Test jumpBackward" << endl;
	SortedIteratedList list(relation1);
	list.add(1);
	list.add(2);
	list.add(3);
	list.add(4);
	list.add(5);

	// Create an iterator for the list
	ListIterator it = list.iterator();

	// Move the iterator to the last element
	it.first();
	it.next(); // Now at 2
	it.next(); // Now at 3
	it.next(); // Now at 4
	it.next(); // Now at 5

	// Test jumpBackward with valid k
	try {
		it.jumpBackward(2); // Should move to 3
		std::cout << "Current element after jumpBackward(2): " << it.getCurrent() << std::endl;
	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Test jumpBackward with k larger than the number of elements before the current
	try {
		it.jumpBackward(5); // Should throw an exception
	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	// Test jumpBackward with invalid k (negative or zero)
	try {
		it.jumpBackward(0); // Should throw an exception
	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}

	try {
		it.jumpBackward(-1); // Should throw an exception
	} catch (const std::exception& e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
}

