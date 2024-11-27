#ifndef TREENODE
#define TREENODE

//-----------------------------------------------------------------------------------------------------------------
// TreeNode struct
//-----------------------------------------------------------------------------------------------------------------
template <typename T>
struct A_TreeNode {
	T data;					 	  // node's payload. Custom instances of T should have comparison operators defined
	A_TreeNode<T>* left;															  	   // pointer to left child
	A_TreeNode<T>* right;															  	  // pointer to right child
	A_TreeNode<T>* parent;
	int balance_factor;
	A_TreeNode(T val) : data(val), left(nullptr), right(nullptr), balance_factor(0) {}
};

#endif