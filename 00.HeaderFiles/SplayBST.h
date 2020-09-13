#if 0
#include "SelfModifyingBST.h"
template<class DT>
class SplayBST : SelfModifyingBST<DT>
{
protected:
	virtual BinarySearchTree<DT>* makeSubtree();
public:
	SplayBST();
	SplayBST(const DT& data);
	~SplayBST();
};
template<class DT> SplayBST<DT>::SplayBST() : SelfModifyingBST() {};
template<class DT> SplayBST<DT>::SplayBST(const DT& data) : SelfModifyingBST(data) {};
template<class DT> SplayBST<DT>::~SplayBST() {};
template<class DT> BinarySearchTree<DT>* SplayBST<DT>::makeSubtree()
{
	SplayBST<DT>* bst = new SplayBST<DT>();
	bst->_subtree = true;
	return bst;
}
#endif