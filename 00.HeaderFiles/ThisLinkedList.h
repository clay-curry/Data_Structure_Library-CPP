#ifndef __LINKEDLIST__H
#define __LINKEDLIST__H
#include "LinkedList.h"
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
template<typename DT> LinkedList<DT>::LinkedList() : _info(NULL), _next(NULL) {};
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
template<typename DT> int LinkedList<DT>::size()
{
	if (_next == NULL)	return (_info == NULL) ? 0 : 1;
	else return 1 + _next->size();
}
template<typename DT> DT& LinkedList<DT>::find(DT& key)
{
	if (isEmpty()) throw LinkedListNotFound();	// if Node does not have _Info
	if (key == *_info) return *_info;
	if (_next == NULL) throw LinkedListBounds();
	return _next->find(key);
}
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
template<typename DT> AbstractLinkedList<DT>* LinkedList<DT>::next()
{
	return _next;
}
#endif // !__LINKEDLIST__H