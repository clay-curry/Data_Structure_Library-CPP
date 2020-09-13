#ifndef __ABSTRACT_LINKEDLIST__H
#define __ABSTRACT_LINKEDLIST__H
#include <iostream>
#include <exception>
#include "Enumeration.h"

template<class DT> class AbstractLinkedList;		// CLASS PROTOTYPE

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


// LLEnumerator: contains methods for traversing the LinkedList. 
// Assume that i and j are iterators. 
//	++i : advances one element in the LinkedList and returns a reference to i.
//	i++ : advances one element in the LinkedList and returns i's previous value
//	*i  : returns a reference to the element at i's current position  
//	i!=j: returns true if i and j are positioned at different elements
template<typename DT>
class LLEnumerator : public Enumeration<DT>
{
	friend AbstractLinkedList<DT>;
protected:
	AbstractLinkedList<DT>* _LL;
public:
	LLEnumerator();
	LLEnumerator(AbstractLinkedList<DT>*);
	bool hasMoreElements() override;
	DT& nextElement() override;
	DT& operator*(void);
	LLEnumerator<DT>& operator++ (void);
	LLEnumerator<DT>& operator++ (int);
	bool operator != (const LLEnumerator<DT>& rhs);
};
template<class DT> LLEnumerator<DT>::LLEnumerator() : _LL(NULL) {};
template<class DT> LLEnumerator<DT>::LLEnumerator(AbstractLinkedList<DT>* LL) : _LL(LL) {};
template<class DT> bool LLEnumerator<DT>::hasMoreElements()
{
	return ((_LL != NULL) && (!_LL->isEmpty()));
}
template<typename DT> DT& LLEnumerator<DT>::nextElement()
{
	if ((_LL == NULL) || (_LL->isEmpty())) throw LinkedListBounds();
	AbstractLinkedList<DT>* curr = _LL;
	_LL = _LL->next();
	return curr->info();
}
template<typename DT> DT& LLEnumerator<DT>::operator*(void)
{
	if ((_LL == NULL) || (_LL->isEmpty())) throw LinkedListBounds();
	return _LL->info();
}
//---------------------------------Pre Increment-------------------------------------
template<typename DT> LLEnumerator<DT>& LLEnumerator<DT>::operator++(void)
{
	if ((_LL == NULL) || (_LL->isEmpty())) throw LinkedListBounds();
	_LL = _LL->next();
	return *this;
}
//---------------------------------Post Increment-------------------------------------
template<typename DT> LLEnumerator<DT>& LLEnumerator<DT>::operator++(int)
{
	if ((_LL == NULL) || (_LL->isEmpty())) throw LinkedListBounds();
	LLEnumerator<DT> temp(_LL);
	_LL = _LL->next();
	return temp;
}
template<typename DT> bool LLEnumerator<DT>::operator!=(const LLEnumerator<DT>& rhs)
{
	return (_LL != rhs._LL);
}
//---------------------------------------------------------------------------------------------------------------



template<typename DT>
class AbstractLinkedList
{
	friend std::ostream& operator<<(std::ostream& s, AbstractLinkedList<DT>& ll)
	{
		ll.display(s);
		return s;
	}
public:
	typedef LLEnumerator<DT> iterator;

	Enumeration<DT>* enumerator();
	virtual LLEnumerator<DT> begin();
	virtual LLEnumerator<DT> end();
	virtual void display(std::ostream&);

	// Pure virtuals
	virtual bool isEmpty() = NULL;
	virtual DT& info() = NULL;
	virtual AbstractLinkedList<DT>* next() = NULL;
	virtual int size() = NULL;
	virtual DT& find(const DT&) = NULL;
	virtual DT& infoAt(int) = NULL;
	virtual void add(const DT&) = NULL;
	virtual void insertAt(const DT&, int) = NULL;
	virtual DT remove() = NULL;
	virtual DT remove(const DT&) = NULL;
	virtual DT removeAt(int) = NULL;
};
template<class DT> void AbstractLinkedList<DT>::display(std::ostream& s)
{
	Enumeration<DT>* e = enumerator();
	
	s << "[";
	if (e->hasMoreElements())
		s << e->nextElement();
	while (e->hasMoreElements())
	{
		s << ", " << e->nextElement();
	}
	s << "]";
	delete e;
};
template<typename DT> Enumeration<DT>* AbstractLinkedList<DT>::enumerator()
{
	return new LLEnumerator<DT>(this);
};
template<typename DT> LLEnumerator<DT> AbstractLinkedList<DT>::begin()
{
	return LLEnumerator<DT>(this);
};
template<typename DT> LLEnumerator<DT> AbstractLinkedList<DT>::end()
{
	return LLEnumerator<DT>(NULL);
};
#endif


