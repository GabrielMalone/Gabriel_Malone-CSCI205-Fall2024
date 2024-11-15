
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
class TreeNode {
	public:
		T data;					  // node's payload. Custom instances of T should have comparison operators defined
		TreeNode* left;																	   // pointer to left child
		TreeNode* right;																  // pointer to right child
		TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};
//-----------------------------------------------------------------------------------------------------------------	
// BinarySearchTree class
//-----------------------------------------------------------------------------------------------------------------	
template <typename T>
class BinarySearchTree {
	private:
		TreeNode<T>* root;																	// pointer to root node
		int nodeCount = 0;															 // number of nodes in the tree
		searchData sd;														   // track data related to BST methods
		int max_height = 0 ; 													   // track the height of this tree	
		//---------------------------------------------------------------------------------------------------------	
		// helper function with arguments to insert a node recursively
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		TreeNode<T>* insert(TreeNode<T>* node, T key) {
			sd.inserts ++ ;
			if (node == nullptr){												// if node is null, create new node
				nodeCount++;																// increment node count
				
				return new TreeNode<T>(key);													 // return new node
			}
			if (key < node->data)												 // if key is less than node's data
				node->left = insert(node->left, key);					// recursively insert key into left subtree
			else if (key > node->data)										  // if key is greater than node's data
				node->right = insert(node->right, key);				   // recursively insert key into right subtree
			return node;																			 // return node
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the minimum value in a subtree9
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		TreeNode<T>* min(TreeNode<T>* node) {
			while (node->left != nullptr)											// while node has a left child
				node = node->left;																		// go left
			return node;																			// return node
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the maximum value in a subtree
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		TreeNode<T>* max(TreeNode<T>* node) {
			while (node->right != nullptr)											// while node has a right child
				node = node->right;																		// go right
			return node;
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the inorder successor of a node
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		TreeNode<T>* remove(TreeNode<T>* node, T key) {								  // args: start, key to remove
			if (node == nullptr)		return node;							       // key was not found in tree
			if (key < node->data)		node->left  = remove(node->left, key);   // key < than node's data, go left
			else if (key > node->data)	node->right = remove(node->right, key); // key > than node's data, go right
			else {																	   // found the node, remove it
				if (node->left == nullptr) {								   // node has one child (right child))
					TreeNode<T>* temp = node->right;										   // store right child
					nodeCount -- ;															// decrement node count
					delete node;																	 // delete node
					return temp;															  // return right child
				} else if (node->right == nullptr) {							 // node has one child (left child)
					TreeNode<T>* temp = node->left;												// store left child
					delete node;																	 // delete node
					nodeCount -- ;															// decrement node count
					return temp;															   // return left child
				}													// node has two children, get inorder successor
				TreeNode<T>* temp	= min(node->right);								   // smallest in right subtree
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
		void inOrderTraversal(TreeNode<T>* node, vector<T>& v) {
			if (node != nullptr) {															  // if node is not null
				inOrderTraversal(node->left, v);											// traverse left subtree
				v.emplace_back(node->data);												   // place data into vector
				inOrderTraversal(node->right, v);										   // traverse right subtree
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// IN ORDER TRAVERSAL TO FIND KTH SMALLEST INT
		// in order traversal to follow ints in ascending order 
		// O(n) time for this since visiting nodes until potentially every node visited
		//----------------------------------------------------------------------------------------------------------
		void inOrderFindKthSmallest(TreeNode<T>* node, int& nth_val, int& tracker, int& result) {
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
		void preOrderTraversal(TreeNode<T>* node, bool& valid) {
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
		// POST ORDER TRAVERSAL TO DETERMINE HEIGHT OF A NODE
		// the way I set this up is count up the edges on the way down to a leaf
		// and see how deep this trip was. if it's a new depth record, update max_height
		// then subtract from ths value as we go back up to the root node and start again
		// O(n) time for this since visit every node. 
		//----------------------------------------------------------------------------------------------------------
		void postOrderTraversal(TreeNode<T>* node, int& height, int& max_height) {
			if (node != nullptr) {															  // if node is not null
				height ++ ;																		   // height goes up
				postOrderTraversal(node->left, height, max_height);							// traverse left subtree
				postOrderTraversal(node->right, height, max_height);					   // traverse right subtree
				height -- ;														 // going back up , height goes down
				if (height > max_height){
					max_height = height;
				}
			}
		}
		//----------------------------------------------------------------------------------------------------------
		// PRINT THIS TREE
		//----------------------------------------------------------------------------------------------------------
		void printTree(TreeNode<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
			if (root) {																		  // if root is not null
				if (level == 0) {														 // if root is the root node
					std::cout << "Root: " << root->data << std::endl;							  // print root node
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";						 // determine branch
					std::string spaces(spacing * level - 2, ' ');								// determine spacing
					std::cout << spaces << branch << prefix << root->data << std::endl;				   // print node
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
	public:
		BinarySearchTree() : root(nullptr) {}												   // no-arg constructor
		~BinarySearchTree() {
			if (root != nullptr) {
				std::stack<TreeNode<T>*> s;
				s.push(root);
				while (!s.empty()) {
					TreeNode<T>* current = s.top();
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
			root = insert(root, key);										 // call private recursive helper insert
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
			TreeNode<T>* current = root;															// start at root
			while (current != nullptr) {												// while current is not null
				if (key == current->data)		return true;											// found key
				else if (key < current->data)	current = current->left;		// key is less than current, go left
				else							current = current->right;	// key is greater than current, go right
			}
			return false;																			// key not found
		}
		//----------------------------------------------------------------------------------------------------------
		// public in-order traversal, no arguments
		//----------------------------------------------------------------------------------------------------------
		void in_order(vector<T>& v) {
			inOrderTraversal(root, v);												// call private recursive helper
			std::cout << std::endl;																		 // new line
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
		void pre_order(bool& valid) {
			preOrderTraversal(root, valid);											// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// FIND HEIGHT
		// calls private method above
		// O(n) time for this since visiting nodes until potentially every node visited
		//----------------------------------------------------------------------------------------------------------
		void post_order(int& height, int& max_height) {
			postOrderTraversal(root, height,  max_height);							// call private recursive helper
		}
		//----------------------------------------------------------------------------------------------------------
		// FIND TREE BALANCE
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
		int tree_nodes(){
			return this->nodeCount;
		}
		//----------------------------------------------------------------------------------------------------------
		// Create the BST via vector data
		//----------------------------------------------------------------------------------------------------------
		vector<int> initialize(int size, char type, bool print){
			vector<int>v(size);					
			intialize_vector(v, v.size(), type, print);
			for (int i = 0 ; i < v.size() ; i ++ ){
        		this->insert(v[i]);
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
					break;
				}
			}
			return closest_val;
		}
		//----------------------------------------------------------------------------------------------------------
		// CHECK VALIDITY OF THIS BST  (left child < root / right child > root)
		//----------------------------------------------------------------------------------------------------------
		bool is_valid(){
			bool valid = true;
			pre_order(valid);
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
		//----------------------------------------------------------------------------------------------------------
		// GET BALANCE OF THIS TREE 
		// this just calls the above method (get height) but on the left and right children of this root node
		//----------------------------------------------------------------------------------------------------------
		int balance_factor(){
			int l_height = 0;		
			int r_height = 0;
			int left_max_h = 0;
			int right_max_h = 0;
			post_order_left(l_height, left_max_h);
			post_order_right(r_height, right_max_h);
			return left_max_h - right_max_h;
		}
		//----------------------------------------------------------------------------------------------------------
};
