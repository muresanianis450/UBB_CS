#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <exception>

/**
 * Complexity:
 * BC = AC = WC = TC = 0(1)
 * @param d the sorted multimap to iterate over
 */
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	stackCapacity = map.capacity;
	stack = new int[stackCapacity];
	stackTop = -1;
	currentNode = -1;
	valueIndex = -1;
	first();

}

/**
 * Complexity:
 * BC = 0(1) if node is -1
 * WC = 0(m) if we have to traverse all the nodes (The tree is skewed)
 * AC = 0(log n) if the tree is balanced
 * TC =O(n)
 * @param node node index from which to push all left children onto the stack
 */
void SMMIterator::pushLeftPath(int node) {
	while (node != -1) {
		stack[++stackTop] = node; //Push the current node onto the stack
		node = map.left[node]; //Move to the left child
	}
}
/**
 * Complexity:
 * BC = 0(1) if the stack is empty
 * WC = 0(n) if the tree is skewed, we have to traverse all nodes
 * AC = 0(log n) if the tree is balanced
 * TC = O(n)
 */
void SMMIterator::first(){
	stackTop = -1; // Reset the stack
	pushLeftPath(map.root); //Push all left children of the root onto the stack

	if (stackTop != -1){
	currentNode = stack[stackTop--]; // Pop the top node from the stack
		valueIndex = 0; // Start with the first value in the current node
	}else
		currentNode = -1;

}

/**
 * BC =	0(1) if the current node is -1 or if the value index is valid
 * WC = 0(n) if we have to traverse all nodes in the worst case
 * AC =0(1) AMORTIZED because each node is pushed and popped from the stack only once during a full traversal.
 * TC = O(n)
 */
void SMMIterator::next(){
	if (!valid()) {
		throw exception();
	}

	valueIndex++;
	if (valueIndex >= map.valueCounts[currentNode]) {
		//Move to the next node in-order traversal
		if (map.right[currentNode] != -1) {
			pushLeftPath(map.right[currentNode]);// Push all left children of the right child onto the stack
		}
		if (stackTop != -1) {
			currentNode = stack[stackTop--]; // Pop the next node from the stack
			valueIndex = 0; // Reset value index for the new current node
		} else {
			currentNode = -1; // No more nodes left
		}
	}
}

/**
 * BC = WC = AC = TC: Θ(1)
 * @return if the node is valid
 */
bool SMMIterator::valid() const{
	return currentNode != -1;
}

/**
 * BC = WC = AC = TC: Θ(1)
 * @return current key-value pair
 */
TElem SMMIterator::getCurrent() const{
	if (!valid()) {
		throw exception();
	}
	return pair<TKey,TValue>(map.keys[currentNode],map.values[currentNode][valueIndex]);
	return NULL_TELEM;
}

SMMIterator::~SMMIterator() {
	delete[] stack;
}

