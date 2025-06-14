#include "PriorityQueue.h"
#include "ShortTest.h"
#include <assert.h>
#include <iostream>

bool rel(TPriority p1, TPriority p2) {
	if (p1 <= p2) {
		return true;
	}
	else {
		return false;
	}
}




void testAll() { //call each function and see if it exists
	PriorityQueue pq(rel);
	
	assert(pq.isEmpty() == true);
	
	//adaugam 5, 3, 10, 2, 12 -> rezultat: 2, 3, 5, 10, 12
	pq.push(5, 5);
	assert(pq.top().first == 5);
	assert(pq.top().second == 5);
	pq.push(3, 3);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(10, 10);
	assert(pq.top().first == 3);
	assert(pq.top().second == 3);
	pq.push(2, 2);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	pq.push(12, 12);
	assert(pq.top().first == 2);
	assert(pq.top().second == 2);
	assert(pq.isEmpty() == false);
	assert(pq.pop().second == 2);
	assert(pq.top().second == 3);
	assert(pq.pop().second == 3);
	assert(pq.top().second == 5);
	assert(pq.pop().second == 5);
	assert(pq.top().second == 10);
	assert(pq.pop().second == 10);
	assert(pq.top().second == 12);
	assert(pq.pop().second == 12);
	assert(pq.isEmpty() == true);
}

void testLaboratoryFunctionality() {
	PriorityQueue pq(rel);
std::cout<<"Start testLaboratoryFunctionality\n";
	// Add elements to the priority queue
	pq.push(5, 5);
	pq.push(3, 3);
	pq.push(10, 10);
	pq.push(2, 2);
	pq.push(12, 12);


	// Test priorityOf for existing elements
	assert(pq.priorityOf(5) == 5);
	assert(pq.priorityOf(3) == 3);
	assert(pq.priorityOf(10) == 10);
	assert(pq.priorityOf(2) == 2);
	assert(pq.priorityOf(12) == 12);

	// Test priorityOf for non-existing elements
	assert(pq.priorityOf(7) == -1);
	assert(pq.priorityOf(0) == -1);
	assert(pq.priorityOf(15) == -1);

	// Test after removing elements
	pq.pop(); // Removes element with priority 2
	assert(pq.priorityOf(2) == -1); // Element 2 no longer exists
	assert(pq.priorityOf(3) == 3);  // Other elements remain unaffected
	std::cout<<"end testLaboratoryFunctionality\n";


}

