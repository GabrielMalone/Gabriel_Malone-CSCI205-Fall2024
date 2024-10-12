/*
Open Hash Table: A key is NOT ALWAYS stored in the bucket it is hashed to.
Collisions are dealt with by searching for another empty buckets within the hash table array itself.

	0:
	1: ①
	2: ②
	3: ②
	4: ②
	5: ④
	6:
	7: ⑦
	8: ⑦
	9: ⑨ 
*/

#ifndef OPEN_HASH_TABLE_HPP
#define OPEN_HASH_TABLE_HPP

#include <string>
#include <iomanip>
#include <iostream>

template<typename V>
class OpenHashTable{
	private:
		// Each element in the hash table is a HashNode
		// Each HashNode contains a key-value pair and a flag to indicate if it is deleted
		// The key is a string, and the value is of type V
		// If a HashNode is deleted, it should be skipped during searching. Why?
		// The key is also stored along with the value in the HashNode. Why?
		struct HashNode {
			std::string key;
			V value;
			bool deleted;
			HashNode() : key(""), value(V()), deleted(false) {}
			HashNode(std::string& k, V& v) : key(k), value(v), deleted(false) {}
		};

		// So that you can focus on the details of hash table implementation, we will
		// implement the hash table using a fixed size array instead of a vector
		// this will allow you to focus on the details of resizing
		HashNode* table;	// dynamically allocated array of HashNodes
		int size;			// number of key-value pairs in the hash table
		int capacity;		// number of slots in the hash table

		// helper function to compute hash value
		int hash(std::string key) {
			// TO DO
			// You will be experimenting here with varous hashing approaches
			// You will be asked to report on your findings
			// Feel free to create separate functions for each hash implementation
		}

		// helper function to determine load factor
		double loadFactor() {
			// TO DO
			// You will be experimenting here with varous load factors
			// You will be asked to report on your findings
		}

		// helper function to determine if we should resize
		bool should_resize() {
			// TO DO
		}

		// helper function to resize the table
		void resize() {
			// TO DO
			// resize capacity to 50% larger, then find next prime number
			// rehash and put all key-value pairs. Why is this necessary?
			// clean up memory from old table
		}

		// helper function to determine if a number is prime
		bool is_prime(int n) {
			if (n <= 1) return false;
			if (n <= 3) return true;
			if (n % 2 == 0 || n % 3 == 0) return false;
			for (int i = 5; i * i <= n; i = i + 6)
				if (n % i == 0 || n % (i + 2) == 0)
					return false;
			return true;
		}

		// helper function to find the next prime number
		int find_next_prime(int n) {
			// TO DO
		}

		// helper function to put key-value pairs into the hash table using linear probing
		void put_with_linear_probe(std::string& key, V& value)	{/* TO DO */}

		// helper function to put key-value pairs into the hash table using quadratic probing
		void put_with_quadratic_probe(std::string& key, V& value){/* TO DO */}

	public:
		OpenHashTable(int capacity) : 
						size(0), 
						capacity(capacity)	{/*TO DO*/}	// constructor
		~OpenHashTable()					{/*TO DO*/}	// destructor

		void put(std::string& key, V& value){/*TO DO*/}	// insert key-value pair into the hash table using a put-helper
		bool remove(std::string& key)		{/*TO DO*/}	// remove key-value pair from the hash table
		V get(std::string& key)				{/*TO DO*/}	// get value associated with key
		bool contains(std::string& key)		{/*TO DO*/}	// check if key is in the hash table
		void operator[](std::string& key)	{/*TO DO*/}	// overload the [] operator to access elements in hash table

		int size()	{return size;}			// return the number of key-value pairs in the hash table
		bool empty(){return size == 0;}		// check if the hash table is empty

		// print out all the key-value pairs in the hash table
		// use this function to help you debug your code
		void print() {
			for (int i = 0; i < capacity; i++) {
				std::cout << "table[ ";
				if (table[i].deleted)
					std::cout << i << " ]\t= DELETED" << std::endl; 
				else if (table[i].key != "")
					std::cout << table[i].key << " ]\t= " << table[i].value << std::endl;
				else 
				 	std::cout << i << " ]\t= EMPTY" << std::endl;
			}
		}
	};
#endif
