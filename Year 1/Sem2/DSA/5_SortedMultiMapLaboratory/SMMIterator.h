#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	int* stack; //to simulate recursion (store node indeces)
	int stackTop;// index to top of stack
	int currentNode; //current node index
	int valueIndex; //index of the current value in the current node
	int stackCapacity; //capacity of the stack

	void pushLeftPath(int node);//helper to push all left children onto the stack
public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
	~SMMIterator();//to free memory
};

