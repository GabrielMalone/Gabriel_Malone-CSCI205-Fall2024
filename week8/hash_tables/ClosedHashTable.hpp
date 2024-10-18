//--------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / HASHMAPS
//--------------------------------------------------------------------------------------------------------
#ifndef CLOSED_HASH_TABLE_HPP
#define CLOSED_HASH_TABLE_HPP

#include <iostream>
#include <string>
#include "../backend/List.hpp"	
#include "../backend/colors.hpp"

using namespace std;
//--------------------------------------------------------------------------------------------------------
// CLOSED HASHMAP CLASS
//--------------------------------------------------------------------------------------------------------
	// Each element in the hash table is a list of HashNodes (linked list)
	// Each HashNode contains a key-value pair
	// The key is a string, and the value is of type V
	// The key is also stored along with the value in the HashNode. Why?
		// ^ for constant time look up speed. the key be unique unique and can 
		// mathematically identify the location of the key/value pair quickly.
	// Why do we not need to track nodes as deleted? 
		// the relative position of a key/value pair is not relevant to how it is located in the array. 
//--------------------------------------------------------------------------------------------------------
template<typename V>
class ClosedHashTable {
	private:
		//-----------------------------------------------------------------------------------------------
		// BUCKET STRUCTURE - for each position in the map
		//-----------------------------------------------------------------------------------------------
		struct HashNode {
			string key;
			V value;
			HashNode(){};					  // default constructor needed otherwise compiler complained
			HashNode(const string& k, const V& v) : key(k), value(v){}
			bool operator == (const HashNode& rhs) {
				return this->key == rhs.key;       			// needed to see if current key exists in map
			}
			// overload the << operator so we can easily print HashNodes
			friend ostream& operator << (ostream& os, const HashNode& node) {
				os << node.key << ": " << node.value;
				return os;
			}
		};
		//-----------------------------------------------------------------------------------------------
		// CLASS VARS - The open hash tables are collections of lists of HashNodes
		//-----------------------------------------------------------------------------------------------
		List<HashNode>* table;								// dynamically allocated array of LinkedLists
		int size;										   // number of key-value pairs in the hash table
		int capacity;												 // number of slots in the hash table
		int resizes = 0;									      // number of times this map has resized
		int nc = 0;									// to count number of operations to complete a search											 					
		HashNode bracket_node;
		//-----------------------------------------------------------------------------------------------
		// HASH - 
		//-----------------------------------------------------------------------------------------------
		// the multiplying by a square (and never being zero, 
		// helped prevent a bunch of collisions happening near the start of every map
		int hash(const string& key) {
			int hash = 0 ;
			for (int i = 0 ; i < key.length(); i ++){
				hash += static_cast<int>(key[i]) * ((i+1*1223) * (i+1*61)) % capacity;			
			}
			return hash % capacity;
		}

		//-----------------------------------------------------------------------------------------------
		// LOADFACTOR - helper function to determine load factor
		//-----------------------------------------------------------------------------------------------
		double loadFactor() {
			return static_cast<double>(this->size) / static_cast<double>(this->capacity);
		}
		//-----------------------------------------------------------------------------------------------
		// RESIZE? - helper function to determine if we should resize
		//-----------------------------------------------------------------------------------------------
		bool should_resize() {
			double load_size = .5;
			if (loadFactor() > load_size) return true;
			return false;
		}
		//-----------------------------------------------------------------------------------------------
		// RESIZE 
		//-----------------------------------------------------------------------------------------------
		  // will need to rehash all key-value pairs  because new capacity == new modulus division number
		void resize() {
			resizes ++ ;
			int old_capacity = capacity;									   // for iterating old table
			capacity = capacity + (capacity * .5);						
			if (! is_prime(capacity)){								       // then find next prime number
				capacity = find_next_prime(capacity);
			}							
			List<HashNode>* new_table = new List<HashNode>[capacity];       // rehash all key-value pairs	
			for (int i = 0 ; i < old_capacity ; i ++){ 
				List<HashNode>& cb = this->table[i];					     // iterate to current bucket
				Node<HashNode>* n = cb.get_head();				   // get the head node of current bucket
				while (n != NULL){
					HashNode chn = n->data;							     // get the hashnode at this node
					string ck = chn.key;										   // get the current key
					int nhk = hash(ck);											       // rehash this key
					new_table[nhk].insert(chn);			// place the current hashnode in its new location
					n = n->next;
				} 
			}
			delete [] table; 													  // delete the old table
			table = new_table;											  // point old table at new table
		}
		//-----------------------------------------------------------------------------------------------
		// DETERMINE THE NEXT PRIME
		//-----------------------------------------------------------------------------------------------
		int find_next_prime(int n) {
			while (! is_prime(n)){
				n ++;						  // keep checking every integer after n to see if it's prime
			}
			return n;															// return the found prime
		}

	public:
		//-----------------------------------------------------------------------------------------------
		// OVERLOADED CONSTRUCTOR
		//-----------------------------------------------------------------------------------------------
		ClosedHashTable(int capacity) : size(0), capacity(capacity) {
			table = new List<HashNode>[find_next_prime(capacity)];
		}
		//-----------------------------------------------------------------------------------------------
		// NO ARGUMENT CONSTRUCTOR 
		//-----------------------------------------------------------------------------------------------
		ClosedHashTable() : size(0), capacity(11) {
			table = new List<HashNode>[find_next_prime(capacity)];
		}		
		//-----------------------------------------------------------------------------------------------
		// DESTRUCTOR
		//-----------------------------------------------------------------------------------------------
		~ClosedHashTable(){
			delete [] table;
		}	
		//-----------------------------------------------------------------------------------------------
		// PUT - place a key and a value into the map
		//-----------------------------------------------------------------------------------------------
		void put(string& key, V& value){
				this->size ++;													  // increase size of map
				if (should_resize()){									 // check to see if resize needed
				resize();	
				}
				this->table[hash(key)].insert(HashNode(key,value));	//place data in linked list at bucket
			}
		//-----------------------------------------------------------------------------------------------
		// GET - get value associated with key
		//-----------------------------------------------------------------------------------------------	
		V& get(string& key){
			nc = 1;																		   // N value
			List<HashNode>& current_bucket = this->table[hash(key)];			  // get bucket at hk
			Node<HashNode>* n = current_bucket.get_head();			   // get that bucket's head node
			while (n != NULL){			 // traverse the current linked list until matching key found
				if (n->data.key == key){
					return n->data.value;						      // return the value of that key
				}
				n = n->next;
				nc ++;
			}
			throw out_of_range("Key Error, Key Does Not Exist");				  // if no key found
		}	
		//-----------------------------------------------------------------------------------------------
		// REMOVE - remove key-value pair from hash table
		//-----------------------------------------------------------------------------------------------	 
		bool remove(string& key){
			if (contains(key)){
				List<HashNode>& current_bucket = this->table[hash(key)];			  // get bucket at hk
				Node<HashNode>* n = current_bucket.get_head();			   // get that bucket's head node
				while (n != NULL){			 // traverse the current linked list until matching key found
					if (n->data.key == key){			
						n->data.key = "";									  		  // remove that node
						current_bucket.remove(current_bucket.find(n->data));     // remove node from list
						this->size -- ;												// decrement map size
						return true;								 // return true for found and removed
					}
					n = n->next;
					nc ++;
				}
			}
			return false;																 // nothing found
		}	
		//-----------------------------------------------------------------------------------------------
		// CONTAINS - see if key exists in map
		//-----------------------------------------------------------------------------------------------	
		bool contains(string& key_in){
			nc = 1;
			List<HashNode>& current_bucket = this->table[hash(key_in)];			      // get bucket at hk
			Node<HashNode>* n = current_bucket.get_head();				   // get that bucket's head node
			while (n != NULL){			     // traverse the current linked list until matching key found
				nc ++ ;
				if (n->data.key == key_in){
					return true;
				}
				n = n->next;
			}
			return false;
		}
		//-----------------------------------------------------------------------------------------------
		// HELPER METHODS
		//-----------------------------------------------------------------------------------------------			
		int m_size() {return size;}				// return the number of key-value pairs in the hash table
		//-----------------------------------------------------------------------------------------------	
		bool empty(){return size == 0;}								  // check if the hash table is empty
		//-----------------------------------------------------------------------------------------------	
		void print() const {										// print the state of the current map
			for (int i = 0; i < this->capacity; ++i) {
				cout << "table[" << Colors::YELLOW << i << Colors::RESET << "]: ";
				if (table[i].length() == 0) cout << Colors::BLUE << "EMPTY" << Colors::RESET << endl; 
				else table[i].print();	
			}
		}
		//-----------------------------------------------------------------------------------------------
		int count_empty(){							   // return how many empty slots a map currently has
			int count = 0;
			for (int i = 0 ; i < this->capacity; i ++){
				if (table[i].length() == 0){
					count ++;
				}
			}
			return count;
		}
		//-----------------------------------------------------------------------------------------------
		int map_capacity(){return this->capacity;}					 // return the map's current capacity
		//-----------------------------------------------------------------------------------------------
		int count_full(){return this->capacity - count_empty();}      // return how many slots are filled
		//-----------------------------------------------------------------------------------------------
		int max_depth(){								 // find bucket with highest number of collisions
			int max = 0;											 // return the maximum depth recorded
			int count = 0;												// will reset each bucket checked
			for (int i = 0 ; i < this->capacity; i ++){			// iterate through the buckets in the map
				if (table[i].length() > 0){						 // if a bucket is not empty, check depth
					count = 0 ;									 // reset count before starting new count
					Node<HashNode>* n = table[i].get_head();		   	   // get that bucket's head node
					while (n != NULL){										 // traverse the current tree
						count ++ ;
						n = n->next;
					}
					if (count > max){								 // if current count new high, set it
						max = count;
					}
				}
			}
			return max;													 // return the max depth recorded
		}
		//-----------------------------------------------------------------------------------------------
		double avg_depth(){								  // find average number of collisions per bucket
			return static_cast<double>(this->size)/static_cast<double>(count_full()); 
		}
		//-----------------------------------------------------------------------------------------------
		// IS PRIME ? - helper function to determine if a number is prime
		//-----------------------------------------------------------------------------------------------
		bool is_prime(int n) {
			if (n <= 1) return false;
			if (n <= 3) return true;
			if (n % 2 == 0 || n % 3 == 0) return false;
			for (int i = 5; i * i <= n; i = i + 6)
				if (n % i == 0 || n % (i + 2) == 0)
					return false;
			return true;
		}
		//-----------------------------------------------------------------------------------------------
		int times_resized(){									   // how many times has this map resized
			return this->resizes;
		}
		//-----------------------------------------------------------------------------------------------
		int search_count(){									// return how many operations the search took
			return this->nc;
		}
		//-----------------------------------------------------------------------------------------------
		// OVERLOADED [] and = for []= assignments in map
		//-----------------------------------------------------------------------------------------------	
		V& operator [] (const string& key_in) {
			this->size ++;	
			if (should_resize()){									 	// check to see if resize needed
				resize();	
			}
			this->bracket_node.key = key_in;
			this->table[hash(key_in)].insert(this->bracket_node);
			return this->bracket_node.value;
				throw out_of_range("KeyGetError - Key Does Not Exist");				  // if no key found
			}
			V& operator = (V& val) {											
			return val;
		}

};		
#endif