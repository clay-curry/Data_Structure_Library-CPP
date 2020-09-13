#ifndef __STACK_LINKED__H
#define __STACK_LINKED__H
#include "AbstractStack.h"
#include "LinkedList.h"

template<class DT> class StackLinked;

template<class DT>
class StackLinkedEnumerator : public Enumeration<DT>
{
protected:
	AbstractLinkedList<DT>* LL;
public:
	StackLinkedEnumerator(StackLinked<DT>* stack);
	StackLinkedEnumerator(AbstractLinkedList<DT>* ll);
	bool hasMoreElements();
	DT& nextElement();
	DT& operator*(void);
	StackLinkedEnumerator<DT>& operator++ (void);
	StackLinkedEnumerator<DT>& operator++ (int);
	bool operator != (const StackLinkedEnumerator<DT>& rhs);
};
template<class DT> StackLinkedEnumerator<DT>::StackLinkedEnumerator(StackLinked<DT>* stack)
{
	if (stack == NULL)
		LL = NULL;
	else
		LL = &stack->LL;
};
template<class DT> StackLinkedEnumerator<DT>::StackLinkedEnumerator(AbstractLinkedList<DT>* ll) : LL(ll) {};
template<class DT> bool StackLinkedEnumerator<DT>::hasMoreElements()
{
	return LL != NULL;
};
template<class DT> DT& StackLinkedEnumerator<DT>::nextElement()
{
	if (LL == NULL) throw StackOverflow();
	AbstractLinkedList<DT>* oldLL = LL;
	LL = LL->next();
	return oldLL->info();
};
template<typename DT> DT& StackLinkedEnumerator<DT>::operator*(void)
{
	if ((LL == NULL) || (LL->isEmpty())) throw StackOverflow();
	return LL->info();
}
//---------------------------------Pre Increment-------------------------------------
template<typename DT> StackLinkedEnumerator<DT>& StackLinkedEnumerator<DT>::operator++(void)
{
	if ((LL == NULL) || (LL->isEmpty())) throw StackOverflow();
	LL = LL->next();
	return *this;
}
//---------------------------------Post Increment-------------------------------------
template<typename DT> StackLinkedEnumerator<DT>& StackLinkedEnumerator<DT>::operator++(int)
{
	if ((LL == NULL) || (LL->isEmpty())) throw StackOverflow();
	StackLinkedEnumerator<DT> temp(LL);
	LL = LL->next();
	return temp;
}
template<typename DT> bool StackLinkedEnumerator<DT>::operator!=(const StackLinkedEnumerator<DT>& rhs)
{
	return (LL != rhs.LL);
}
//---------------------------------------------------------------------------------------------------------------



template<class DT>
class StackLinked : virtual public AbstractStack<DT>
{
	friend StackLinkedEnumerator<DT>;
protected:
	LinkedList<DT> LL;
public:
	typedef StackLinkedEnumerator<DT> iterator;
	Enumeration<DT>* enumerator();
	StackLinkedEnumerator<DT> begin();
	StackLinkedEnumerator<DT> end();


	StackLinked() : LL() {};
	virtual ~StackLinked() {};
	virtual bool isEmpty();
	virtual DT& peek();
	virtual void push(const DT& newDataType);
	virtual DT pop();
};

template<class DT> bool StackLinked<DT>::isEmpty() 
{ 
	return LL.isEmpty(); 
};
template<class DT> DT& StackLinked<DT>::peek()
{
	if (isEmpty()) throw StackUnderflow();
	return LL.info();
};
template<class DT> void StackLinked<DT>::push(const DT& newDataType)
{
	LL.add(newDataType);
};
template<class DT> DT StackLinked<DT>::pop()
{
	if (isEmpty()) throw StackUnderflow();
	return LL.remove();
};
template<class DT> Enumeration<DT>* StackLinked<DT>::enumerator()
{
	return new StackLinkedEnumerator<DT>(this);
};
template<class DT> StackLinkedEnumerator<DT> StackLinked<DT>::begin()
{
	return StackLinkedEnumerator<DT>(this);
};
template<class DT> StackLinkedEnumerator<DT> StackLinked<DT>::end()
{
	LinkedList<DT>* e = NULL;
	return StackLinkedEnumerator<DT>(e);
}
#endif // !__STACK_LINKED__H