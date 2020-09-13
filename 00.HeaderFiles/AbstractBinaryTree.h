#ifndef __ABSTRACT_BINARY_TREE__H
#define __ABSTRACT_BINARY_TREE__H
#include <iostream>
#include "AbstractBinaryTreeAccess.h"

template<class DT>
class AbstractBinaryTree : public AbstractBinaryTreeAccess<DT>
{
public:
	virtual ~AbstractBinaryTree() {};
	// sets the root to a copy of this 'data'
	virtual void setRoot(const DT& data) = 0;
	// sets the left subtree pointed by 'newLeft'; returns pointer to the former left subtree
	virtual AbstractBinaryTree<DT>* setLeft(AbstractBinaryTree<DT>* newLeft) = 0;
	// sets the left subtree pointed by 'newRight'; returns pointer to the former right subtree
	virtual AbstractBinaryTree<DT>* setRight(AbstractBinaryTree<DT>* newRight) = 0;
};
#endif __ABSTRACT_BINARY_TREE__H

