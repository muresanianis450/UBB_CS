#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;
/*
 * SortedMultiMap constructor
 * Best case: 0(1) - when the capacity is 1;
 * Total case: O(capacity)   0(1)
 * Worst case: 0(capacity)
 */
SortedMultiMap::SortedMultiMap(Relation r) : capacity(10), size_(0), firstFree(0), r(r), loadFactor(0.7f) {
	table = new Node[capacity];
	for (int i = 0 ; i < capacity ; i++) {
		table[i].next = EMPTY_NODE;
	}
}
/*
 * Hash function that maps the key to an index in the table
 * Best case = Worst case = Average case = 0(1)
 */
int SortedMultiMap::hash(TKey key) const {

	return abs(key) % capacity; // hash function that maps the key to an index in the table
}

/*Resize and rehash the table
 *Best Case: 0(n) - all keys have distinct positions, each key has only one value, the add() functions adds to an empty position each time
 *Total Case: O(1)
 *Worst Case : 0(n^2) - all keys have the same hash value, the add() function adds to the same position each time
 */
void SortedMultiMap::resizeAndRehash() {
	int oldCapacity = capacity;
	capacity *= 2;
	Node* oldTable = table;
	// create a new table with double the capacity
	table = new Node[capacity];
	for (int i = 0 ; i < capacity ; i++) {
		table[i].next = EMPTY_NODE;
	}
	size_ = 0;
	firstFree = 0;

	// rehash the elements from the old table
	for (int i = 0; i< oldCapacity ; i++) {
		if (oldTable[i].key != NULL_TVALUE) {
			for (int j = 0 ; j < oldTable[i].valueSize ; j++) {
				add(oldTable[i].key, oldTable[i].values[j]);//Add each value of each key to the new table
			}
			delete[] oldTable[i].values; // free the memory allocated for the values
		}
	}
}

/*
 * Adding a new key-value pair to the multimap
 * Best case: 0(1) - when the table is empty or the key does not previously do exist
* Average case: Traverse a short chain (O(L)). Possibly resize a small value array (O(k)). Overall O(L + k) = O(n)
* Worst case: O(n + k) - all key hash have the same value, the add() function adds to the same position each time
*			  O(n^2)   - if resizeAndRehash() is called, the function will traverse all the elements in the old table and rehash them
 */
void SortedMultiMap::add(TKey c, TValue v) {
	if ((float)size_ / capacity >= loadFactor)
		resizeAndRehash();

	int pos = hash(c); // find the position in the table
// check if the key already exists
	if (table[pos].key == NULL_TVALUE){
		table[pos].key = c;
		table[pos].values = new TValue[1];
		table[pos].values[0] = v;
		table[pos].valueSize = 1;
		table[pos].valueCapacity = 1;  // ✅ Add this line
		size_++;
	}else {// if the key already exists
		int current = pos;// get the current position
		while (current != EMPTY_NODE && table[current].key != c) {//traverse the list
			current = table[current].next;//move to the next node
		}
		if (current != EMPTY_NODE) {// if the key already exists
			if (table[current].valueSize == table[current].valueCapacity) {
				// resize the values array
				table[current].valueCapacity *= 2;
				TValue* newValues = new TValue[table[current].valueCapacity];
				for (int i = 0; i < table[current].valueSize; i++) {
					newValues[i] = table[current].values[i];
				}
				delete[] table[current].values;
				table[current].values = newValues;
			}table[current].values[table[current].valueSize++] = v; // add the new value to the array
			size_++;// increment the size of the multimap
		}else { //if the key does not exist
			int freePos = firstFree; //get the first free position
			while (freePos < capacity && table[freePos].key != NULL_TVALUE)
					freePos++;// find the next free position

			if (freePos == capacity) {
				resizeAndRehash(); // if there is no free position, resize and rehash
				add(c,v);
				return;
			}
			// assign the key and value to the new node
			firstFree = freePos;
			table[freePos].key = c;
			table[freePos].values = new TValue[1];
			table[freePos].values[0] = v;
			table[freePos].valueSize = 1;
			table[freePos].valueCapacity = 1;
			table[freePos].next = table[pos].next ; // set the next pointer to the next node
			table[pos].next = freePos;
			size_++; // increment the size of the multimap
		}
	}

}

/*
 * Search for the values belonging to a given key
 * Best case: 0(1) - when the key is found in the first position
 * Total case: O(n/2) = O(n) - when the key is found in the middle of the list
 * Worst case: 0(n) - when the key is found at the end of the list or not found at all
 */
vector<TValue> SortedMultiMap::search(TKey c) const {
	int pos = findPosition(c); // find the position of the key
	if (pos == EMPTY_NODE)
		return {};

	std::vector<TValue> result;
	for (int i = 0 ; i < table[pos].valueSize ; i++) {
		result.push_back(table[pos].values[i]); // add the values to the result vector
	}
	return result;
}


/*
 * Remove a key-value pair from the multimap
 *Best Case : 0(1) - when hash(c) points directly at my value, the first value in the list is the one I want to remove and the node is not empty(I don t need to unlink)
 *Average Case: O(L + k) , where L = the length of the chain and k = the number of values scanned to get key c..... WE CAN AMORTIZE THIS TO 0(1)
 *Worst Case:  O(n + k) - when the key is not found in the table, or key is at the end of a long chain (L = n) , after removal the key has no more values -> unlink
 */
bool SortedMultiMap::remove(TKey c, TValue v) {
	int pos = hash(c);
	int prev = EMPTY_NODE;

	// Traverse the chain to find the key
	while (pos != EMPTY_NODE && table[pos].key != c) {
		prev = pos;
		pos = table[pos].next;
	}

	if (pos == EMPTY_NODE) {
		return false; // Key not found
	}

	bool found = false;

	// Search for the value in the values array
	for (int i = 0; i < table[pos].valueSize; i++) {
		if (table[pos].values[i] == v) {
			found = true;

			// Shift values to the left to remove the value
			for (int j = i; j < table[pos].valueSize - 1; j++) {
				table[pos].values[j] = table[pos].values[j + 1];
			}

			table[pos].valueSize--;
			size_--;
			break;
		}
	}

	// If the node has no values left, remove the node
	if (table[pos].valueSize == 0) {
		delete[] table[pos].values;
		table[pos].values = nullptr;
		table[pos].key = NULL_TVALUE;

		if (prev != EMPTY_NODE) {
			table[prev].next = table[pos].next; // Update the previous node's next pointer
		}

		table[pos].next = EMPTY_NODE; // Mark the node as empty

		// Update firstFree to the current position if it's earlier
		if (pos < firstFree) {
			firstFree = pos;
		}
	}

	return found;
}


/*
 * Returns the number of key-value pairs from the multimap
 * Best case: 0(1)
 * Average case: 0(1)
 * Worst case: 0(1)
 */
int SortedMultiMap::size() const {
	return size_;
}

/**
 * Returns true if the multimap is empty, false otherwise2
* Best case: 0(1)
 * Average case: 0(1)
 * Worst case: 0(1)
 *
 */
bool SortedMultiMap::isEmpty() const {
	return size_ == 0;
}


/**
 * Best case: 0(1) - the key does not exist in the table
 * Average case: O(n/2) = O(n) - the key is found in the middle of the list
 * Worst case: O(n) - the key is found at the end of the list or not found at all
 * @param key : the key to search for
 * @return returns the position of the key in the table or EMPTY_NODE if the key is not found
 */
int SortedMultiMap::findPosition(TKey key ) const {
	int pos = hash(key);
	while (pos != EMPTY_NODE && table[pos].key != key) {
		pos = table[pos].next; // traverse the list
	}
	return pos; // return the position of the key
}
/*
 * Assign the iterator to the first element of the multimap
 * Best case: 0(1) = Average case = Worst case
 */
SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

/*
 *Constructor
 * Best case: 0(1) - when the table is empty
 * Average case: O(n/2) = O(n) - when the table is half full
 * Worst case: O(n) - when the table is full
 */
SortedMultiMap::~SortedMultiMap() {
	for (int i = 0; i < capacity; i++) {
		delete[] table[i].values;
	}
	delete[] table;

}


/**
 * Complexity:
 * BC = 0(n) - when no trimming is needed
 * WC = 0(n+m) - all keys have more than maxSize values.
 *			m = the total number of values in the map
 * AC = 0(n + k)
 *			k = the number of keys that have more than maxSize values
 * TC = O(n + m)
 * @param maxSize : the maximum number of values allowed for each key
 * @return the total number of values removed from the multimap
 */
int SortedMultiMap::trimValues(int maxSize) {
	if (maxSize < 0) {
		return 0; // No values to trim
	}
	int totalRemoved = 0;
	for (int i = 0; i< capacity; ++i) {
		if (table[i].key != NULL_TVALUE && table[i].valueSize >maxSize) {
			int toRemove = table[i].valueSize - maxSize;
			//remove the last values (does not matter which ones)
			table[i].valueSize = maxSize;
			totalRemoved += toRemove;
			size_ -= toRemove; // Decrease the size of the multimap


 		}
	}
	return totalRemoved;
}