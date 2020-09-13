#ifndef __ABSTRACT_BINARY_SEARCH_TREE__H
#define __ABSTRACT_BINARY_SEARCH_TREE__H
#include <iostream>
#include "AbstractBinaryTreeAccess.h"

class BinarySearchTreeChangedSubtree : public BinaryTreeException {};
class BinarySearchTreeNotFound : public BinaryTreeException {};


template<class DT>
class AbstractBinarySearchTree : public AbstractBinaryTreeAccess<DT>
{
public:
	virtual ~AbstractBinarySearchTree() {};
	// returns true if the tree contains the node matching 'node'
	virtual bool contains(const DT& node) = NULL;
	// outputs all the nodes within the range bounded by 'lo' and 'hi' (inclusive)
	virtual void rangeSearch(const DT& lo, const DT& hi) = NULL;
	// returns the node matching 'node'
	virtual DT find(const DT& node) = NULL;
	// inserts a new node containing 'data' while maintaining binary search tree properies
	virtual void insert(const DT& data) = NULL;
	// removes the node containing 'data' while maintaining binary search tree properies
	virtual void remove(const DT& data) = NULL;
};
#endif __ABSTRACT_BINARY_TREE__H