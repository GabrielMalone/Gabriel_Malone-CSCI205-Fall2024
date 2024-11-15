/*
	A Binary Search Tree (BST) is a hierarchical data structure used in computer science to store and organize data efficiently. 
	It is a type of binary tree with the following key characteristics:

	1.	Binary Tree Structure: A BST is a binary tree, meaning that each node has at most two child nodes: a left child and a right child. 
		These child nodes are also BSTs, forming sub-trees within the main tree.

	2.	Ordering Property: The defining feature of a BST is the ordering property. Each node in a BST is associated with a value, 
		and this value is such that for any given node:
		~ All values in the left sub-tree are less than the value of the node.
		~ All values in the right sub-tree are greater than the value of the node.

		This ordering property ensures that the tree is organized in such a way that you can quickly search for, insert, or delete values in logarithmic time.

	3.	No Duplicates: In most BST implementations, duplicate values are not allowed. If a duplicate value is encountered, it can be placed in 
		either the left or right sub-tree, depending on the specific implementation.

	4.	Balanced vs. Unbalanced: BSTs can be balanced or unbalanced. In a balanced BST, the tree is structured such that its height is minimized,
		leading to efficient search, insert, and delete operations. In an unbalanced BST, the height can approach that of a linked list,
		resulting in poor performance for these operations. Techniques such as AVL trees and Red-Black trees are used to ensure that the tree remains balanced.

	5. Traversal: Common ways to traverse a BST include in-order, pre-order, and post-order traversal.
		~ In-order traversal of a BST results in visiting the nodes in ascending order of their values.
		~ Pre-order traversal of a BST results in visiting the root node first, followed by the left and right sub-trees.
		~ Post-order traversal of a BST results in visiting the left and right sub-trees first, followed by the root node.

	BSTs are widely used in various applications, including databases, search algorithms, and data structures like sets and maps. 
	The efficiency of search, insertion, and deletion operations in a BST makes it a valuable tool for managing and organizing data. 
	However, it's important to note that the efficiency of these operations depends on the tree's balance, and unbalanced trees 
	may degrade to linear time complexity for these operations. To maintain balance, self-balancing binary search trees, 
	such as AVL trees and Red-Black trees, are often used.
*/

#include <iostream>
#include <vector>
#include <stack>
#include "bst_helpers.hpp/bst_data.hpp"
#include "bst_helpers.hpp/initialize_vec.hpp"
#include <cmath>

// TreeNode class
template <typename T>
class TreeNode {
	public:
		T data;				// node's payload. Custom instances of T should have comparison operators defined
		TreeNode* left;		// pointer to left child
		TreeNode* right;	// pointer to right child
		TreeNode(T val) : data(val), left(nullptr), right(nullptr) {}
};

// BinarySearchTree class
template <typename T>
class BinarySearchTree {
	private:
		TreeNode<T>* root;									// pointer to root node
		int nodeCount = 0;									// number of nodes in the tree
		searchData sd;										// track data related to BST methods
		int max_height = 0 ; 								// track the height of this tree		
		// helper function with arguments to insert a node recursively
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* insert(TreeNode<T>* node, T key) {

			sd.inserts ++ ;
			if (node == nullptr){							// if node is null, create new node
				nodeCount++;								// increment node count
				
				return new TreeNode<T>(key);				// return new node
			}
			if (key < node->data)							// if key is less than node's data
				node->left = insert(node->left, key);		// recursively insert key into left subtree
			else if (key > node->data)						// if key is greater than node's data
				node->right = insert(node->right, key);		// recursively insert key into right subtree
			return node;									// return node
		}

		// helper function to find the minimum value in a subtree9
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* min(TreeNode<T>* node) {
			while (node->left != nullptr)					// while node has a left child
				node = node->left;							// go left
			return node;									// return node
		}

		// helper function to find the maximum value in a subtree
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* max(TreeNode<T>* node) {
			while (node->right != nullptr)					// while node has a right child
				node = node->right;							// go right
			return node;
		}

		// helper function to find the inorder successor of a node
		// O(log n) where n is the number of nodes in the tree
		TreeNode<T>* remove(TreeNode<T>* node, T key) {							// args: start, key to remove
			if (node == nullptr)		return node;							// key was not found in tree
			if (key < node->data)		node->left  = remove(node->left, key);  // key is smaller than node's data, go left
			else if (key > node->data)	node->right = remove(node->right, key); // key is greater than node's data, go right
			else {																// found the node, remove it
				if (node->left == nullptr) {									// node has one child (right child))
					TreeNode<T>* temp = node->right;							// store right child
					nodeCount -- ;
					delete node;												// delete node
					return temp;												// return right child
				} else if (node->right == nullptr) {							// node has one child (left child)
					TreeNode<T>* temp = node->left;								// store left child
					delete node;												// delete node
					nodeCount -- ;
					return temp;												// return left child
				}
				// node has two children, get inorder successor
				TreeNode<T>* temp	= min(node->right);							// smallest in right subtree
				node->data			= temp->data;								// copy inorder successor's content to this node (to delete)
				node->right			= remove(node->right, temp->data);			// delete inorder successor
			}
			return node;														// return node (potentially modified)
		}

		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		void inOrderTraversal(TreeNode<T>* node, vector<T>& v) {
			if (node != nullptr) {					// if node is not null
				inOrderTraversal(node->left, v);		// traverse left subtree
				//std::cout << node->data << " ";		// print node's data
				v.emplace_back(node->data);			// place data into vector
				inOrderTraversal(node->right, v);		// traverse right subtree
			}
		}
		// helper function to traverse the tree in pre-order
		// O(n) where n is the number of nodes in the tree
		void preOrderTraversal(TreeNode<T>* node, bool& valid) {
			if (node != nullptr) {					// if node is not null
				// checking if tree is valid
				if (node->left == nullptr && node->right == nullptr){
					return; // if no children, nothing to check
				}
				else if (node->left != nullptr && node->right == nullptr){ // if just a left child
					if (node->left->data > this->root->data){ // if left greater than root
						valid = false; 
						return;
					};
				}
				else if (node->right != nullptr && node->left == nullptr){ // if just a right child
					if (node->right->data < this->root->data){ // if left greater than root or right smaller than root, invalid
						valid = false;
						return;
					};
				} else { // if both children present
					if (node->left->data > this->root->data || node->right->data <  this->root->data)
					valid = false;
					return;
				}
				preOrderTraversal(node->left, valid);		// traverse left subtree
				preOrderTraversal(node->right, valid);		// traverse right subtree
			}
		}

		// helper function to traverse the tree in post-order
		// O(n) where n is the number of nodes in the tree
		void postOrderTraversal(TreeNode<T>* node, int& height, int& max_height) {
			if (node != nullptr) {										// if node is not null
				height ++ ;												// height goes up
				postOrderTraversal(node->left, height, max_height);		// traverse left subtree
				postOrderTraversal(node->right, height, max_height);	// traverse right subtree
				height -- ;												// going back up , height goes down
				if (height > max_height){
					max_height = height;
				}
			}
		}

		// just for illustration purposes
		void printTree(TreeNode<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
			if (root) {																	// if root is not null
				if (level == 0) {														// if root is the root node
					std::cout << "Root: " << root->data << std::endl;					// print root node
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";				// determine branch
					std::string spaces(spacing * level - 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->data << std::endl;	// print node
				}

				if (root->left || root->right) {										// if node has children
					printTree(root->left, level + 1, "L: ", spacing);					// print left child
					printTree(root->right, level + 1, "R: ", spacing);					// print right child
				}
			}
		}

	public:
		// no-arg constructor
		BinarySearchTree() : root(nullptr) {}
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

		// public insert with T argument
		void insert(T key) {
			root = insert(root, key);	// call private recursive helper insert
		}

		// public remove with T argument
		void remove(T key) {
			root = remove(root, key);	// call private recursive helper remove
		}

		// public search with T argument
		// O(log n) where n is the number of nodes in the tree
		bool search(T key) {
			TreeNode<T>* current = root;									// start at root
			while (current != nullptr) {									// while current is not null
				if (key == current->data)		return true;				// found key
				else if (key < current->data)	current = current->left;	// key is less than current, go left
				else							current = current->right;	// key is greater than current, go right
			}
			return false;													// key not found
		}

		// public in-order traversal, no arguments
		void in_order(vector<T>& v) {
			inOrderTraversal(root, v);							// call private recursive helper
			std::cout << std::endl;							// new line
		}

		// public pre-order traversal, no arguments
		void pre_order(bool& valid) {
			preOrderTraversal(root, valid);						// call private recursive helper
		}

		// public post-order traversal, no arguments
		void post_order(int& height, int& max_height) {
			postOrderTraversal(root, height,  max_height);						// call private recursive helper
		}
		
		// public print with no arguments
		void print() {
			printTree(root);								// call private recursive helper
		}

		// public min with no arguments
		T min() {
			return min(root)->data;							// call private recursive helper min
		}

		// public max with no arguments
		T max() {
			return max(root)->data;							// call private recursive helper max
		}

		searchData& get_data(){
			return this->sd;
		}

		int tree_nodes(){
			return this->nodeCount;
		}

		vector<int> initialize(int size, char type, bool print){// create the BST via vector data
			vector<int>v(size);
			intialize_vector(v, v.size(), type, print);
			for (int i = 0 ; i < v.size() ; i ++ ){
        		this->insert(v[i]);
   			}
			return v;
		};

		vector<T> flatten(){
			vector<T>v;				// instantiate a new vector
			in_order(v);			// place data in order from this tree into vector
			return v;				// return this vector
		}

		T closest_val(T val){							// find the closest value 
			int difference = 999999;						
			int closest_val = -1;	
			vector<T> v = flatten();					// flatten the tree and place into a vector
			for (int i = 0 ; i < v.size() ; i ++ ){
				int diff = abs(v[i] - val);					// find the difference between val and current int in vector
				if (diff < difference){					// if new low, set it as the closest val
					difference = diff;					// set new lowest difference 
					closest_val = v[i];					// set closest val
				}
				if (difference == 0 ){					// if difference == 0, same value present in tree
					return val;
					break;
				}
			}
			return closest_val;
		}

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

		int get_height(){
			int max_height = 0;								// int to track height
			int height = 0;									// int to track height both passed in by reference
			post_order(height, max_height);					// recerse through in post_oder (leaf action)
			return max_height;	
		}
};
