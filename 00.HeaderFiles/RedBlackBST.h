#include "SelfModifyingBST.h"

const int RED = 0;
const int BLACK = 1;

template<class DT>
class RedBlackBST : public SelfModifyingBST<DT>
{
private:
	RedBlackBST<DT>* rbleft();
	RedBlackBST<DT>* rbright();
protected:
	int _color;
	BinarySearchTree<DT>* makeSubtree();
	virtual void _makeEmpty();
	virtual void makeEmpty();
	virtual void makeNull();

	void fixred();
	void fixblackleft(bool&);
	void fixblackright(bool&);

	virtual void _insert(const DT& data);
	virtual void _remove(bool& blackCondition, const DT& data);
public:
	RedBlackBST();
	RedBlackBST(const DT& data);
	~RedBlackBST();

	virtual void insert(const DT& data);
	virtual void remove(const DT& data);

	int color();
	virtual void printTree(std::ostream&, int level);
};








template<class DT> RedBlackBST<DT>::RedBlackBST() : SelfModifyingBST<DT>()
{
	_color = BLACK;
};
template<class DT> RedBlackBST<DT>::RedBlackBST(const DT& data) : SelfModifyingBST<DT>(data) 
{
	_color = RED;
};
template<class DT> RedBlackBST<DT>::~RedBlackBST() {};
template<class DT> RedBlackBST<DT>* RedBlackBST<DT>::rbleft()
{
	return ((RedBlackBST<DT>*)(BinarySearchTree<DT>::left()));
}
template<class DT> RedBlackBST<DT>* RedBlackBST<DT>::rbright()
{
	return ((RedBlackBST<DT>*)(BinarySearchTree<DT>::right()));
}
template<class DT> BinarySearchTree<DT>* RedBlackBST<DT>::makeSubtree()
{
	BinarySearchTree<DT>* sub = new RedBlackBST<DT>();
	((RedBlackBST<DT>*) sub)->_subtree = true;
	return sub;
}
template<class DT> void RedBlackBST<DT>::makeEmpty()
{
	if (BinarySearchTree<DT>::_subtree) throw BinarySearchTreeChangedSubtree();
	_makeEmpty();
}
template<class DT> void RedBlackBST<DT>::_makeEmpty()
{
	BinarySearchTree<DT>::_makeEmpty();
	_color = BLACK;
}
template<class DT> void RedBlackBST<DT>::makeNull()
{
	BinarySearchTree<DT>::makeNull();
	_color = BLACK;
};
template<class DT> void RedBlackBST<DT>::fixred()
{
	if (BinarySearchTree<DT>::isEmpty()) return;

	RedBlackBST<DT>* lft = rbleft();	// to make semantics simple
	RedBlackBST<DT>* rgt = rbright();

	// first fix the root

	if (!BinarySearchTree<DT>::_subtree)	// recolors the root node to black if needed
		if (_color == RED)
			if ((lft->_color == RED) || (rgt->_color == RED))
				_color = BLACK;


	// now lets fix the subtree

	// if 'c' is the newly inserted node, let
	//	'p' : denote the red node pointing to 'c' (a.k.a. the parent)
	//	'g' : denote the black node pointing to 'p' (a.k.a. the grandparent)

	if (lft->_color == RED)
	{
		// left-left violation
		if (lft->rbleft()->_color == RED)
		{	// correct left-left violaiton
			if (rgt->_color == RED)
			{
				_color = RED;
				lft->_color = BLACK;
				rgt->_color = BLACK;
			}
			else
				SelfModifyingBST<DT>::zig();
		}

		// left-right violation
		else if (lft->rbright()->_color == RED)
		{	// correct left-right violation
			if (rgt->_color == RED)
			{
				_color = RED;
				lft->_color = BLACK;
				rgt->_color = BLACK;
			}
			else
				SelfModifyingBST<DT>::zigzag();
		}
		
	}
	if (rgt->_color == RED)
	{
		// right-right violation
		if (rgt->rbright()->_color == RED)
		{	// correct right-right violation
			if (lft->_color == RED)
			{
				_color = RED;
				lft->_color = BLACK;
				rgt->_color = BLACK;
			}
			else
				SelfModifyingBST<DT>::zag();
		}

		// right-left
		else if (rgt->rbleft()->_color == RED)
		{	// correct right-left violation
			if (lft->_color == RED)
			{
				_color = RED;
				lft->_color = BLACK;
				rgt->_color = BLACK;
			}
			else
				SelfModifyingBST<DT>::zagzig();
		}
	}
}
template<class DT> void RedBlackBST<DT>::fixblackleft(bool& blackCondition)
{
	if (blackCondition) return;
	if (rbleft()->_color == RED)
	{
		rbleft()->_color = BLACK;
		blackCondition = true;
		return;
	}

	if (_color == RED)
	{
		_color = BLACK;
		rbright()->_color = RED;

		if ((rbright()->rbleft()->_color == RED) && (rbright()->rbright()->_color == RED))
			SelfModifyingBST<DT>::zag();
		fixred();
		blackCondition = true;
		return;
	}
	if (rbright()->_color == BLACK)
	{
		rbright()->_color = RED;
		if ((rbright()->rbleft()->_color == RED) && (rbright()->rbright()->_color == RED))
			SelfModifyingBST<DT>::zag();

		fixred();
		
		if (_color == RED)
		{
			_color = BLACK;
			blackCondition = true;
		}
		return;
	}
	SelfModifyingBST<DT>::zag();
	rbleft()->fixblackleft(blackCondition);
}
template<class DT> void RedBlackBST<DT>::fixblackright(bool& blackCondition)
{
	if (blackCondition) return;
	if (rbright()->_color == RED)
	{
		rbright()->_color = BLACK;
		blackCondition = true;
		return;
	}

	if (_color == RED)
	{
		_color = BLACK;
		rbleft()->_color = RED;

		if ((rbleft()->rbright()->_color == RED) && (rbleft()->rbleft()->_color == RED))
			SelfModifyingBST<DT>::zig();
		fixred();
		blackCondition = true;
		return;
	}
	if (rbleft()->_color == BLACK)
	{
		rbleft()->_color = RED;
		if ((rbleft()->rbright()->_color == RED) && (rbleft()->rbleft()->_color == RED))
			SelfModifyingBST<DT>::zig();

		fixred();

		if (_color == RED)
		{
			_color = BLACK;
			blackCondition = true;
		}
		return;
	}
	SelfModifyingBST<DT>::zig();
	rbright()->fixblackright(blackCondition);
}


template<class DT> void RedBlackBST<DT>::insert(const DT& data)
{
	if (BinarySearchTree<DT>::_subtree) throw BinarySearchTreeChangedSubtree();
	_insert(data);
}
template<class DT> void RedBlackBST<DT>::_insert(const DT& data)
{
	if (BinarySearchTree<DT>::isEmpty())
	{
		BinarySearchTree<DT>::_info = new DT(data);
		_color = RED;
		BinarySearchTree<DT>::_LC = makeSubtree();
		BinarySearchTree<DT>::_RC = makeSubtree();
		return;
	}
	if ((*BinarySearchTree<DT>::_info) == data)
	{
		delete BinarySearchTree<DT>::_info;
		BinarySearchTree<DT>::_info = new DT(data);
		return;
	}
	if ((*BinarySearchTree<DT>::_info) > data)
		rbleft()->_insert(data);
	else
		rbright()->_insert(data);
}
template<class DT> void RedBlackBST<DT>::remove(const DT& data)
{
	bool blackCondition = true;
	if (BinarySearchTree<DT>::_subtree) throw BinarySearchTreeChangedSubtree();
	_remove(blackCondition, data);
}
template<class DT> void RedBlackBST<DT>::_remove(bool& blackCondition, const DT& data)
{
	if (BinarySearchTree<DT>::isEmpty()) throw BinarySearchTreeNotFound();
	
	if ((*BinarySearchTree<DT>::_info) > data)
	{
		rbleft()->_remove(blackCondition, data);
		fixblackleft(blackCondition);
	}
	else if ((*BinarySearchTree<DT>::_info) < data)
	{
		rbright()->_remove(blackCondition, data);
		fixblackright(blackCondition);
	}
	else
	{
		if ((BinarySearchTree<DT>::_LC->isEmpty()) && (BinarySearchTree<DT>::_RC->isEmpty()))
		{
			if (_color == BLACK)
				blackCondition = false;
			makeEmpty();
		}
		else if ((!BinarySearchTree<DT>::_LC->isEmpty()) && (BinarySearchTree<DT>::_RC->isEmpty()))
		{
			RedBlackBST<DT>* oldLeft = rbleft();
			delete BinarySearchTree<DT>::_RC;
			delete BinarySearchTree<DT>::_info;
			BinarySearchTree<DT>::copyTree(BinarySearchTree<DT>::_LC);
			oldLeft->makeNull();
			delete oldLeft;		
		}
		else if ((BinarySearchTree<DT>::_LC->isEmpty()) && (!BinarySearchTree<DT>::_RC->isEmpty()))
		{
			RedBlackBST<DT>* oldRight = rbright();
			delete BinarySearchTree<DT>::_LC;
			delete BinarySearchTree<DT>::_info;
			BinarySearchTree<DT>::copyTree(BinarySearchTree<DT>::_RC);
			oldRight->makeNull();
			delete oldRight;
		}
		else
		{
			RedBlackBST<DT>* succ = rbright();
			while (!(succ)->BinarySearchTree<DT>::_LC->isEmpty())
				succ = succ->rbleft();
			delete BinarySearchTree<DT>::_info;

			BinarySearchTree<DT>::_info = new DT(*(succ->BinarySearchTree<DT>::_info));
			rbright()->_remove(blackCondition, *(succ)->BinarySearchTree<DT>::_info);
			fixblackright(blackCondition);
		}
	}
}

template<class DT> int RedBlackBST<DT>::color() { return _color; }
template<class DT> void RedBlackBST<DT>::printTree(std::ostream& s, int level)
{
	if (BinarySearchTree<DT>::isEmpty()) return;
	rbright()->printTree(s, level + 1);
	for (int i = 0; i < level; i++) s << " ";
	s << "+--" << *BinarySearchTree<DT>::_info << std::endl;
	if (_color == RED) s << "(r)";
	if (_color == BLACK) s << "(b)";
	rbleft()->printTree(s, level + 1);
}
