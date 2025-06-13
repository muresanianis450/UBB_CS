#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
#define EMPTY_NODE -1
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

struct Node {
	TKey key;
	TValue* values;
	int valueCapacity; //the capacity of the value array
	int valueSize; //the number of values in the array
	int next; //the index of the next node in the list

	Node() {
		key = NULL_TVALUE;
		values = nullptr;
		valueCapacity = 0;
		valueSize = 0;
		next = -1;
	}

};
class SortedMultiMap {
	friend class SMMIterator;
    private:
		Node* table; //the array of nodes
		int capacity; //the capacity of the hash table
		int size_; //the number of key-value pairs in the multimap
		int firstFree; //the index of the first free node
		Relation r;
		float loadFactor; //the load factor of the hash table
	void resizeAndRehash();
	int hash(TKey key) const;
	int findPosition(TKey key) const;

    public:
	int trimValues(int maxSize);
    // constructor
    SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multimap
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multimap is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
