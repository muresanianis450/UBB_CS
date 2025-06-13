#pragma once
//DO NOt INCLUDE LISTITERATOR

//DO NOT CHANGE THIS PART
class ListIterator;
typedef int TComp;
typedef bool (*Relation)(TComp, TComp);
#define NULL_TCOMP -11111


struct Node {
	TComp data;
	Node* next;
	Node* prev;
};
class SortedIteratedList {
private:
	friend class ListIterator;
private:
	Node* head; //pointer to the first node
	Node* tail; //pointer to the last node
	int length; //number of elements in the list
	Relation relation;

public:
	// constructor
	SortedIteratedList(Relation r); // O(1)

	// returns the number of elements from the list
	int size() const;	 // O(1)

	// verifies if the list is empty
	bool isEmpty() const;	 // O(1)

	// returns the first position from the list
	ListIterator first() const;

	// returns the element from the given position
	//throws an exception if the position is not valid
	TComp getElement(ListIterator pos) const;

	// adds a new element to the list
	void add(TComp e); // O(n) >> t(1) || t(n)

	// removes the element from position pos
	//returns the removed element
	//after removal pos is positioned on the next element (the one after the removed one) or it is invalid if the last element was removed
	//throws an exception if the position is not valid

	TComp remove(ListIterator& poz); // O(n) >> t(1) || t(n)

	// searches for the first occurrence of an element 
	//returns an iterator that points to the element, if it appear in the list, or an invalid iterator if the element is not in the list
	ListIterator search(TComp e) const; //O(n)


	//void print();

	//destructor
	~SortedIteratedList(); //O(1)

	ListIterator iterator() const;  // O(1)

};
