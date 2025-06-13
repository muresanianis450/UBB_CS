#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;

/**
 * BC = WC = AC = TC = 0(1)
 * @param r relation that defines the order of the keys
 */
SortedMultiMap::SortedMultiMap(Relation r): rel(r), capacity(10), treeSize(0){
	keys = new TKey[capacity];
	values = new TValue*[capacity];
	valueCounts = new int[capacity];
	left = new int[capacity];
	right = new int[capacity];

	for (int i = 0; i < capacity ; i++) {
		values[i] = nullptr;
		left[i] = right[i] = -1;
		valueCounts[i] = 0;
	}
	root = -1;
	firstFree = 0;
}

/**
 * Complexity:
 * BC = AC = WC = TC 0(n) We always copy all elements from
 *					the old arrays to the new arrays, and we have to iterate through all
 */
void SortedMultiMap::resize() {
	int newCapacity = capacity * 2;
	TKey* newKeys = new TKey[newCapacity];
	TValue** newValues = new TValue*[newCapacity];
	int* newValueCounts = new int[newCapacity];
	int* newLeft = new int[newCapacity];
	int* newRight = new int[newCapacity];

	// Copy old arrays to new arrays
	for (int i = 0; i< capacity;i++) {
		newKeys[i] = keys[i];
		newValues[i] = values[i];
		newValueCounts[i] = valueCounts[i];
		newLeft[i] = left[i];
		newRight[i] = right[i];
	}
	// Clean up old arrays
	for (int i = capacity; i < newCapacity; i++) {
		newValues[i] = nullptr;
		newLeft[i] = newRight[i] = -1;
		newValueCounts[i] = 0;
	}
	delete[] keys;
	delete[] values;
	delete[] valueCounts;
	delete[] left;
	delete[] right;
	// Assign new arrays to the class members
	keys = newKeys;
	values = newValues;
	valueCounts = newValueCounts;
	left = newLeft;
	right = newRight;
	capacity = newCapacity;
}

/**
 * Complexity:
 * BC = AC = 0(1) if there's no resize needed
 * WC = 0(n) if a resize is needed
 * TC = O(n)
 * @param key Key to be added
 * @param value Value to be added
 * @return firstFree index of the newly created node
 */
int SortedMultiMap::createNode(TKey key, TValue value) {
	if (firstFree >= capacity) resize();

	keys[firstFree] = key; // Initialize the key
	values[firstFree] = new TValue[2];
	values[firstFree][0] = value; // Initialize the first value
	valueCounts[firstFree] = 1; // Initialize the count of values to 1
	left[firstFree] = -1;// No left child
	right[firstFree] = -1;// No right child
	return firstFree++;
}

/**
 * Complexity:
 * BC = 0(1) If valueCoutns[node] is 0
 * WC = 0(n) If valueCounts[node] is the maximum
 * AC = O(n) Every addValueToNode does full copy on each call
 * TC = O(n)
 * @param node Index of the node to which the value will be added
 * @param value Value to be added to the node
 */
void SortedMultiMap::addValueToNode(int node,TValue value) {
	int count = valueCounts[node];// get the current count of values
	TValue* newArr = new TValue[count + 1]; // Create a new array with one more element
	for ( int i = 0; i < count; i++)
		newArr[i] = values[node][i]; // Copy old values
	newArr[count] = value; // Add the new value

	delete[] values[node]; // Delete the old array
	values[node] = newArr; // Assign the new array
	valueCounts[node]++; // Increment the count of values
}

/**
 * Complexity:
 * BC = 0(1) If the tree is empty
 * WC = 0(n) if our key is the largest or smallest in the tree +
 *				+ our tree is not balanced, we have to traverse all nodes
 * AC = 0(log n) if the tree is balanced
 * TC = O(N)
 * @param c key to be added
 * @param v value to be added
 */
void SortedMultiMap::add(TKey c, TValue v) {
	//Tree is empty
	if  ( root == -1 ) {
		root = createNode(c,v);
		treeSize++;
		return;
	}

	int current = root;
	int parent = -1;

	while ( current != -1) {
		if (keys[current] == c) {
			addValueToNode(current,v); // If the key already exists, add the value to the node
			treeSize++;
			return;
		}
		parent = current;
		if (rel(c,keys[current]))
			current = left[current];// Move to the left child if the key is less than the current node's key
		else
			current = right[current];// Move to the right child if the key is greater than the current node's key

	}
	int newNode = createNode(c,v);
	if (rel(c,keys[parent]))
		left[parent] = newNode; // If the new key is less than the parent's key, set it as the left child
	else
		right[parent] = newNode; // Add the new node as a child of the parent

	treeSize++;
}

/**
 *Complexity:
 * BC = 0(1) If the tree is empty / if the key is the first node
 * WC = 0(n) if the key is not found in the tree
 * AC = 0(log n) if the tree is balanced <<BINARY SEARCH>>
 * TC = O(n)
 * @param c key to be searched
 * @return vector of values associated with the key
 */
vector<TValue> SortedMultiMap::search(TKey c) const {
	int current = root;
	while ( current != -1) {
		if ( keys[current] == c) {
			//Found the node; return the values as a vector
			return vector<TValue>(values[current],values[current]+valueCounts[current]);
		}
		if (rel(c,keys[current]))
			current = left[current]; // Move to the left child if the key is less than the current node's key
		else
			current = right[current];
	}
	return {}; // If the key is not found, return an empty vector

}

/**
 * Complexity:
 * BC = 0(1) if the tree is empty
 * WC = 0(n+m) where
 *				n is the height of unbalanced tree
 *				m the number of values
 *				Search: O(n) + Remove: O(n) + Tree restructuring: O(n)

 * AC = 0(log n+m) if the tree is balanced <<BINARY SEARCH>>
 *				Search: O(log n) + Remove: O(m) + Tree restructuring: O(log n)
 * TC = 0(h + m)
 * @param c the key to be removed
 * @param v the value to be removed
 * @return
 */
bool SortedMultiMap::remove(TKey key, TValue value) {
	bool removed = false;
	root = removeNodeInline(root, key, value, removed);
	if (removed) treeSize--;
	return removed;
}
int SortedMultiMap::removeNodeInline(int node, TKey key, TValue value, bool& removed) {
	if (node == -1) return -1;

	if (keys[node] == key) {
		// Inline removeValueFromNode
		int count = valueCounts[node];
		int index = -1;
		for (int i = 0; i < count; i++) {
			if (values[node][i] == value) {
				index = i;
				break;
			}
		}

		if (index == -1) return node;

		for (int i = index; i < count - 1; i++) {
			values[node][i] = values[node][i + 1];
		}
		valueCounts[node]--;
		removed = true;

		if (valueCounts[node] == 0) {
			// Physically remove the node
			if (left[node] == -1) return right[node];
			if (right[node] == -1) return left[node];

			// Find in-order successor (minimum in right subtree)
			int minNode = right[node];
			while (left[minNode] != -1) minNode = left[minNode];

			// Replace current node with minNode
			keys[node] = keys[minNode];

			delete[] values[node];
			values[node] = new TValue[valueCounts[minNode]];
			for (int i = 0; i < valueCounts[minNode]; i++) {
				values[node][i] = values[minNode][i];
			}
			valueCounts[node] = valueCounts[minNode];

			// Recursively delete successor node
			right[node] = removeNodeInline(right[node], keys[minNode], values[minNode][0], removed);
		}
	} else if (rel(key, keys[node])) {
		left[node] = removeNodeInline(left[node], key, value, removed);
	} else {
		right[node] = removeNodeInline(right[node], key, value, removed);
	}

	return node;
}


/**
 *Complexity:
 *BC = AC = WC = TC = 0(1)
 * @return size of the sorted multi map
 */
int SortedMultiMap::size() const {
	return treeSize;
}

/**
 *Complexity:
 * BC = AC = WC = TC = 0(1)
 * @return True: if the sorted multimap is empty, False: otherwise
 */
bool SortedMultiMap::isEmpty() const {
	return treeSize == 0;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	for (int i = 0; i< capacity; i++) {
		delete[] values[i];
	}
	delete[] keys;
	delete[] values;
	delete[] valueCounts;
	delete[] left;
	delete[] right;
}


int SortedMultiMap::trimValues(int maxSize) {
	if (maxSize < 0) return 0; // Invalid maxSize, return 0

	int removed = 0;
	int stackSize = capacity > 1000 ? capacity : 1000; // Allocate stack size based on capacity
	int* stack = new int[stackSize]; // Stack for iterative in-order traversal
	int top = -1;
	int node = root;

	// In-order traversal of BST (Left -> Node -> Right)
	while (node != -1 || top != -1) {
		// Go as left as possible
		while (node != -1) {
			stack[++top] = node;
			node = left[node];
		}

		// pop the node from the stack (visit current node)
		node = stack[top--];

		// If current node has more values than allowed, trim them
		if (valueCounts[node] > maxSize) {
			int toRemove = valueCounts[node] - maxSize;
			TValue* newArr = nullptr;

			// copy only the first maxSize values (preserving order)
			if (maxSize > 0) {
				newArr = new TValue[maxSize];
				for (int i = 0; i < maxSize; ++i)
					newArr[i] = values[node][i];
			}

			// Free old value array and assign the trimmed one
			delete[] values[node];
			values[node] = newArr;
			valueCounts[node] = maxSize;

			removed += toRemove;
			treeSize -= toRemove;
		}

		// Move to the right subtree
		node = right[node];
	}

	delete[] stack;
	return removed;
}