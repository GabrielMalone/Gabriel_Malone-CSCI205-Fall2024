#ifndef MIN_HEAP
#define MIN_HEAP


#include <iostream>
#include <vector>
#include "huffman.hpp"

template <typename T>
class MinHeap {

	public:
		// Templated vector. Instances of T should have comparison operators defined
		std::vector<T> heap;										// vector to store heap elements

		// Build a min heap from an unordered array
		void heapify() {
			for (int i = heap.size() / 2; i >= 1; i--)				// for each element from the middle to the beginning
				sift_down(i);										// move the element down the tree to maintain the max heap property
		}

		// Move an element up the tree to maintain the max heap property
		void sift_up(int index) {
			while (index > 1) {										// while not at root
				int parent = index / 2;								// get parent index
				if (heap[index] >= heap[parent]) break;				// if element is less than or = to parent, break
				std::swap(heap[index], heap[parent]);				// swap element and parent
				index = parent;										// set index to parent
			}
		}

		// Move an element down the tree to maintain the min heap property
		// O(log n)
		void sift_down(int index) {
			int leftChild   = 2 * index;							// get left child index
			int rightChild  = 2 * index + 1;						// get right child index
			int smallest     = index;								// set smallest to index

			// find the smallest child
			if (leftChild < heap.size() && heap[leftChild] < heap[smallest])	// if left child is less than smallest
				smallest = leftChild;											// set smallest to left child

			if (rightChild < heap.size() && heap[rightChild] < heap[smallest])	// if right child is less than smallest
				smallest = rightChild;											// set smallest to right child

			if (smallest != index) {								// if smallest is at index
				std::swap(heap[index], heap[smallest]);				// swap element and smallest
				sift_down(smallest);								// recursively sift down largest
			}
		}

		// Get the height of the tree
		int height() {
			return log2(heap.size() - 1);							// height of heap is log2(n) where n is the number of elements
		}

		// Get the log base 2 of an integer
		// O(log n)
		int log2(int x) {
			int ans = 0;											// log base 2 of 0 is 0
			while (x >>= 1) ans++;									// shift bits right (divide by 2) until x is 0
			return ans;												// return number of shifts (division by 2 operations)
		}

	public:
		// Default constructor with empty heap
		MinHeap() {}

		// Constructor to build a max heap from an array
		MinHeap(const std::vector<T>& array) {
			heap.push_back(T()); 									// add dummy element at index 0 to make math easier
			heap.insert(heap.end(), array.begin(), array.end());	// insert elements from array
			heapify();												// build heap
		}

		// Insert an element into the max heap
		void insert(T value) {
			heap.push_back(value);									// add element to end of heap
			sift_up(heap.size() - 1);								// move element up the tree to maintain min heap property
		}

		// Remove and return the minimum element from the min heap
		// sift_down is O(log n)
		T extract_min() {											// remove min element
			if (empty()) throw std::runtime_error("Heap is empty");	// throw exception if heap is empty
			T min	= heap[1];										// get min element
			heap[1] = heap.back();									// set root to last element
			heap.pop_back();										// remove last element
			sift_down(1);											// move new root down the tree to maintain min heap property
			return min;												// return min element
		}

		// Get the maximum element without removing it
		// O(1)
		T get_min() const {
			if (empty()) throw std::runtime_error("Heap is empty");	// throw exception if heap is empty
			return heap[1];											// return min element
		}

		// Check if the max heap is empty
		// O(1)
		bool empty() const {
			return heap.size() < 1;								// return true if heap size is 0
		}
	
		// Print the heap as a list
		void print_heap() {
			cout << "----------------------------" << endl;
			cout << "          Heap Vector" << endl;
			cout << " ----------------------------" << endl << " ";
			for (int i = 1; i < heap.size(); i++)					// for each element
				std::cout << i << " = " << heap[i] << " ";			// print element
			std::cout << std::endl;									// new line
		}

		// print heap as tree. This is just for illustration.
		// For best results set T as int and keep numbers to two digits
			void print_tree() {
			if (empty()) {
				std::cout << "Heap is empty." << std::endl;
				return;
			}

			int h				= height();								// height of heap
			int maxLevelSize	= 1 << h;								// max nodes at any level
			int levelSize		= 1;									// nodes at current level

			for (int level = 0; level <= h; level++) {					// for each level
				int padding = maxLevelSize / levelSize;					// padding between nodes
				for (int i = 0; i < levelSize; i++) {					// for each node
					for (int j = 0; j < padding; j++) std::cout << "  ";// print padding
					int index = (1 << level) + i;						// get index of node
					if (index < heap.size()) std::cout << heap[index];	// print node
					else std::cout << " ";								// print space
					if (i < levelSize - 1)								// print padding between nodes on same level
						for (int j = 0; j < padding-1; j++)
							std::cout << "  ";
				}
				std::cout << "\n";										// new line
				levelSize *= 2;											// next level has twice as many nodes
			}
		}
		
};

#endif