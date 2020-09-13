#ifndef __SELF_MODIFYING_BST__H
#define __SELF_MODIFYING_BST__H
#include "BinarySearchTree.h"
template<class DT>
class SelfModifyingBST : public BinarySearchTree<DT>
{
public:

//protected:
	BinarySearchTree<DT>* makeSubtree();
	virtual void zig();
	virtual void zag();
	virtual void zigzag();
	virtual void zagzig();
	virtual void zigzig();
	virtual void zagzag();
//public:
	SelfModifyingBST();
	SelfModifyingBST(const DT& data);
	virtual ~SelfModifyingBST();
};
template<class DT> SelfModifyingBST<DT>::SelfModifyingBST() 
	: BinarySearchTree<DT>() {};
template<class DT> SelfModifyingBST<DT>::SelfModifyingBST(const DT& data)
	: BinarySearchTree<DT>(data) {};
template<class DT> SelfModifyingBST<DT>::~SelfModifyingBST() {};
template<class DT> BinarySearchTree<DT>* SelfModifyingBST<DT>::makeSubtree()
{
	BinarySearchTree<DT>* sub = new SelfModifyingBST<DT>(); // override virtual BST methods
	((SelfModifyingBST<DT>*) sub)->_subtree = true;
	return sub;
}
template<class DT> void SelfModifyingBST<DT>::zig()
{
	if (BinarySearchTree<DT>::isEmpty()) return;
	if (BinarySearchTree<DT>::_LC->BinarySearchTree<DT>::isEmpty()) return;
	SelfModifyingBST<DT>* leftchild = (SelfModifyingBST<DT>*) BinarySearchTree<DT>::_LC;
	BinarySearchTree<DT>::_LC = leftchild->BinarySearchTree<DT>::_LC;
	leftchild->BinarySearchTree<DT>::_LC = leftchild->BinarySearchTree<DT>::_RC;
	leftchild->BinarySearchTree<DT>::_RC = BinarySearchTree<DT>::_RC;
	BinarySearchTree<DT>::_RC = leftchild;
	std::swap(leftchild->BinarySearchTree<DT>::_info, BinarySearchTree<DT>::_info);
}
template<class DT> void SelfModifyingBST<DT>::zag()
{
	if (BinarySearchTree<DT>::isEmpty()) return;
	if (BinarySearchTree<DT>::_RC->BinarySearchTree<DT>::isEmpty()) return;
	SelfModifyingBST<DT>* rightchild = (SelfModifyingBST<DT>*) BinarySearchTree<DT>::_RC;
	BinarySearchTree<DT>::_RC = rightchild->BinarySearchTree<DT>::_RC;
	rightchild->BinarySearchTree<DT>::_RC = rightchild->BinarySearchTree<DT>::_LC;
	rightchild->BinarySearchTree<DT>::_LC = BinarySearchTree<DT>::_LC;
	BinarySearchTree<DT>::_LC = rightchild;
	std::swap(rightchild->BinarySearchTree<DT>::_info, BinarySearchTree<DT>::_info);
}
template<class DT> void SelfModifyingBST<DT>::zigzig() { zig(); zig(); }
template<class DT> void SelfModifyingBST<DT>::zagzag() { zag(); zag(); }
template<class DT> void SelfModifyingBST<DT>::zigzag() 
{ 
	if (BinarySearchTree<DT>::isEmpty()) return;
	((SelfModifyingBST<DT>*) BinarySearchTree<DT>::_LC)->zag();
	zig();
}
template<class DT> void SelfModifyingBST<DT>::zagzig()
{
	if (BinarySearchTree<DT>::isEmpty()) return;
	((SelfModifyingBST<DT>*) BinarySearchTree<DT>::_RC)->zig();
	zag();
}
#endif