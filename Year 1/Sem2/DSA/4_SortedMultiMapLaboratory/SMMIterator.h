#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	std::vector<std::pair<TKey, std::vector<TValue>>> sortedElements;
	int currentKeyIndex;
	int currentValueIndex;// vector to store the sorted elements
public:
	SMMIterator(const SortedMultiMap& d);
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;

	//____BONUS____

	 void jumpBackward(int k);
};

