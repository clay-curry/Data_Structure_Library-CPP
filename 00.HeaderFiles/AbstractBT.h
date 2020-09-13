#ifndef __ABSTRACT_BINARY_TREE__H
#define __ABSTRACT_BINARY_TREE__H
#include <iostream>
#include <exception>
class BinaryTreeException : public std::exception {};
class BinaryTreeMemory : public BinaryTreeException {};
class BinaryTreeEmptyTree : public BinaryTreeException {};
class BinaryTreeGaveSubtreeToEmptyTree : public BinaryTreeException {};

//template<class DT>
//class AbstractBinaryTree;
//template <class DT> 
//std::ostream& operator<< (std::ostream&, const AbstractBinaryTree<DT>&);

template<class DT>
class AbstractBinaryTree
{
	friend std::ostream& operator<< <DT> (std::ostream&, const AbstractBinaryTree<DT>&);
public:
	virtual ~AbstractBinaryTree();
	// returns true if the tree is empty
	virtual bool isEmpty() = 0;
	// returns the height (or depth) of the tree
	virtual int height() = 0;
	// returns data from the root
	virtual DT& root() = 0;
	// returns pointer to the left subtree
	virtual AbstractBinaryTree<DT>* left() = 0;
	// returns pointer to the right subtree
	virtual AbstractBinaryTree<DT>* right() = 0;
	// sets the root to a copy of this 'data'
	virtual void setRoot(DT& data) = 0;
	// sets the left subtree pointed by 'newLeft'; returns pointer to the former left subtree
	virtual AbstractBinaryTree<DT>* setLeft(AbstractBinaryTree<DT>* newLeft) = 0;
	// sets the left subtree pointed by 'newRight'; returns pointer to the former right subtree
	virtual AbstractBinaryTree<DT>* setRight(AbstractBinaryTree<DT>* newRight) = 0;
	// empties tree
	virtual void makeEmpty() = 0;
	// returns an inorder enumeration of the data from all nodes contained in the tree
	virtual Enumeration<DT>* inOrderEnumerator() = 0;
	// returns an postorder enumeration of the data from all nodes contained in the tree
	virtual Enumeration<DT>* postOrderEnumerator() = 0;
	// returns an preorder enumeration of the data from all nodes contained in the tree
	virtual Enumeration<DT>* preOrderEnumerator() = 0;
	// display tree structure
	virtual void display(std::ostream& os) = 0;

};
#endif __ABSTRACT_BINARY_TREE__H

