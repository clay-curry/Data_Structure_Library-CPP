#ifndef __ABSTRACT_LINKEDLIST__H
#define __ABSTRACT_LINKEDLIST__H
#include <iostream>
#include <exception>
template<typename DT> class AbstractLinkedList;		// CLASS PROTOTYPE
template<typename DT> std::ostream& operator<<(std::ostream& s, AbstractLinkedList<DT>& ll);
// Root type for all LinkedList Exceptions
class LinkedListException : public std::exception {};
// Allocation using "new" failed
class LinkedListMemory : public LinkedListException {};
// The specified Node is outside the bounds of the LinkedList
class LinkedListBounds : public LinkedListException {};
// The specified Node could not be identified inside the bounds of the LinkedList
class LinkedListNotFound : public LinkedListException {};
// The LinkedList could not be attached to a LinkedList with no Info
class LinkedListAttachToEmpty : public LinkedListException {};
// AbstractLinkedList: defines the member functions expected for all implementations of LinkedList data structures.
// Essential Operations on a LinkedList include:
//   create()
//		// creates an empty LinkedList
//   isEmpty()
//		// returns true if the LinkedList is empty, but otherwise returns false
//   size()
//		// returns the number of nodes in the LinkedList
//   add(object)
//		// adds 'object' to the beginning of the LinkedList
//   info()
//		// returns the data from the head node, or NULL if the LinkedList is empty
//   next()
//		// returns the LinkedList pointed by this LinkedList
//   setNext()
//		// attaches a LinkedList following the head node. The LinkedList previously following that head node is returned.
//   delete()
//		// deletes the first node of the LinkedList.
template<typename DT>
class AbstractLinkedList
{
	friend std::ostream& operator<< <DT>(std::ostream& s, AbstractLinkedList<DT>& ll);
public:
	virtual void display(std::ostream&);

	// Pure virtuals
	virtual bool isEmpty() = NULL;
	virtual DT& info() = NULL;
	virtual AbstractLinkedList<DT>* next() = NULL;
	virtual int size() = NULL;
	virtual DT& find(DT&) = NULL;
	virtual DT& infoAt(int) = NULL;
	virtual void add(DT&) = NULL;
	virtual void insertAt(DT&, int) = NULL;
	virtual DT remove() = NULL;
	virtual DT remove(const DT&) = NULL;
	virtual DT removeAt(int) = NULL;
};
template<typename DT> std::ostream& operator<<(std::ostream& s, AbstractLinkedList<DT>& ll)
{
	ll.display(s);
	return s;
}
template<typename DT> void AbstractLinkedList<DT>::display(std::ostream& s)
{
	int n = size() - 1;					// n - number of elements to print to cout followed by a ","
	if (n == -1)
	{
		s << "{}";		// if size == 0 then cout << "{}"
		return;
	}
	s << "{";
	for (int i = 0; i < n; i++)				// prints (size() - 1) elements followed by ","
	{
		s << (*this).infoAt(i) << ",";
	}
	s << (*this).infoAt(n - 1) << "}";
	return;
}
#endif#pragma once
