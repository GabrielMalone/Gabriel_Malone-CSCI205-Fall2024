#ifndef AVL_TREE
#define AVL_TREE

#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include "bst_helpers.hpp/bst_data.hpp"
#include "bst_helpers.hpp/initialize_vec.hpp"
#include <cmath>
#include "backend/ClosedHashTable.hpp"
#include "bst_helpers.hpp/tree_node.hpp"
#include "bst_helpers.hpp/tree_order.hpp"
#include "bst_helpers.hpp/cell.hpp"


using namespace std;

//-----------------------------------------------------------------------------------------------------------------	
// BinarySearchTree class
//-----------------------------------------------------------------------------------------------------------------	
template <typename T>
class AVL_BinarySearchTree {
	private:
	//-------------------------------------------------------------------------------------------------------------
	// Class vars
	//-------------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* root;																// pointer to root node
		int NodeCount = 0;
		searchData sd;														   // track data related to BST methods
		int max_height = 0 ; 													   // track the height of this tree
		unordered_map<int, tree_order<T>> TO;
		int pos = 0;
		//---------------------------------------------------------------------------------------------------------
		// ROTATE RIGHT -https://www.youtube.com/watch?v=JPI-DPizQYk// runestone's implementation did not work
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* rotateRight(A_TreeNode<T>* node) {
			A_TreeNode<T>*  B = node->left;  // B is node that is rotated to the position of 'node' beig passed in
			A_TreeNode<T>*  Y = B->right;					 // Y is the node that is current the left child of 'B'
			B->right = node;													// 'node' becomes left child of 'B'
			node->left = Y;										// left child of B swapped to right child of 'node'
			if (Y != nullptr) Y->parent = node; 					   // if Y isn't null, set 'node' to its parent
			B->parent = node->parent;  // now that B root of subtree, make sure it has parent of former root 'node'
			node->parent = B;									// 'B' becomes the parent of the former root 'node'
			node->balance_factor = node_balance_factor(node);
			B->balance_factor = node_balance_factor(B);
			return B; 																	// New root after rotation
		}
		//---------------------------------------------------------------------------------------------------------
		// ROTATE LEFT - https://www.youtube.com/watch?v=JPI-DPizQYk - mirrors the method above
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* rotateLeft(A_TreeNode<T>* node) {  // node is the root of the subtree that is out of balance
			A_TreeNode<T>*  B = node->right;  // B is node that is rotated to the position of 'node' beig passed in
			A_TreeNode<T>*  Y = B->left;					 // Y is the node that is current the left child of 'B'
			B->left = node;														// 'node' becomes left child of 'B'
			node->right = Y;									// left child of B swapped to right child of 'node'
			if (Y != nullptr) Y->parent = node; 					   // if Y isn't null, set 'node' to its parent
			B->parent = node->parent;  // now that B root of subtree, make sure it has parent of former root 'node'
			node->parent = B;									// 'B' becomes the parent of the former root 'node'
			node->balance_factor = node_balance_factor(node);
			B->balance_factor = node_balance_factor(B);
			return B; 																	// New root after rotation
		}
		//---------------------------------------------------------------------------------------------------------
		// BALANCE
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* balance(A_TreeNode<T>*  node) {
			if (node->balance_factor > 1 && node->left->balance_factor >= 0) { // if in linked list form going left
				return rotateRight(node);														  // Left Left Case
			}
			if (node->balance_factor > 1 && node->left->balance_factor < 0) {	    // if in a kinked form going LR
				node->left = rotateLeft(node->left);							 // rotate the bottom of tree first
				return rotateRight(node);													     // then rotate top
			}
			if (node->balance_factor < -1 && node->right->balance_factor <= 0) { // in linked list form going right
				return rotateLeft(node);													    // Right Right Case
			}
			if (node->balance_factor < -1 && node->right->balance_factor > 0) {		  // if in kinked form going RL
				node->right = rotateRight(node->right);						// Right Left Case, rotate bottom first
				return rotateLeft(node);															    // then top
			}
			return node;
		}
		//---------------------------------------------------------------------------------------------------------
		// INSERT - private
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* _insert(A_TreeNode<T>* node, T key) {
			sd.inserts ++ ;
			if (node == nullptr){
				return new A_TreeNode(key); 				 				 // if reached a leaf return a new node
			}
			if (key < node->data) {										   	  // if less than subtree root, go left
				node->left = _insert(node->left, key);					   // recursively call this until at a leaf
				node->left->parent = node;  //set the parent pointer of the newly inserted node in the left subtree
			} else if (key > node->data) {								  // if greater than subtree root, go right
				node->right = _insert(node->right, key);				   // recursively call this until at a leaf
				node->right->parent = node; //set the parent pointer of the newly inserted node in the left subtree
			} else {
				return node; 														 // No duplicate values allowed
			}
			node->balance_factor = node_balance_factor(node);   // calc BF of cur node - if balanced post insertion
			return balance(node);								    // balance the node if it has become unbalanced
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the inorder successor of a node
		// O(log n) where n is the number of nodes in the tree
		// added the balance logic at end
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* _remove(A_TreeNode<T>* node, T key) {						  // args: start, key to remove
			if (node == nullptr)		return node;							       // key was not found in tree
			if (key < node->data)		node->left  = _remove(node->left, key);  // key < than node's data, go left
			else if (key > node->data)	node->right = _remove(node->right, key);// key > than node's data, go right
			else {																	   // found the node, remove it
				if (node->left == nullptr) {								   // node has one child (right child))
					A_TreeNode<T>* temp = node->right;										   // store right child
					delete node;																	 // delete node
					return temp;															  // return right child
				} else if (node->right == nullptr) {							 // node has one child (left child)
					A_TreeNode<T>* temp = node->left;											// store left child
					delete node;																	 // delete node
					return temp;															   // return left child
				}													// node has two children, get inorder successor
				A_TreeNode<T>* temp	= min(node->right);								   // smallest in right subtree
				node->data			= temp->data;	   // copy inorder successor's content to this node (to delete)
				node->right			= _remove(node->right, temp->data);					// delete inorder successor
			}
			if (node == nullptr) return  node; 					    // if root has become nullptr (was a leaf node)
			node->balance_factor = node_balance_factor(node);		   // calculate balance factor of ccurrent root
			return balance(node);								   // perform any rotations that might be necessary
		}
		//---------------------------------------------------------------------------------------------------------
		// helper function to find the MIN value in a subtree
		// O(log n) where n is the number of nodes in the tree
		//---------------------------------------------------------------------------------------------------------
		A_TreeNode<T>* min(A_TreeNode<T>* node) {
			while (node->left != nullptr)											 // while node has a left child
				node = node->left;																	   	 // go left
			return node;																			 // return node
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
		// PRE ORDER TRAVERSAL TO FILL OUT MATRIX FOR PRINTING TREE
		//----------------------------------------------------------------------------------------------------------
		// maybe need to keep track of height?
		// get all the nodes for his level of the tree
		// pick out the leftmost remaining node
		// now we can fill in each row of the matrix left to right
		//----------------------------------------------------------------------------------------------------------
		void preOrderTraversalMatrix(A_TreeNode<T>* node, vector<vector<Cell<T>> >& matrix, int& height, 
									                        int& nodes_used, int max_width, int int_w) {
			auto spacing = double(max_width / pow(2, height));
			if (node != nullptr) {
				int node_value = node->data;  								   // Get the value present at this node
				tree_order<T> t;
				for (const auto &pair: TO) {                			  // get the node position data from the map
					if (pair.second.value == node_value) {	 // iterate through map and find the current node's data
						t = pair.second;
						break;
					}
				}
				if (nodes_used > 0) {
					if (height == 0) {
						for (int i = 0; i < matrix[0].size(); i++) { 				   // Find the next cell to fill
							if (matrix[height][i].is_node) {
								matrix[height][i].node_data.value = node_value;
								matrix[height][i].is_node = false;
								matrix[height][i].used = true;
								break;
							}
						}
					} else {
						for (int i = 0; i < matrix[0].size(); i++) {  				   // Find the next cell to fill
							if (matrix[height][i].is_node) { 								  // if we are at a node
								int parent_index = 0;       								  // get the parent info
								int parent_data = t.parent_val;
								for (int j = 0; j < matrix[0].size(); j++) {
									if (parent_data == matrix[height - int_w/2][j].node_data.value) {
										parent_index = j; 									 // parent location found
										break;
									} 	   // should we place this data to the left or the right of this parent index
								}
								if (t.left) {
									matrix[height][parent_index - spacing].node_data.value = node_value;
									matrix[height][parent_index - spacing].is_node = false;
									matrix[height][parent_index - spacing].used = true;
									matrix[height][parent_index].is_edges = true;
									int connector_start = parent_index - spacing + int_w/2;
									int connector_end = parent_index;
									for (int c = connector_start ; c < connector_end ; c ++ ){
										matrix[height][c].is_connector = true;
									}
									nodes_used--;
									break;
								}
								if (t.right) {
									matrix[height][parent_index + spacing].node_data.value = node_value;
									matrix[height][parent_index + spacing].is_node = false;
									matrix[height][parent_index + spacing].used = true;
									matrix[height][parent_index].is_edges = true;
									int connector_start = parent_index + int_w/2;
									int connector_end = parent_index + spacing;
									for (int c = connector_start ; c < connector_end; c ++ ){
										matrix[height][c].is_connector = true;
									}
									nodes_used--;
									break;
								}
							}
						}
					}
				}
				height++; 														  // Going down one level in the tree
				preOrderTraversalMatrix(node->left, matrix, height, nodes_used, max_width, int_w);         // go left
				preOrderTraversalMatrix(node->right, matrix, height, nodes_used, max_width, int_w);       // go right
				height--;  																  // Coming back up one level
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
	public:
		//----------------------------------------------------------------------------------------------------------
		// PRINT THIS TREE
		//----------------------------------------------------------------------------------------------------------
		void printTree(A_TreeNode<T>* root,int& pos, int level = 0, const std::string& prefix = "", int spacing = 5) {
			if (root) {																		  // if root is not null
				if (level == 0) {														 // if root is the root node
					//std::cout << "Root: " << root->data << " (" << root->balance_factor  << ")" <<  std::endl;
					tree_order<T> t;
					t.level = 0;
					t.value = root->data;
					t.left = true;
					TO.insert(make_pair(pos, t));
					pos ++ ;
					NodeCount ++ ;
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";						 // determine branch
					std::string spaces(spacing * level - 2, ' ');								// determine spacing
//					std::cout
//                    << spaces
//                    << branch
//                    << prefix << root->data << " ("
//                    << root->balance_factor
//                    << ")"
//                    << std::endl;
					tree_order<T> t;
					if (prefix == "L: "){
						t.left = true;
					} else {
						t.right = true;
					}
					t.parent = root->parent;
					t.parent_val = root->parent->data;
					t.level = level;
					t.value = root->data;
					TO.insert(make_pair(pos, t));
					pos ++;
					NodeCount ++ ;
				}
				if (root->left || root->right) {											 // if node has children
					printTree(root->left, pos,  level + 1, "L: ", spacing);						 // print left child
					printTree(root->right, pos, level + 1, "R: ", spacing);					    // print right child
				}
			}
		}
	//--------------------------------------------------------------------------------------------------------------
	// CONSTRUCTOR / DESTRUCTOR
	//--------------------------------------------------------------------------------------------------------------
		AVL_BinarySearchTree() : root(nullptr) {}											   // no-arg constructor
	//--------------------------------------------------------------------------------------------------------------
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
			root = _insert(root, key);
		}
		int get_num_nodes(){
			return NodeCount;
		}
		//----------------------------------------------------------------------------------------------------------
		// REMOVE
		//----------------------------------------------------------------------------------------------------------
		void remove(T key) {
			root = _remove(root, key);									// call private recursive helper remove
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
			printTree(root, pos);													// call private recursive helper
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
		//----------------------------------------------------------------------------------------------------------
		// FIND THE BALANCE FACTOR OF EACH NODE
		//----------------------------------------------------------------------------------------------------------
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
		// FILL OUT MATRIX VIA PREORDER TRAVERSAL
		//----------------------------------------------------------------------------------------------------------
		void fill_matrix(int w){   // w could change this for very big trees with numbers > 99
			int height = 0;
			int nodes_used = tree_nodes();
			int maxwidth = pow(2, get_height()) * w;  		// nodes * space for each node * spaces between node
			vector<vector<Cell<T>> >cell_matrix = initialize_matrix(w);
			preOrderTraversalMatrix(root, cell_matrix, height, nodes_used, maxwidth, w);
			for (int e = 0 ; e < cell_matrix.size(); e ++) {                                         // iterate rows
				for (int f = 0; f < cell_matrix[0].size(); f++) {                                 // iterate columns
					Cell<T> cur_cell = cell_matrix[e][f];
					//----------------------------------------------------------------------------------------------
					if (cur_cell.used) {
						cout << Colors::YELLOW << setw(w) << setfill(' ') << cur_cell.node_data.value << Colors::RESET;
					//----------------------------------------------------------------------------------------------
					} else if (cur_cell.is_connector) {
						cout << Colors::GREEN << setw(w) << setfill('-') << "-" << Colors::RESET;
					//----------------------------------------------------------------------------------------------
					} else if (cur_cell.is_edges){
						cout << Colors::GREEN << setw(w) << setfill(' ') << "^" << Colors::RESET;
					//----------------------------------------------------------------------------------------------
					} else {
						cout << Colors::WHITE << setw(w) << setfill(' ') << " ";
					}
					//----------------------------------------------------------------------------------------------
				}
				cout << endl;                                                                             // end row
			}

		}
		//----------------------------------------------------------------------------------------------------------
		// IN ORDER TRAVERSAL TO COUNT NODES ON THIS TREE 
		//----------------------------------------------------------------------------------------------------------
		// in order to preserver sorted arrangement
		// helper function to traverse the tree in order
		// O(n) where n is the number of nodes in the tree
		//----------------------------------------------------------------------------------------------------------
        int tree_nodes(){
			int count = 0; 																// pass this in by reference
			in_order_count(count);														  // count the tree in order
            return count;
        }
		unordered_map<int, tree_order<T> >& get_tree_map(){
			return TO;
		}
		vector<vector<Cell<T>>> initialize_matrix(int w){
			//--------------------------------------------------------------------------------------------------------
			// method vars
			//--------------------------------------------------------------------------------------------------------
			this->print();                                                            // used this to check final tree
			unordered_map<int, tree_order<T>> TO = this->get_tree_map();
			int total_nodes = this->get_num_nodes();
			vector<int>space_saver;                                          // tracks if a column is in use by a node
			int height = this->get_height() + 1;                                                     // height of tree
			cout << "height of this tree is: " << height - 1 << endl;
			cout << "number of nodes in this tree is: " << total_nodes << endl;
			int maxwidth = pow(2, height) * w;                                // potential nodes * space for each node
			int spacing = maxwidth / 2;                    // first row spacing requirements // will decrease each row
			int space_counter = spacing;                                   // this will print the spaces between nodes

			//--------------------------------------------------------------------------------------------------------
			// Lets build an actual matrix of cells
			//--------------------------------------------------------------------------------------------------------
			vector<vector<Cell<T>> >cell_matrix;
			for (int a = 0 ; a < height; a ++ ){
				vector<Cell<T>> row;
				for (int b = 0 ; b < maxwidth + 1; b ++ ){
					Cell<T> c;
					c.x_coord = b;
					c.y_coord = a;                                                   // used these coords in debugging
					row.emplace_back(c);
				}
				cell_matrix.emplace_back(row);
			}
			//--------------------------------------------------------------------------------------------------------
			// find where all the potential nodes are and mark those positions in the cell matrix
			//--------------------------------------------------------------------------------------------------------
			for (int i = 0 ; i < height ; i ++ ){                                                              // rows
				space_counter = spacing;                                              // reset space_counter every row
				for (int j = 0 ; j < maxwidth ; j ++ ){                                                     // columns
					if (space_counter < 0){                   // has this space been used by a node? if so, dont print
						if (find(space_saver.begin(), space_saver.end(), j) == space_saver.end())                 // ^
							cell_matrix[i][j].is_node = true;
					}
					space_counter -- ;                                     // decrement space counter as columns print
				}
				spacing /=2;       // halve spacing each row since number of nodes can increase by power of 2 each row
			}
			return cell_matrix;
		}
};

#endif