#ifndef __ABSTRACT_STACK__H
#define __ABSTRACT_STACK__H
#include <iostream>
#include <exception>
#include "Enumeration.h"

class StackException : public std::exception {};
class StackUnderflow : public StackException {};
class StackOverflow : public StackException {};
class StackMemoryException : public StackException {};


template<class DT> class AbstractStack;
template<class DT> std::ostream& operator<<(std::ostream&, AbstractStack<DT>&);

template<class DT>
class AbstractStack
{
	friend std::ostream& operator<< <DT>(std::ostream&, AbstractStack<DT>&);
public:
	// TRUE: if the Stack has no element
	virtual bool isEmpty() = 0;
	// Accesses the DT at the top of the stack; if the stack is empty, throws StackUnderflowException()
	virtual DT& peek() = 0;
	// get the DT that is stored at the top of the stack and remove it from the top of the stack; if the stack is empty, throws StackUnderflowException()
	virtual DT pop() = 0;
	// add the DT to the top of the stack; if the stack is of fixed size, then a StackOverflowException() may be thrown
	virtual void push(const DT&) = 0;
	virtual Enumeration<DT>* enumerator() = 0;
	virtual void display(std::ostream&);
};
template<typename DT> void AbstractStack<DT>::display(std::ostream& os)
{
	bool first = true;
	Enumeration<DT>* e = enumerator();
	os << "<";
	while (e->hasMoreElements())
	{
		if (!first) os << ",";
		first = false;
		os << e->nextElement();
	}
	os << ">";
	delete e;
}
template<typename DT> std::ostream& operator<< (std::ostream& os, AbstractStack<DT>& s)
{
	s.display(os);
	return os;
}
#endif