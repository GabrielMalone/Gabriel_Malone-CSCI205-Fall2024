#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

#include <iostream>
#include <cstdlib>
#include "char_code.hpp"
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
					std::string spaces(spacing * level + 2, ' ');						// determine spacing
					std::cout << spaces << branch << prefix << root->key << std::endl;	// print node
				}

				if (root->leftChild || root->rightChild) {									// if node has children
					printTree(root->leftChild, level + 2, "L: ", spacing);					// print left child
					printTree(root->rightChild, level + 2, "R: ", spacing);					// print right child
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
		// 	if (this->leftChild != NULL){							// if left child is not null
		// 		delete this->leftChild;								// delete left child
		// 		this->leftChild = nullptr;
		// 	}
		// 	if (this->rightChild != NULL){							// if right child is not null
		// 		delete this->rightChild;							// delete right child
		// 		this->rightChild = nullptr;
		// 	}
		// }

		void insertLeft(BinaryTree<T>& newNode){						// insert left child
			if (this->leftChild == NULL)							// if left child is null
				this->leftChild = new BinaryTree<T>(newNode);		// create new node
			else {													// left child is not null
				BinaryTree<T> *t = new BinaryTree<T>(newNode);		// create new node
				t->leftChild = this->leftChild;						// set new node's left child to current left child
				this->leftChild = t;								// set current left child to new node
			}
		}

		void insertRight(BinaryTree<T>& newNode){					// insert right child
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
			return this->leftChild;															
		}

		void setRootVal(T obj){										// set root's payload
			this->key = obj;										// set root's payload
		}

		T getRootVal(){												// get root's payload
			return this->key;										// return root's payload
		}

		void inorder(vector<char_code>& cds, string& code, int max){// inorder traversal
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

		void inflate(string& decoded_str, string& huff_code, int steps){// inorder traversal
			string current_direction = huff_code.substr(0,1);
			if (current_direction == "0" && this->leftChild!=NULL){
				huff_code= huff_code.substr(1,huff_code.length());
				this->leftChild->inflate(decoded_str, huff_code, steps);
			}
			if (key.letter != '*'){
				string c = "";
				c += key.letter;		
				decoded_str += c;
			}	
			if (current_direction == "1" && this->rightChild!=NULL){
				steps ++ ;
				huff_code= huff_code.substr(1,huff_code.length());
				this->rightChild->inflate(decoded_str, huff_code, steps);
			}												
		}
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