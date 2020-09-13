
#ifndef __BINARY_SEARCH_TREE__H
#define __BINARY_SEARCH_TREE__H
#include "AbstractBinarySearchTree.h"

template<class DT> class BinarySearchTree : public AbstractBinarySearchTree<DT>
{
protected:

	DT* _info;
	BinarySearchTree<DT>* _LC;
	BinarySearchTree<DT>* _RC;
	bool _subtree;
	virtual BinarySearchTree<DT>* makeSubtree(); // virtual so that types can be overridden by
	virtual void copyTree(BinarySearchTree<DT>* bst);
	virtual void _makeEmpty();
	virtual void makeEmpty();
	virtual void makeNull();
	BinarySearchTree<DT>* _find(const DT& data);

	// returns pointer to the left subtree
	virtual AbstractBinaryTreeAccess<DT>* left();
	// returns pointer to the right subtree
	virtual AbstractBinaryTreeAccess<DT>* right();
public:
	BinarySearchTree();
	BinarySearchTree(const DT& data);
	virtual ~BinarySearchTree();
	// returns data from the root
	virtual DT& root();
	// indicates whether this node is a subtree of another tree
	virtual bool subtree();
	// returns true if the tree is empty
	virtual bool isEmpty();
	// returns the height (or depth) of the tree
	virtual int height();
	// returns the size of the tree
	virtual int size();
	// returns true if the tree contains the node matching 'node'
	virtual bool contains(const DT& node);
	// outputs all the nodes within the range bounded by 'lo' and 'hi' (inclusive)
	virtual void rangeSearch(const DT& lo, const DT& hi);
	// returns the node matching 'node'
	virtual DT find(const DT& node);
	// inserts a new node containing 'data' while maintaining binary search tree properies
	virtual void insert(const DT& data);
	// removes the node containing 'data' while maintaining binary search tree properies
	virtual void remove(const DT& data);

};
template<class DT> BinarySearchTree<DT>::BinarySearchTree() : _info(NULL), _LC(NULL), _RC(NULL), _subtree(false) {};
template<class DT> BinarySearchTree<DT>::BinarySearchTree(const DT& data) : _info(new DT(data)), _subtree(false)
{
	if (_info == NULL) throw BinaryTreeMemory();
	_LC = makeSubtree();
	_RC = makeSubtree();
};
template<class DT> BinarySearchTree<DT>::~BinarySearchTree()
{
	if (_info != NULL) delete _info;
	_info = NULL;
	if (_LC != NULL) delete _LC;
	_LC = NULL;
	if (_RC != NULL) delete _RC;
	_RC = NULL;
}
template<class DT> BinarySearchTree<DT>* BinarySearchTree<DT>::makeSubtree()
{
	BinarySearchTree<DT>* bst = new BinarySearchTree<DT>();
	bst->_subtree = true;
	return bst;
}
template<class DT> void BinarySearchTree<DT>::copyTree(BinarySearchTree<DT>* bst)
{
	_info = bst->_info;
	if (_LC != NULL) _LC->makeEmpty();
	_LC = bst->_LC;
	if (_RC != NULL) _RC->makeEmpty();
	_RC = bst->_RC;
 }
template<class DT> void BinarySearchTree<DT>::_makeEmpty()
{
	if (_info != NULL) delete _info;
	_info = NULL;
	if (_LC != NULL) delete _LC;
	_LC = NULL;
	if (_RC != NULL) delete _RC;
	_RC = NULL;
}
template<class DT> void BinarySearchTree<DT>::makeEmpty()
{
	if (_subtree) throw BinarySearchTreeChangedSubtree();
	_makeEmpty();
}
template<class DT> void BinarySearchTree<DT>::makeNull()
{
	_info = NULL;
	_LC = NULL;
	_RC = NULL;
};
template<class DT> BinarySearchTree<DT>* BinarySearchTree<DT>::_find(const DT& data)
{
	BinarySearchTree<DT>* bst = this;
	while (true)
	{
		if (bst->isEmpty())
			return bst;
		if (*(bst->_info) < data)
			bst = bst->_RC;
		else if (*(bst->_info) > data)
			bst = bst->_LC;
		else
			return bst;
	}
}

template<class DT> AbstractBinaryTreeAccess<DT>* BinarySearchTree<DT>::left() { return _LC; }
template<class DT> AbstractBinaryTreeAccess<DT>* BinarySearchTree<DT>::right() { return _RC; }
template<class DT> DT& BinarySearchTree<DT>::root()
{
	if (_info == NULL) throw BinaryTreeEmptyTree();
	return *_info;
}
template<class DT> bool BinarySearchTree<DT>::subtree() { return _subtree; }

template<class DT> bool BinarySearchTree<DT>::isEmpty()
{
	return (_info == NULL);
}
template<class DT> int BinarySearchTree<DT>::height()
{
	if (_info == NULL) return 0;
	return 1 + max(_LC->height(), _RC->height());
}
template<class DT> int BinarySearchTree<DT>::size()
{
	if (_info == NULL) return 0;
	return 1 + _LC->size() + _RC->size();
}
template<class DT> bool BinarySearchTree<DT>::contains(const DT& data)
{
	BinarySearchTree<DT>* bst = _find(data);
	return !bst->isEmpty();
}
template<class DT> void BinarySearchTree<DT>::rangeSearch(const DT& lo, const DT& hi)
{
	if (isEmpty()) return;
	if (*_info >= lo)
	{
		_LC->rangeSearch(lo, hi);
		if (*_info <= hi)
			std::cout << *_info << " ";
	}
	if (*_info <= hi)
		_RC->rangeSearch(lo, hi);
}
template<class DT> DT BinarySearchTree<DT>::find(const DT& data)
{
	BinarySearchTree<DT>* bst = _find(data);
	if (bst->isEmpty()) throw BinarySearchTreeNotFound();
	return *(bst->_info);
}
template<class DT> void BinarySearchTree<DT>::insert(const DT& data)
{
	if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DT>* bst = _find(data);
	if (bst->isEmpty())
	{
		bst->_info = new DT(data);
		bst->_LC = makeSubtree();
		bst->_RC = makeSubtree();
	}
	else
	{
		delete bst->_info;
		bst->_info = new DT(data);
	}
}
template<class DT> void BinarySearchTree<DT>::remove(const DT& data)
{
	if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DT>* bst;
	BinarySearchTree<DT>* bst2;
	BinarySearchTree<DT>* bst3;

	bst = _find(data);
	if (bst->isEmpty()) throw BinarySearchTreeNotFound();

	if (bst->_LC->isEmpty())
	{
		delete bst->_LC;
		bst2 = bst->_RC;
		bst->copyTree(bst2);

		bst2->makeNull();
		delete bst2;
	}

	else if (bst->_RC->isEmpty())
	{
		delete bst->_RC;
		bst2 = bst->_LC;
		bst->copyTree(bst2);

		bst2->makeNull();
		delete bst2;
	}

	else
	{
		bst2 = bst->_RC;
		while (!bst2->_LC->isEmpty()) bst2 = bst2->_LC;
		bst->_info = bst2->_info;

		delete bst2->_LC;

		if (bst2->_RC->isEmpty())
		{
			delete bst2->_RC;
			bst2->makeNull();
		}
		else
		{
			bst3 = bst2->_RC;
			bst2->copyTree(bst2->_RC);
			bst3->makeNull();
			delete bst3;
		}
	}
}

#endif // __BINARY_SEARCH_TREE_H