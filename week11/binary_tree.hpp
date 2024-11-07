#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <cstdlib>
#include "backend/char_code.hpp"
#include <string>

template <typename T>
class BinaryTree {

	private:
		T key;											// node's payload
		BinaryTree<T> *leftChild;						// pointer to left child
		BinaryTree<T> *rightChild;						// pointer to right child
		
		// just for illustration purposes
		void printTree(BinaryTree<T>* root, int level = 0, const std::string& prefix = "", int spacing = 4) {
			if (root) {																	// if root is not null
				if (level == 0) {														// if root is the root node
					std::cout << "Root: " << root->key << std::endl;					// print root node
				} else {																// node is not the root node
					std::string branch = (level % 2 == 1) ? "└─" : "├─";				// determine branch
					std::string spaces(spacing * level - 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->key << std::endl;	// print node
				}

				if (root->leftChild || root->rightChild) {									// if node has children
					printTree(root->leftChild, level + 1, "L: ", spacing);					// print left child
					printTree(root->rightChild, level + 1, "R: ", spacing);					// print right child
				}
			}
		}

	public:

		BinaryTree(){												// constructor
			this->leftChild = NULL;									// set left child to null
			this->rightChild = NULL;								// set right child to null
		}

		BinaryTree(T rootObj){										// constructor
			this->key = rootObj;									// set root's payload
			this->leftChild = NULL;									// set left child to null
			this->rightChild = NULL;								// set right child to null
		}

		// ~BinaryTree(){											// destructor
		// 	if (this->leftChild != NULL)							// if left child is not null
		// 		delete this->leftChild;								// delete left child
		// 	if (this->rightChild != NULL)							// if right child is not null
		// 		delete this->rightChild;							// delete right child
		// }

		void insertLeft(BinaryTree<T> newNode){									// insert left child
			if (this->leftChild == NULL)							// if left child is null
				this->leftChild = new BinaryTree<T>(newNode);		// create new node
			else {													// left child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->leftChild = this->leftChild;						// set new node's left child to current left child
				this->leftChild = t;								// set current left child to new node
			}
		}

		void insertRight(BinaryTree<T> newNode){								// insert right child
			if (this->rightChild == NULL)							// if right child is null
				this->rightChild = new BinaryTree<T>(newNode);		// create new node
			else {													// right child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->rightChild = this->rightChild;					// set new node's right child to current right child
				this->rightChild = t;								// set current right child to new node
			}
		}

		BinaryTree<T> *getRightChild(){								// get right child
			return this->rightChild;								// return right child
		}

		BinaryTree<T> *getLeftChild(){								// get left child
			return this->leftChild;									// return left child
		}

		void setRootVal(T obj){										// set root's payload
			this->key = obj;										// set root's payload
		}

		T getRootVal(){												// get root's payload
			return this->key;										// return root's payload
		}

		// void preorder(vector<char_code>& cds, string& code){		// preorder traversal
		// 	std::cout << this->key << " ";							// print root
		// 	if (key.letter != '.'){
		// 		cds.emplace_back(char_code{key.letter, code});
		// 	}
		// 	if (this->leftChild != NULL){
		// 		code += "0" ;										// if left child is not null
		// 		this->leftChild->preorder(cds, code);				// preorder left child		
		// 		code = code.substr(0, code.length() - 1);
					
		// 	}
		// 	if (this->rightChild != NULL){	
		// 		code += "1" ;										// if right child is not null
		// 		this->rightChild->preorder(cds, code);				// preorder right child	
		// 		code = code.substr(0, code.length() - 1);
		// 	}
		// }

		void inorder(vector<char_code>& cds, string& code, int max){// inorder traversal
			if (this->key.frequency == max){
				code = "";
			}
			if (this->leftChild != NULL){
				code += "0" ;										// going left, add 0 to code
				this->leftChild->inorder(cds, code, max);			// inorder left child
				code = code.substr(0, code.length()-1);				// going up, remove end of current code string
			}
			if (key.letter != '*'){		
				cds.emplace_back(char_code{key.letter, code});
			}
			if (this->rightChild != NULL){
				code += "1" ;										// going right, add 1 to code
				this->rightChild->inorder(cds, code, max);			// inorder right child
				code = code.substr(0, code.length()-1);				// going up, remove end of current code string
			}													
		}

		// void postorder(vector<char_code>& cds, string& code){		// postorder traversal
		// 	if (this->leftChild != NULL){	
		// 		code += "0" ;								// if left child is not null
		// 		this->leftChild->postorder(cds, code);
		// 		code = code.substr(0, code.length() - 1);
				
		// 	}														// postorder left child
		// 	if (this->rightChild != NULL){		
		// 		code += "1" ;					// if right child is not null
		// 		this->rightChild->postorder(cds, code);
		// 		code = code.substr(0, code.length() - 1);	
		// 	}														// postorder right child
		// 	if (key.letter != '.'){
		// 		cds.emplace_back(char_code{key.letter, code});
		// 	}	
		// 	//std::cout << this->key << " ";							// print root
		// }

		void printTree(){
			printTree(this);
		}
		bool operator<(const BinaryTree<T>& other){
			return this->key < other.key;
		}
		bool operator>(const BinaryTree<T>& other){
			return this->key > other.key;
		}
		bool operator>=(const BinaryTree<T>& other){
			return this->key >= other.key;
		}
		bool operator<=(const BinaryTree<T>& other){
			return this->key <= other.key;
		}
		T& get_key(){
			return this->key;
		}  
};

template <typename T>
ostream& operator << (ostream& stream, BinaryTree<T>& tree)  {
	stream << tree.get_key();
	return stream;
}

#endif

