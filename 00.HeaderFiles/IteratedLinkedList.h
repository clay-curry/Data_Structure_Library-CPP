
#ifndef __ABSTRACT_LINKEDLIST__H
#define __ABSTRACT_LINKEDLIST__H
#include <iostream>
class Exception {};

template<typename DT> class AbstractLinkedList;		// CLASS PROTOTYPE
template<typename DT> class LLEnumerator;			// CLASS PROTOTYPE
template<typename DT> class Enumeration;			// CLASS PROTOTYPE

// Root type for all LinkedList Exceptions
class LinkedListException : public Exception {};
// Allocation using "new" failed
class LinkedListMemory : public LinkedListException {};
// The specified Node is outside the bounds of the LinkedList
class LinkedListBounds : public LinkedListException {};
// The specified Node could not be identified inside the bounds of the LinkedList
class LinkedListNotFound : public LinkedListException {};
// The LinkedList could not be attached to a LinkedList with no Info
class LinkedListAttachToEmpty : public LinkedListException {};

#ifndef __ITERATOR__H
#define __ITERATOR__H

class EnumerationException : public Exception {};

template<typename DT>
class Enumeration
{
public:
	// boolean method which determines whether there are any more elements in the data structure being Enumerated
	virtual bool hasMoreElements() = NULL;
	// returns the object which is the next element
	virtual DT& nextElement() = NULL;
};

//------------------------------------------------------------------------------

// LLEnumerator: contains methods for traversing the LinkedList. 
//
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
	bool hasMoreElements() override { return ((_LL != NULL) && (!_LL->isEmpty())); };
	DT& nextElement() override;
	LLEnumerator() : _LL(NULL) {};
	LLEnumerator(AbstractLinkedList<DT>* LL) : _LL(LL) {};
	DT& operator*(void);
	LLEnumerator<DT> operator++ (void);
	LLEnumerator<DT> operator++ (int);
	bool operator != (LLEnumerator<DT> rhs);
};
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
template<typename DT> LLEnumerator<DT> LLEnumerator<DT>::operator++(void)
{
	if ((_LL == NULL) || (_LL->isEmpty())) throw LinkedListBounds();
	_LL = _LL->next();
	return *this;
}
template<typename DT> LLEnumerator<DT> LLEnumerator<DT>::operator++(int)
{
	if ((_LL == NULL) || (_LL->isEmpty())) throw LinkedListBounds();
	LLEnumerator<DT>* temp = new LLEnumerator<DT>(_LL);
	_LL = _LL->next();
	return *temp;
}
template<typename DT> bool LLEnumerator<DT>::operator!=(LLEnumerator<DT> rhs)
{
	return (_LL != rhs._LL);
}
#endif /* __ITERATOR__H */

//---------------------------------------------------------------------------------------------------------------

template<typename DT> std::ostream& operator<<(std::ostream& s, AbstractLinkedList<DT>& ll);
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
	typedef LLEnumerator<DT> iterator;

	Enumeration<DT>* enumerator();	// may not be overridden
	virtual LLEnumerator<DT> begin();
	virtual LLEnumerator<DT> end();
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
template<typename DT> Enumeration<DT>* AbstractLinkedList<DT>::enumerator()
{
	return new LLEnumerator<DT>(this);
}
template<typename DT> LLEnumerator<DT> AbstractLinkedList<DT>::begin()
{
	return *(new LLEnumerator<DT>(this));
}
template<typename DT> LLEnumerator<DT> AbstractLinkedList<DT>::end()
{
	return NULL;
}
template<typename DT> void AbstractLinkedList<DT>::display(std::ostream& s)
{
	int n = size() - 1;					// n - number of elements to print to cout followed by a ","
	if (n == -1)
	{
		s << "{}";		// if size == 0 then cout << "{}"
		return;
	}
	Enumeration<DT>* e = enumerator();	// to be traversed using for-loop
	s << "{";
	for (int i = 0; i < n; i++)				// prints (size() - 1) elements followed by ","
	{
		s << e->nextElement() << ",";
	}
	s << e->nextElement() << "}";
	return;
}

#endif

#ifndef __LINKEDLIST__H
#define __LINKEDLIST__H

template<typename DT> class LinkedList : public AbstractLinkedList<DT>
{
	void copy(const LinkedList<DT>&);
protected:
	DT* _info;
	LinkedList<DT>* _next;
public:
	LinkedList();
	LinkedList(DT&);
	LinkedList(DT&, LinkedList<DT>*);
	LinkedList(const LinkedList<DT>&);

	~LinkedList();
	bool isEmpty() override;
	DT& info() override;
	int size() override;
	DT& find(DT&) override;
	DT& infoAt(int) override;
	void add(DT&) override;
	void insertAt(DT&, int) override;
	DT remove() override;
	DT remove(const DT&) override;
	DT removeAt(int) override;
	void operator=(const LinkedList<DT>&);
	virtual AbstractLinkedList<DT>* next() override;
};
//
template<typename DT> LinkedList<DT>::LinkedList() : _info(NULL), _next(NULL) {};
//
template<typename DT> LinkedList<DT>::LinkedList(DT& info)
{
	_info = new DT(info);
	if (_info == NULL) throw LinkedListMemory();
	_next = NULL;
}
// Constructs a new Node, dynamically (manually) stores 'info' deep-copy, and points to 'next'
template<typename DT> LinkedList<DT>::LinkedList(DT& info, LinkedList<DT>* next)
{
	_info = new DT(info);
	if (_info == NULL) throw LinkedListMemory();
	_next = next;
}
template<typename DT> LinkedList<DT>::LinkedList(const LinkedList<DT>& ll)
{
	copy(ll);
}
template<typename DT> void LinkedList<DT>::copy(const LinkedList<DT>& ll)
{
	if (ll._info == NULL) _info = NULL;
	else
	{
		_info = new DT(*(ll._info));
		if (_info == NULL) throw LinkedListMemory();
	}
	if (ll._next == NULL) _next = NULL;
	else
	{
		_next = new LinkedList<DT>(*(ll._next));
		if (_next == NULL) throw LinkedListMemory();
	}
}
//
template<typename DT> LinkedList<DT>::~LinkedList()
{
	if (_info != NULL)
	{
		delete _info;
		_info = NULL;
	}
	if (_next != NULL)
	{
		delete _next;
		_next = NULL;
	}
}
template<typename DT> bool LinkedList<DT>::isEmpty()
{
	return (_info == NULL);
}
template<typename DT> DT& LinkedList<DT>::info()
{
	if (isEmpty()) throw LinkedListBounds();
	return *_info;
}
//
template<typename DT> int LinkedList<DT>::size()
{
	if (_next == NULL)	return (_info == NULL) ? 0 : 1;
	else return 1 + _next->size();
}
//
template<typename DT> DT& LinkedList<DT>::find(DT& key)
{
	if (isEmpty()) throw LinkedListNotFound();	// if Node does not have _Info
	if (key == *_info) return *_info;
	if (_next == NULL) throw LinkedListBounds();
	return _next->find(key);
}
//
template<typename DT> DT& LinkedList<DT>::infoAt(int position)
{
	if (_info == NULL) throw LinkedListBounds();
	if (position == 0) return *_info;
	if (_next == NULL) throw LinkedListBounds();
	return _next->infoAt(position - 1);
}
// Inserts a deep-copy of 'newObj' into the head node, which now points to the to the beginning of original the LinkedList
template<typename DT> void LinkedList<DT>::add(DT& newObj)
{
	if (_info == NULL) { _info = new DT(newObj); }
	else
	{
		LinkedList<DT>* newList = new LinkedList<DT>(*_info, _next);	// node shares the same 'next' and contains a deep-copy of '*_info'
		if (newList == NULL) throw LinkedListMemory();
		*_info = newObj;
		_next = newList;
	}
}
//
template<typename DT> void LinkedList<DT>::insertAt(DT& newObj, int position)
{
	if (position == 0) add(newObj);
	else
	{
		if (_next == NULL)
		{
			_next = new LinkedList(newObj);
			if (_next == NULL) throw LinkedListMemory();
		}
		else
		{
			_next->insertAt(newObj, position - 1);
		}
	}
}
//
template<typename DT> DT LinkedList<DT>::remove()
{
	if (_info == NULL) throw LinkedListBounds();
	DT temp = *_info;								// temp is a Deep-Copy of _info; it is the return value
	delete _info;									// _info is deallocated
											// if the is not a '_next':
	if (_next == NULL) { _info = NULL; }			// a node cannot remove itself from the end of the LinkedList because it cannot erase its own address
													// from the previous node. Therefore if there is no '_next', this node will set '_info' to NULL
													// and other LinkedLists that point to this node will treat it as NULL
	else
	{										// if there is a '_next':
		LinkedList<DT>* oldNext = _next;	// oldNext is a deep-copy of _next
		_info = _next->_info;				// this node becomes essentially the same as last node
		_next = _next->_next;

		oldNext->_info = NULL;
		oldNext->_next = NULL;
		delete oldNext;
	}
	return temp;
}
template<typename DT> DT LinkedList<DT>::remove(const DT& key)
{

	if (isEmpty()) throw LinkedListNotFound();	// if Node does not have _Info
	if (key == *_info) remove();
	if (_next == NULL) throw LinkedListBounds();
	return _next->remove(key);
}
template<typename DT> DT LinkedList<DT>::removeAt(int position)
{
	if (_info == NULL) throw LinkedListBounds();
	if (position == 0) return remove();
	if (_next == NULL) throw LinkedListBounds();
	return _next->removeAt(position - 1);
}
template<typename DT> void LinkedList<DT>::operator=(const LinkedList<DT>& ll)
{
	if (this != &ll)
	{
		if (_info != NULL) delete _info;
		if (_next != NULL) delete _next;
		copy(ll);
	}
}
//
template<typename DT> AbstractLinkedList<DT>* LinkedList<DT>::next()
{
	return _next;
}

#endif // !__LINKEDLIST__H
