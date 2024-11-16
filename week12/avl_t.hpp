#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <vector>
#include <stack>
#include "bst_helpers.hpp/bst_data.hpp"
#include "bst_helpers.hpp/initialize_vec.hpp"
#include <cmath>

//-----------------------------------------------------------------------------------------------------------------	
// TreeNode class
//-----------------------------------------------------------------------------------------------------------------	
template <typename T>
class A_TreeNode {
	public:
		T data;					  // node's payload. Custom instances of T should have comparison operators defined
		A_TreeNode<T>* left;															   // pointer to left child
		A_TreeNode<T>* right;															  // pointer to right child
		A_TreeNode<T>* parent;
		int balance_factor; 
		A_TreeNode(T val) : data(val), left(nullptr), right(nullptr), balance_factor(0) {}
};
//-----------------------------------------------------------------------------------------------------------------	
// BinarySearchTree class
//-----------------------------------------------------------------------------------------------------------------	
template <typename T>
class AVL_BinarySearchTree {
	public:
	//-------------------------------------------------------------------------------------------------------------
	// Class vars
	//-------------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* root;																// pointer to root node
		int nodeCount = 0;															 // number of nodes in the tree
		searchData sd;														   // track data related to BST methods
		int max_height = 0 ; 													   // track the height of this tree	
	//-------------------------------------------------------------------------------------------------------------
		//---------------------------------------------------------------------------------------------------------
		// ROTATE RIGHT - https://www.youtube.com/watch?v=otiDcwZbCo4 // runestone's implementation did not work
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* rotateRight(A_TreeNode<T>* rotRoot) {
			A_TreeNode<T>* newRoot = rotRoot->left;
			A_TreeNode<T>* T2 = newRoot->right;    // T2 = r_child of x before rotation, becomes l_child of rotRoot
			// Perform rotation
			newRoot->right = rotRoot;
			rotRoot->left = T2;
			// Update parents
			if (T2) T2->parent = rotRoot;
			newRoot->parent = rotRoot->parent;
			rotRoot->parent = newRoot;
			// Update balance factors
			rotRoot->balance_factor = node_balance_factor(rotRoot);
			newRoot->balance_factor = node_balance_factor(newRoot);
			return newRoot; // New root after rotation
		}
		//---------------------------------------------------------------------------------------------------------
		// ROTATE LEFT
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* rotateLeft(A_TreeNode<T>* x) {
			A_TreeNode<T>*  y = x->right;
			A_TreeNode<T>*  T2 = y->left;
			// Perform rotation
			y->left = x;
			x->right = T2;
			// Update parents
			if (T2) T2->parent = x;
			y->parent = x->parent;
			x->parent = y;
			// Update balance factors
			x->balance_factor = node_balance_factor(x);
			y->balance_factor = node_balance_factor(y);
			return y; // New root after rotation
		}
		//---------------------------------------------------------------------------------------------------------
		// BALANCE
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>*  balance(A_TreeNode<T>*  node) {
			if (node->balance_factor > 1 && node->left->balance_factor >= 0) {
				return rotateRight(node);														  // Left Left Case
			}
			if (node->balance_factor > 1 && node->left->balance_factor < 0) {
				node->left = rotateLeft(node->left);
				return rotateRight(node);													     // Left Right Case
			}
			if (node->balance_factor < -1 && node->right->balance_factor <= 0) {
				return rotateLeft(node);													    // Right Right Case
			}
			if (node->balance_factor < -1 && node->right->balance_factor > 0) {
				node->right = rotateRight(node->right);											 // Right Left Case
				return rotateLeft(node);
			}
			return node;
		}
		//---------------------------------------------------------------------------------------------------------
		// INSERT
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* insert(A_TreeNode<T>* node, T key) {
			sd.inserts ++ ;
			if (node == nullptr) return new A_TreeNode(key);
			if (key < node->data) {
				node->left = insert(node->left, key);
				node->left->parent = node;
			} else if (key > node->data) {
				node->right = insert(node->right, key);
				node->right->parent = node;
			} else {
				return node; 														 // No duplicate values allowed
			}
			node->balance_factor = node_balance_factor(node);		 // Update balance factor of this ancestor node
			return balance(node);									// Balance the node if it has become unbalanced
		}
		//---------------------------------------------------------------------------------------------------------
		// DELETE - https://www.youtube.com/watch?v=3UivJWAFaI4
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>*  deleteNode(A_TreeNode<T>*  root, T key) {
			if (root == nullptr) return root;
			if (key < root->data) {
				root->left = deleteNode(root->left, key);
			} else if (key > root->data) {
				root->right = deleteNode(root->right, key);
			} else {
				if (root->left == nullptr || root->right == nullptr) {
					A_TreeNode<T>* temp = root->left ? root->left : root->right;		  // Node with the key found
					if (temp == nullptr) {
						temp = root;
						root = nullptr;
					} else {
						*root = *temp;
					}
					delete temp;
				} else {
					A_TreeNode<T>* temp = min(root->right);
					root->data = temp->data;
					root->right = deleteNode(root->right, temp->data);
				}
			}
			if (root == nullptr) return root;
			// Update balance factor and balance the node
			root->balance_factor = node_balance_factor(root);
			return balance(root);
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the MIN value in a subtree
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* min(A_TreeNode<T>* node) {
			while (node->left != nullptr)											// while node has a left child
				node = node->left;																		// go left
			return node;																			// return node
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the MAX value in a subtree
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* max(A_TreeNode<T>* node) {
			while (node->right != nullptr)											// while node has a right child
				node = node->right;																		// go right
			return node;
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the inorder successor of a node
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* remove(A_TreeNode<T>* node, T key) {						      // args: start, key to remove
			if (node == nullptr)		return node;							       // key was not found in tree
			if (key < node->data)		node->left  = remove(node->left, key);   // key < than node's data, go left
			else if (key > node->data)	node->right = remove(node->right, key); // key > than node's data, go right
			else {																	   // found the node, remove it
				if (node->left == nullptr) {								   // node has one child (right child))
					A_TreeNode<T>* temp = node->right;										   // store right child
					nodeCount -- ;															// decrement node count
					delete node;																	 // delete node
					return temp;															  // return right child
				} else if (node->right == nullptr) {							 // node has one child (left child)
					A_TreeNode<T>* temp = node->left;											// store left child
					delete node;																	 // delete node
					nodeCount -- ;															// decrement node count
					return temp;															   // return left child
				}													// node has two children, get inorder successor
				A_TreeNode<T>* temp	= min(node->right);								   // smallest in right subtree
				node->data			= temp->data;	   // copy inorder successor's content to this node (to delete)
				node->right			= remove(node->right, temp->data);					// delete inorder successor
			}
			return node;													  // return node (potentially modified)
		}
		//----------------------------------------------------------------------------------------------------------
		// IN ORDER TRAVERSAL TO FLATTEN THIS TREE 
		//----------------------------------------------------------------------------------------------------------
		// in order to preserver sorted arrangement
		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		//----------------------------------------------------------------------------------------------------------
		void inOrderTraversal(A_TreeNode<T>* node, vector<T>& v) {
			if (node != nullptr) {															  // if node is not null
				inOrderTraversal(node->left, v);											// traverse left subtree
				v.emplace_back(node->data);												   // place data into vector
				inOrderTraversal(node->right, v);										   // traverse right subtree
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// public in-order traversal
		//----------------------------------------------------------------------------------------------------------
		void in_order(vector<T>& v) {
			inOrderTraversal(root, v);												// call private recursive helper
			std::cout << std::endl;																		 // new line
		}
		//----------------------------------------------------------------------------------------------------------
		// IN ORDER TRAVERSAL TO COUNT THIS TREE 
		//----------------------------------------------------------------------------------------------------------
		// in order to preserver sorted arrangement
		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		//----------------------------------------------------------------------------------------------------------
		void inOrderTraversal_count(A_TreeNode<T>* node, int& count) {
			if (node != nullptr) {															  // if node is not null
				inOrderTraversal_count(node->left, count);									// traverse left subtree
				count ++ ;
				inOrderTraversal_count(node->right, count);								   // traverse right subtree
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// public in-order count traversal, no arguments
		//----------------------------------------------------------------------------------------------------------
		void in_order_count(int& count) {
			inOrderTraversal_count(root, count);									// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// IN ORDER TRAVERSAL TO FIND KTH SMALLEST INT
		// in order traversal to follow ints in ascending order 
		// O(n) time for this since visiting nodes until potentially every node visited
		//----------------------------------------------------------------------------------------------------------
		void inOrderFindKthSmallest(A_TreeNode<T>* node, int& nth_val, int& tracker, int& result) {
			if (node != nullptr) {															  // if node is not null
				inOrderFindKthSmallest(node->left, nth_val, tracker, result);				// traverse left subtree
				tracker ++ ;												     // increment how many nodes visited
				if (tracker == nth_val){												   // once visits == kth_val
					result = node->data;											// return the value at this node
				}
				inOrderFindKthSmallest(node->right, nth_val, tracker, result);		       // traverse right subtree
			}
		}
        //----------------------------------------------------------------------------------------------------------
		// PRE ORDER TRAVERSAL TO CHECK VALIDITY OF TREE
		// pre order since this will stop at a root of a subtree, then can compare children to root
		// O(n) time for this since visit every node
		//----------------------------------------------------------------------------------------------------------
		void preOrderTraversal(A_TreeNode<T>* node, bool& valid) {
			if (node != nullptr) {															  // if node is not null
				if (node->left == nullptr && node->right == nullptr){
					return; 													 // if no children, nothing to check
				}
				else if (node->left != nullptr && node->right == nullptr){ 					 // if just a left child
					if (node->left->data > this->root->data){ 							// if left greater than root
						valid = false; 
						return;
					};
				}
				else if (node->right != nullptr && node->left == nullptr){ 					// if just a right child
					if (node->right->data < this->root->data){  // if left > than root or right < than root, invalid
						valid = false;
						return;
					};
				} else { 																 // if both children present
					if (node->left->data > this->root->data || node->right->data <  this->root->data)
					valid = false;
					return;
				}
				preOrderTraversal(node->left, valid);										// traverse left subtree
				preOrderTraversal(node->right, valid);									   // traverse right subtree
			}
		}
        //----------------------------------------------------------------------------------------------------------
		// PRE ORDER TRAVERSAL TO SET BALANCE OF EACH NODE -- ended up not using this 
		// pre order since this will stop at a root of a subtree, then can compare children to root
		// O(n) time for this since visit every node
		//----------------------------------------------------------------------------------------------------------
		void preOrderTraversalBalance(A_TreeNode<T>* node) {
			if (node != nullptr) {															  // if node is not null						
				node->balance_factor = node_balance_factor(node);
				preOrderTraversalBalance(node->left);									    // traverse left subtree
				preOrderTraversalBalance(node->right);									   // traverse right subtree
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// POST ORDER TRAVERSAL TO DETERMINE HEIGHT OF A NODE 
		// the way I set this up is count up the edges on the way down to a leaf
		// and see how deep this trip was. if it's a new depth record, update max_height
		// then subtract from ths value as we go back up to the root node and start again
		// O(n) time for this since visit every node. 
		//----------------------------------------------------------------------------------------------------------
		void postOrderTraversal(A_TreeNode<T>* node, int& height, int& max_height) {
            height ++ ;	
            if (height > max_height){
					max_height = height;
			}
			if (node != nullptr) {															  // if node is not null																	   // height goes up
				postOrderTraversal(node->left, height, max_height);							// traverse left subtree
                height -- ;		
				postOrderTraversal(node->right, height, max_height);					   // traverse right subtree
                height -- ;		
																                // going back up , height goes down
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// PRINT THIS TREE
		//----------------------------------------------------------------------------------------------------------
		void printTree(A_TreeNode<T>* root, int level = 0, const std::string& prefix = "", int spacing = 5) {
			if (root) {																		  // if root is not null
				if (level == 0) {														 // if root is the root node
					std::cout << "Root: " << root->data << " (" << root->balance_factor  << ")" <<  std::endl; 
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";						 // determine branch
					std::string spaces(spacing * level - 2, ' ');								// determine spacing
					std::cout 
                    << spaces 
                    << branch 
                    << prefix << root->data << " (" 
                    << root->balance_factor 
                    << ")"
                    << std::endl;
				}
				if (root->left || root->right) {											 // if node has children
					printTree(root->left, level + 1, "L: ", spacing);							 // print left child
					printTree(root->right, level + 1, "R: ", spacing);							// print right child
				}
			}
		}
	//--------------------------------------------------------------------------------------------------------------
	// CONSTRUCTOR / DESTRUCTOR
	//--------------------------------------------------------------------------------------------------------------

		AVL_BinarySearchTree() : root(nullptr) {}											   // no-arg constructor
		~AVL_BinarySearchTree() {
			if (root != nullptr) {
				std::stack<A_TreeNode<T>*> s;
				s.push(root);
				while (!s.empty()) {
					A_TreeNode<T>* current = s.top();
					s.pop();
					if (current->left != nullptr)	s.push(current->left);
					if (current->right != nullptr)	s.push(current->right);
					delete current;
				}
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// INSERT
		//----------------------------------------------------------------------------------------------------------
		void insert(T key) {
			root = insert(root, key);
		}
		//----------------------------------------------------------------------------------------------------------
		// REMOVE
		//----------------------------------------------------------------------------------------------------------
		void remove(T key) {
			root = remove(root, key);										 // call private recursive helper remove
		}
		//----------------------------------------------------------------------------------------------------------
		// SEARCH
		// O(log n) where n is the number of nodes in the tree
		//----------------------------------------------------------------------------------------------------------
		bool search(T key) {
			A_TreeNode<T>* current = root;															// start at root
			while (current != nullptr) {												// while current is not null
				if (key == current->data)		return true;											// found key
				else if (key < current->data)	current = current->left;		// key is less than current, go left
				else							current = current->right;	// key is greater than current, go right
			}
			return false;																			// key not found
		}
		//----------------------------------------------------------------------------------------------------------
		// FIND KTH SMALLEEST
		// calls private method above
		// O(n) time for this since visiting nodes until potentially every node visited
		//----------------------------------------------------------------------------------------------------------
		int kth_smallest(int& nth_val) {
			int tracker = 0;
			int result = 0;
			inOrderFindKthSmallest(root, nth_val, tracker, result);					// call private recursive helper
			return result;
		}
		//----------------------------------------------------------------------------------------------------------
		// public pre-order traversal, no arguments
		//----------------------------------------------------------------------------------------------------------
		void pre_order(bool& valid) {
			preOrderTraversal(root, valid);											// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// FIND HEIGHT
		//----------------------------------------------------------------------------------------------------------
		// calls private method above
		// O(n) time for this since visiting nodes until potentially every node visited
		//----------------------------------------------------------------------------------------------------------
		void post_order(int& height, int& max_height) {
			postOrderTraversal(root, height,  max_height);							// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// FIND NODE BALANCE
		//----------------------------------------------------------------------------------------------------------
		// calls private method above
		// O(n) time for this since visiting every node
		//----------------------------------------------------------------------------------------------------------
		void post_order_left_node(A_TreeNode<T>* node,  int& height, int& max_height) {
			postOrderTraversal(node->left, height,  max_height);				    // call private recursive helper
		}
		void post_order_right_node(A_TreeNode<T>* node, int& height, int& max_height) {
			postOrderTraversal(node->right, height,  max_height);			        // call private recursive helper
		}
        //----------------------------------------------------------------------------------------------------------
		// FIND TREE BALANCE
		//----------------------------------------------------------------------------------------------------------
		// calls private method above
		// O(n) time for this since visiting every node
		//----------------------------------------------------------------------------------------------------------
		void post_order_left(int& height, int& max_height) {
			postOrderTraversal(this->root->left, height,  max_height);				// call private recursive helper
		}
		void post_order_right(int& height, int& max_height) {
			postOrderTraversal(this->root->right, height,  max_height);				// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// public print with no arguments
		void print() {
			printTree(root);														// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// public min with no arguments
		T min() {
			return min(root)->data;												// call private recursive helper min
		}
		//----------------------------------------------------------------------------------------------------------
		// public max with no arguments
		T max() {
			return max(root)->data;												// call private recursive helper max
		}
		//----------------------------------------------------------------------------------------------------------
		searchData& get_data(){
			return this->sd;
		}

		//----------------------------------------------------------------------------------------------------------
		// Create the BST via vector data
		//----------------------------------------------------------------------------------------------------------
		vector<int> initialize(int size, char type, bool print){
			vector<int>v(size);																		 // get a vector
			intialize_vector(v, v.size(), type, print);	// initialize the vector with either random or assorted ints
			for (int i = 0 ; i < v.size() ; i ++ ){	             // insert the values from the vector into this tree
        		this->insert(v[i]);		 // lazy insertion approach, could use better method like divide and conquer
   			}
			return v;
		};
		//----------------------------------------------------------------------------------------------------------
		// Flaaten this bst into a vector
		//----------------------------------------------------------------------------------------------------------
		vector<T> flatten(){
			vector<T>v;																	 // instantiate a new vector
			in_order(v);										   // place data in order from this tree into vector
			return v;																		   // return this vector
		}
		//----------------------------------------------------------------------------------------------------------
		T closest_val(T val){															   // find the closest value 
			int difference = 999999;						
			int closest_val = -1;	
			vector<T> v = flatten();									 // flatten the tree and place into a vector
			for (int i = 0 ; i < v.size() ; i ++ ){
				int diff = abs(v[i] - val);				// find the difference between val and current int in vector
				if (diff < difference){										// if new low, set it as the closest val
					difference = diff;													// set new lowest difference 
					closest_val = v[i];															  // set closest val
				}
				if (difference == 0 ){							   // if difference == 0, same value present in tree
					return val;
				}
			}
			return closest_val;
		}
		//----------------------------------------------------------------------------------------------------------
		// CHECK VALIDITY OF THIS BST  (left child < root / right child > root)
		//----------------------------------------------------------------------------------------------------------
		bool is_valid(){
			bool valid = true;
			pre_order(valid);  // this method stops at a root node, and compares value of children to that root node
			if (valid){
				cout << "Tree is valid" << endl;
			} else {
				cout << "Tree is invalid" << endl;
			}
			return valid;
		}
		//----------------------------------------------------------------------------------------------------------
		// GET HEIGHT OF THIS TREE 
		//----------------------------------------------------------------------------------------------------------
		int get_height(){
			int max_height = 0;																  // int to track height
			int height = 0;										  // int to track height both passed in by reference
			post_order(height, max_height);							   // recerse through in post_oder (leaf action)
			return max_height;	
		}
        void set_Balance(){
            preOrderTraversalBalance(root);
        }
        //----------------------------------------------------------------------------------------------------------
		// GET BALANCE OF THIS TREE 
		// this just calls the above method (get height) but on the left and right children of this root node
		//----------------------------------------------------------------------------------------------------------
		int balance_factor(){
			int l_height = 0;								 // current height of left subtree - passed as reference
			int r_height = 0;								// current height of right subtree - passed as reference
			int left_max_h = 0;							   // current left subtree max height - passed as areference
			int right_max_h = 0;						  // current right subtree max height - passed as areference
			post_order_left(l_height, left_max_h);		  		              // call max height on the left subtree
			post_order_right(r_height, right_max_h);				         // call max height on the right subtree
			return left_max_h - right_max_h;												// return the difference
		}
		//----------------------------------------------------------------------------------------------------------
		// GET BALANCE OF THIS NODE 
		// this just calls the above method (get height) but on the left and right children of this root node
		//----------------------------------------------------------------------------------------------------------
		int node_balance_factor(A_TreeNode<T>* node){
			int l_height = 0;								 // current height of left subtree - passed as reference
			int r_height = 0;								// current height of right subtree - passed as reference
			int left_max_h = 0;							   // current left subtree max height - passed as areference
			int right_max_h = 0;						  // current right subtree max height - passed as areference
			post_order_left_node(node, l_height, left_max_h);		  		  // call max height on the left subtree
			post_order_right_node(node, r_height, right_max_h);				 // call max height on the right subtree
			return left_max_h - right_max_h;												// return the difference
		}
		//----------------------------------------------------------------------------------------------------------
		// IN ORDER TRAVERSAL TO COUNT NODES ON THIS TREE 
		//----------------------------------------------------------------------------------------------------------
		// in order to preserver sorted arrangement
		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		//----------------------------------------------------------------------------------------------------------
		
        int tree_nodes(){
			int count = 0; 
			in_order_count(count);
            return count;
        }
};

#endif