#ifndef __ABSTRACT_BINARY_TREE_ACCESS__H
#define __ABSTRACT_BINARY_TREE_ACCESS__H
#include <iostream>
#include <exception>
#include "Enumeration.h"
#include "StackLinked.h"

class BinaryTreeException : public std::exception {};
class BinaryTreeMemory : public BinaryTreeException {};
class BinaryTreeEmptyTree : public BinaryTreeException {};
class BinaryTreeGaveSubtreeToEmptyTree : public BinaryTreeException {};

int max(int l, int r) { return (l > r) ? l : r; }

template<class DT>
class AbstractBinaryTreeAccess
{
	friend std::ostream& operator<< (std::ostream& s, AbstractBinaryTreeAccess<DT>& tree)
	{
		tree.display(s);
		return s;
	}
public:
	
	virtual ~AbstractBinaryTreeAccess() {};
	// returns data from the root
	virtual DT& root() = 0;
	// returns true if the tree is empty
	virtual bool isEmpty() = 0;
	// returns the height (or depth) of the tree
	virtual int height() = 0;
	// returns the size of the tree
	virtual int size() = 0;
	// returns pointer to the left subtree
	virtual AbstractBinaryTreeAccess<DT>* left() = 0;
	// returns pointer to the right subtree
	virtual AbstractBinaryTreeAccess<DT>* right() = 0;

	// returns an inorder enumeration of the data from all nodes contained in the tree
	virtual Enumeration<DT>* inOrderEnumerator();
	// returns an postorder enumeration of the data from all nodes contained in the tree
	virtual Enumeration<DT>* postOrderEnumerator();
	// returns an preorder enumeration of the data from all nodes contained in the tree
	virtual Enumeration<DT>* preOrderEnumerator();
	// display tree structure
	virtual void display(std::ostream& os);
	virtual void printTree(std::ostream& os, int level);
};


template<class DT>
class PreOrderEnumerator : public Enumeration<DT>
{
protected:
	AbstractBinaryTreeAccess<DT>* _tree;
	StackLinked<AbstractBinaryTreeAccess<DT>*>* _stack;
public:
	PreOrderEnumerator(AbstractBinaryTreeAccess<DT>* tree);
	~PreOrderEnumerator();
	bool hasMoreElements();
	DT& nextElement();

};
template<class DT> PreOrderEnumerator<DT>::PreOrderEnumerator(AbstractBinaryTreeAccess<DT>* tree)
{
	_tree = tree;
	_stack = new StackLinked<AbstractBinaryTreeAccess<DT>*>();
	if ((_tree != NULL) && (!_tree->isEmpty()))
		_stack->push(_tree);
}
template<class DT> PreOrderEnumerator<DT>::~PreOrderEnumerator()
{
	if (_stack != NULL)
		delete _stack;
	_stack = NULL;
}
template<class DT> bool PreOrderEnumerator<DT>::hasMoreElements()
{
	return (!_stack->isEmpty());
}
template<class DT> DT& PreOrderEnumerator<DT>::nextElement()
{
	if (_stack->isEmpty()) throw BinaryTreeEmptyTree();
	AbstractBinaryTreeAccess<DT>* tree = _stack->pop();
	if (!tree->right()->isEmpty())
	{
		_stack->push(tree->right());
	}
	if (!tree->left()->isEmpty())
	{
		_stack->push(tree->left());
	}
	return tree->root();
}

template<class DT>
class InOrderEnumerator : public Enumeration<DT>
{
protected:
	AbstractBinaryTreeAccess<DT>* _tree;
	StackLinked<AbstractBinaryTreeAccess<DT>*>* _stack;
	void pushToBtmLeft(AbstractBinaryTreeAccess<DT>* tree);
public:
	InOrderEnumerator(AbstractBinaryTreeAccess<DT>* tree);
	~InOrderEnumerator();
	bool hasMoreElements();
	DT& nextElement();

};
template<class DT> InOrderEnumerator<DT>::InOrderEnumerator(AbstractBinaryTreeAccess<DT>* tree)
{
	_tree = tree;
	_stack = new StackLinked<AbstractBinaryTreeAccess<DT>*>();
	if (_tree != NULL)
		pushToBtmLeft(_tree);
}
template<class DT> InOrderEnumerator<DT>::~InOrderEnumerator()
{
	if (_stack != NULL)
	delete _stack;
	_stack = NULL;
}
template<class DT> void InOrderEnumerator<DT>::pushToBtmLeft(AbstractBinaryTreeAccess<DT>* tree)
{
	do
	{
		if (tree->isEmpty()) return;
		_stack->push(tree);
		tree = tree->left();
	} while (true);
}
template<class DT> bool InOrderEnumerator<DT>::hasMoreElements()
{
	return (!_stack->isEmpty());
}
template<class DT> DT& InOrderEnumerator<DT>::nextElement()
{
	if (_stack->isEmpty()) throw BinaryTreeEmptyTree();
	AbstractBinaryTreeAccess<DT>* tree = _stack->pop();
	pushToBtmLeft(tree->right());
	return tree->root();
}

template<class DT>
class PostOrderEnumerator : public Enumeration<DT>
{
protected:
	AbstractBinaryTreeAccess<DT>* _tree;
	StackLinked<AbstractBinaryTreeAccess<DT>*>* _stack;
	void pushToBtm(AbstractBinaryTreeAccess<DT>* tree);
public:
	PostOrderEnumerator(AbstractBinaryTreeAccess<DT>* tree);
	~PostOrderEnumerator();
	bool hasMoreElements();
	DT& nextElement();

};
template<class DT> PostOrderEnumerator<DT>::PostOrderEnumerator(AbstractBinaryTreeAccess<DT>* tree)
{
	_tree = tree;
	_stack = new StackLinked<AbstractBinaryTreeAccess<DT>*>();
	if (_tree != NULL)
		pushToBtm(_tree);
}
template<class DT> PostOrderEnumerator<DT>::~PostOrderEnumerator()
{
	if (_stack != NULL)
		delete _stack;
	_stack = NULL;
}
template<class DT> void PostOrderEnumerator<DT>::pushToBtm(AbstractBinaryTreeAccess<DT>* tree)
{
	if (tree->isEmpty()) return;
	do
	{
		_stack->push(tree);
		if (!tree->left()->isEmpty()) tree = tree->left();
		else if (!tree->right()->isEmpty()) tree = tree->right();
		else return;
	} while (true);
}
template<class DT> bool PostOrderEnumerator<DT>::hasMoreElements()
{
	return (!_stack->isEmpty());
}
template<class DT> DT& PostOrderEnumerator<DT>::nextElement()
{
	if (_stack->isEmpty()) throw BinaryTreeEmptyTree();
	AbstractBinaryTreeAccess<DT>* tree = _stack->pop();
	if (!_stack->isEmpty())
	{
		AbstractBinaryTreeAccess<DT>* parent = _stack->peek();
		if (parent != NULL)
		{
			if (parent->left() == tree)
			{
				pushToBtm(parent->right());
			}
		}
	}
	return tree->root();
}


template<class DT> Enumeration<DT>* AbstractBinaryTreeAccess<DT>::preOrderEnumerator()
{
	return new PreOrderEnumerator<DT>(this);
}
template<class DT> Enumeration<DT>* AbstractBinaryTreeAccess<DT>::inOrderEnumerator()
{
	return new InOrderEnumerator<DT>(this);
}
template<class DT> Enumeration<DT>* AbstractBinaryTreeAccess<DT>::postOrderEnumerator()
{
	return new PostOrderEnumerator<DT>(this);
}

template<class DT> void AbstractBinaryTreeAccess<DT>::display(std::ostream& s)
{
	bool first = true;
	Enumeration<DT>* e = new InOrderEnumerator<DT>(this);
	s << "<";
	while (e->hasMoreElements())
	{
		if (!first) s << ",";
		first = false;
		s << e->nextElement();
	}
	s << ">";
	delete e;
}
template<class DT> void AbstractBinaryTreeAccess<DT>::printTree(std::ostream& s, int level)
{
	if (isEmpty()) return;
	right()->printTree(s, level + 1);
	for (int i = 0; i < level; i++) s << " ";
	s << "+--" << root() << std::endl;
	left()->printTree(s, level + 1);
}

#endif //__ABSTRACT_BINARY_TREE__H

