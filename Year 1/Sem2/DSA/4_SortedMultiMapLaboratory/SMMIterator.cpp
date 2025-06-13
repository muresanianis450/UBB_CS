#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <algorithm>
#include <stdexcept>


/**
 * SmmIterator constructor
 * Assuming std::sort is O(nlogn)
 *Best case = 0(1) - when the table is empty
 *Total case = O(n/2 * n/2*n/2logn/2) = O(nlogn) - when the table is half full
 *Worst case = 0(nlogn) - when the table is full
 *
 * @param d Multimap to iterate over
 */
SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d), currentKeyIndex(0), currentValueIndex(0) {
	for (int i = 0; i < map.capacity; i++) { // iterate over the table
		if (map.table[i].key != NULL_TVALUE) {// if the key is not empty
			std::vector<TValue> values(map.table[i].values, map.table[i].values + map.table[i].valueSize); // copy the values to a vector
			sortedElements.emplace_back(map.table[i].key, values);// add the key and values to the sortedElements vector
		}
	}

	std::sort(sortedElements.begin(), sortedElements.end(), [this](const auto& a, const auto& b) {// sort the sortedElements vector
		return map.r(a.first, b.first);// use the relation to sort the elements
	});
}

/**
 * Assign the iterator to the first element of the multimap
 * Best case = Total case = Worst case = 0(1)
 */
void SMMIterator::first() {
	currentKeyIndex = 0;
	currentValueIndex = 0;
}

/**
 * returns the next element in the multimap
 * Best case = 0(1) - when the iterator is at the last element
 * Total case = O(n)
 * Worst case = 0(n) - when the iterator is at the first element
 */
void SMMIterator::next() {
	if (!valid()) {
		throw std::out_of_range("Iterator out of range");
	}

	currentValueIndex++;// increment the value index
	if (currentValueIndex >= sortedElements[currentKeyIndex].second.size()) { // if the value index is out of range
		//we go to the next key
		currentKeyIndex++;// increment the key index
		currentValueIndex = 0;// reset the value index
	}
}

/**
 * Best case = Total case = Worst case = 0(1)
 * @return 1: if the iterator is valid
 */
bool SMMIterator::valid() const {
	return currentKeyIndex < sortedElements.size();
}

/**
 * Best case = Total case = Worst case = 0(1)
 * @return the pair of <key, value> at the current position of the iterator
 */
TElem SMMIterator::getCurrent() const {
	if (!valid()) {
		throw std::out_of_range("Iterator out of range");
	}

	return {
		sortedElements[currentKeyIndex].first, // key
		sortedElements[currentKeyIndex].second[currentValueIndex] //value
	};
}



//____BONUS____

/**
 * Moves the current element from the iterator k steps backward of makes the iterator invalid if there
 *	are less than k elements left until the beginning of the SortedMultiMap
 *	throws: an exception if the iterator is INVALID when the operation is called or if K is ZERO / NEGATIVE
 *	param: k - the number of steps to move backward
 *	Best case: O(1)
 */

void SMMIterator::jumpBackward(int k) {
	if (k <= 0) {
		throw std::invalid_argument("k must be positive, larger than 0");
	}
	if (!valid()) {
		throw std::out_of_range("Iterator is invalid");
	}

	int steps = k;
	while (steps > 0) { // Move backward k steps
		if (currentValueIndex > 0) {
			// Move within the current key's values
			currentValueIndex--;
			steps--;
		} else {
			if (currentKeyIndex == 0) {
				// Not enough steps available; invalidate iterator
				currentKeyIndex = sortedElements.size(); // this makes valid() return false
				currentValueIndex = 0;
				return;
			}
			currentKeyIndex--;
			currentValueIndex = sortedElements[currentKeyIndex].second.size() - 1;
			steps--;
		}
	}
}
