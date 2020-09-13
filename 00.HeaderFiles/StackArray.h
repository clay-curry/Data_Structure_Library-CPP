#ifndef __STACKARRAY__H
#define __STACKARRAY__H
#include "AbstractStack.h"

template<typename DT> class StackArray;

template<typename DT>
class StackArrayEnumerator : public Enumeration<DT>
{
protected:
	StackArray<DT>* _stack;
	int _index;
public:
	StackArrayEnumerator(StackArray<DT>* SA);
	bool hasMoreElements();
	DT& nextElement();
};
template<typename DT> StackArrayEnumerator<DT>::StackArrayEnumerator(StackArray<DT>* stack)
{
	_stack = stack;
	if (_stack == NULL) { _index = 0; }
	else
	{
		_index = stack->size();
	}
}
template<typename DT> DT& StackArrayEnumerator<DT>::nextElement()
{
	if (0 < _index)
	{
		_index--;
		return _stack->arr[_index];
	}
	else throw StackUnderflow();
}
template<typename DT> bool StackArrayEnumerator<DT>::hasMoreElements()
{
	return (0 < _index);
}

template<typename DT>
class StackArray : virtual public AbstractStack<DT>
{
	friend class StackArrayEnumerator<DT>;
protected:
	int _top;
	int _max;
	DT* arr;
public:
	StackArray(int max);
	virtual ~StackArray();
	// TRUE: if the Stack has no elements
	virtual bool isEmpty();
	// TRUE: if the Stack is full
	virtual bool isFull();
	// gets the number of elements in the stack
	virtual int size();
	// Accesses the DT at the top of the stack; if the stack is empty, throws StackUnderflow()
	virtual DT& peek();
	// get the DT that is stored at the top of the stack and remove it from the top of the stack; if the stack is empty, throws StackUnderflow()
	virtual DT pop();
	// add the DT to the top of the stack; if the stack is of fixed size, then a StackOverflow() may be thrown
	virtual void push(const DT&);
	// returns the capacity of the stack
	virtual int max();
	virtual Enumeration<DT>* enumerator();
};
template<typename DT> StackArray<DT>::StackArray(int max) : _top(0), _max(0)
{
	arr = new DT[max];
	if (arr == NULL) throw StackMemoryException();
	_max = max;
}
template<typename DT> StackArray<DT>::~StackArray()
{
	if (arr != NULL)
	{
		delete arr;
		arr = NULL;
	}
	_top = 0;
	_max = 0;
}
template<typename DT> int StackArray<DT>::size()
{
	return _top;
}
template<typename DT> int StackArray<DT>::max()
{
	return _max;
}
template<typename DT> bool StackArray<DT>::isEmpty()
{
	return (_top == 0);
}
template<typename DT> bool StackArray<DT>::isFull()
{
	return (_top == _max);
}
template<typename DT> DT& StackArray<DT>::peek()
{
	if (isEmpty()) throw StackUnderflow();
	return arr[_top - 1];
}
template<typename DT> void StackArray<DT>::push(const DT& newObj)
{
	if (_top == _max) throw StackOverflow();
	arr[_top] = newObj;
	_top++;
}
template<typename DT> DT StackArray<DT>::pop()
{
	if (_top < 1) throw StackUnderflow();
	_top--;
	return arr[_top];
}
template<typename DT> Enumeration<DT>* StackArray<DT>::enumerator()
{
	return new StackArrayEnumerator<DT>(this);
}

#endif