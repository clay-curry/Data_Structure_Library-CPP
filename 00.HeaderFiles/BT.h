
#ifndef __BINARY_TREE__H
#include "AbstractBinaryTree.h"
template <class DT>
class BinaryTree : public AbstractBinaryTree<DT>
{
protected:
	DT* _rootData;
	AbstractBinaryTree<DT>* _left;
	AbstractBinaryTree<DT>* _right;
	int max(int, int);
public:
	BinaryTree();
	BinaryTree(DT& root, AbstractBinaryTree<DT>* left, AbstractBinaryTree<DT>* right);
	bool isEmpty();
	~BinaryTree();
	int height();
	int size();
	DT& getRoot();
	void setRoot(DT& data);
	AbstractBinaryTree<DT>* left();
	AbstractBinaryTree<DT>* right();
	AbstractBinaryTree<DT>* setLeft(AbstractBinaryTree<DT>* newLeft);
	AbstractBinaryTree<DT>* setRight(AbstractBinaryTree<DT>* newRight);
	void makeEmpty();
};
template<class DT>
void BinaryTree<DT>::makeEmpty()
{
	if (_rootData != NULL) delete _rootData;
	_rootData = NULL;
	if (_left != NULL) delete _left;
	_left = NULL;
	if (_right != NULL) delete _right;
	_right = NULL;
}
template<class DT>
int BinaryTree<DT>::max(int l, int r)
{
	return (l > r) ? l : r;
}
template<class DT>
BinaryTree<DT>::BinaryTree()
{
	_rootData = NULL;
	_left = NULL;
	_right = NULL;
}
template<class DT>
BinaryTree<DT>::BinaryTree(DT& root, AbstractBinaryTree<DT>* left, AbstractBinaryTree<DT>* right)
{
	_rootData = NULL;
	_rootData = new DT(root);
	if (_rootData == NULL) throw BinaryTreeMemory();
	
	if (left == NULL)
		_left = new BinaryTree<DT>();
	else 
		_left = left;
	
	if (right == NULL)
		_right = new BinaryTree<DT>();
	else
		_right = right;
}
template<class DT>
BinaryTree<DT>::~BinaryTree()
{
	makeEmpty();
};
template<class DT>
bool BinaryTree<DT>::isEmpty()
{
	return (_rootData == NULL);
}
template<class DT>
int BinaryTree<DT>::height()
{	
	return (isEmpty()) ? 0 : 1 + max(_left->height(), _right->height());
}
template<class DT>
int BinaryTree<DT>::size()
{
	return (isEmpty()) ? 0 : 1 + _left->size() + _right->size();
}
template<class DT>
DT& BinaryTree<DT>::getRoot()
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_rootData;
}
template<class DT>
void BinaryTree<DT>::setRoot(DT& data)
{
	if (_rootData != NULL)
		delete _rootData;
	else
	{
		_left = new BinaryTree<DT>();
		_right = new BinaryTree<DT>();
	}
}
template<class DT>
AbstractBinaryTree<DT>* BinaryTree<DT>::left()
{
	return _left;
}
template<class DT>
AbstractBinaryTree<DT>* BinaryTree<DT>::right()
{
	return _right;
}
template<class DT>
AbstractBinaryTree<DT>* BinaryTree<DT>::setLeft(AbstractBinaryTree<DT>* newLeft)
{
	AbstractBinaryTree<DT>* temp = _left;
	if (isEmpty()) throw BinaryTreeGaveSubtreeToEmptyTree();
	if (newLeft == NULL)
		_left = new BinaryTree<DT>();
	else
		_left = newLeft;
	return temp;
}
template<class DT>
AbstractBinaryTree<DT>* BinaryTree<DT>::setRight(AbstractBinaryTree<DT>* newRight)
{
	AbstractBinaryTree<DT>* temp = _right;
	if (isEmpty()) throw BinaryTreeGaveSubtreeToEmptyTree();
	if (newRight == NULL)
		_right = new BinaryTree<DT>();
	else
		_right = newRight;
	return temp;
}
#endif // !__BINARY_TREE__H
