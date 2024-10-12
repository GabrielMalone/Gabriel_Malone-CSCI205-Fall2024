

#ifndef OPEN_HASH_TABLE_HPP
#define OPEN_HASH_TABLE_HPP

#include <string>
#include <iomanip>
#include <iostream>

using namespace std;
//--------------------------------------------------------------------------------------------------------
// OPEN HASHMAP CLASS
//--------------------------------------------------------------------------------------------------------
template<typename V>
class OpenHashTable{
	private:
		// Each element in the hash table is a HashNode
		// Each HashNode contains a key-value pair and a flag to indicate if it is deleted
		// The key is a string, and the value is of type V
		// If a HashNode is deleted, it should be skipped during searching. Why?
			// so that it is not filled with a value and stops a search for a key prematurely
		// The key is also stored along with the value in the HashNode. Why?
		//-----------------------------------------------------------------------------------------------
		// BUCKET STRUCTURE - for each position in the map
		//-----------------------------------------------------------------------------------------------
		struct HashNode {
			string key;
			V value;
			bool deleted;
			HashNode(){};					  // default constructor needed otherwise compiler complained
			HashNode() : key(""), value(V()), deleted(false) {}
			HashNode(string& k, V& v) : key(k), value(v), deleted(false) {}
		};

		// So that you can focus on the details of hash table implementation, we will
		// implement the hash table using a fixed size array instead of a vector
		// this will allow you to focus on the details of resizing
		HashNode* table;	// dynamically allocated array of HashNodes
		int size;			// number of key-value pairs in the hash table
		int capacity;		// number of slots in the hash table

		//-----------------------------------------------------------------------------------------------
		// HASH - 
		//-----------------------------------------------------------------------------------------------
		// the multiplying by a square (and never being zero, 
		// helped prevent a bunch of collisions happening near the start of every map
		unsigned long long hash(const string& key) {
			unsigned long long hash = 1 ;
			for (int i = 0 ; i < key.length(); i ++){
				hash += static_cast<unsigned long long>(key[i]) * (((i+1*13) * (i+1*61)));			
			}
			return hash % capacity;
		}

		//-----------------------------------------------------------------------------------------------
		// LOADFACTOR - helper function to determine load factor
		//-----------------------------------------------------------------------------------------------
		double loadFactor() {
			return this->size / this->capacity;
		}

		//-----------------------------------------------------------------------------------------------
		// RESIZE? - helper function to determine if we should resize
		//-----------------------------------------------------------------------------------------------
		bool should_resize() {
			double load_size = .75;
			if (loadFactor() > load_size) return true;
			return false;
		}

		//-----------------------------------------------------------------------------------------------
		// RESIZE 
		//-----------------------------------------------------------------------------------------------
		void resize(){ // rehash all key-value pairs  because new capacity == new modulus division number
			int old_capacity = capacity;									   // for iterating old table
			capacity = capacity + (capacity * .5);						// resize capacity to 50% larger,
			if (! is_prime(capacity)){								       // then find next prime number
				capacity = find_next_prime(capacity);
			}
			HashNode* new_table = HashNode[capacity];								  // set up new table		
			for (int i = 0 ; i < old_capacity ; i ++){ 
				HashNode h = this->table[i];							   // iterate through old buckets
				quadratic_probe_resize(h.key, h.value, new_table);  	// place hashnode in new location
				//linear_probe_resize();							  // other collision avoidance option
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
		//-----------------------------------------------------------------------------------------------
		// LINEAR PROBE - helper function to put key-value pairs into the hash table using linear probing
		//-----------------------------------------------------------------------------------------------
		void put_with_linear_probe(string& key, V& value){
			int cur_index = hash(key);
			while (this->table[cur_index] != NULL){
				cur_index ++;
			}
			this->table[cur_index].value = value;
			this->table[cur_index].key = key;
		}
		//-----------------------------------------------------------------------------------------------
		// LINEAR PROBE RESIZE - helper function to put key-value pairs into the hash table using linear 
		//-----------------------------------------------------------------------------------------------
		void linear_probe_resize(string& key, V& value, HashNode*& new_table){
			int cur_index = hash(key);
			while (new_table[cur_index] != NULL){
				cur_index ++;
			}
			new_table[cur_index].value = value;
			new_table[cur_index].key = key;
		}
		//-----------------------------------------------------------------------------------------------
		// QUADRATIC PROBE - helper function to put key-value pairs in hash table with quadratic probing
		//-----------------------------------------------------------------------------------------------
		void put_with_quadratic_probe(std::string& key, V& value){
			int cur_index = hash(key);
			int quadr_fact = 2;
			while (this->table[cur_index] != NULL){
				cur_index += (quadr_fact - 1) * (quadr_fact -1);
				quadr_fact ++;
			}
			this->table[cur_index].value = value;
			this->table[cur_index].key = key;			
		}
		//-----------------------------------------------------------------------------------------------
		// QUADRATIC PROBE RESIZE - helper function to put key-value pairs in hash table with quadratic
		//-----------------------------------------------------------------------------------------------
		void quadratic_probe_resize(string& key, V& value, HashNode*& new_table){
			int cur_index = hash(key);
			int quadr_fact = 2;
			while (new_table[cur_index] != NULL){
				cur_index += (quadr_fact - 1) * (quadr_fact -1);
				quadr_fact ++;
			}
			new_table[cur_index].value = value;
			new_table[cur_index].key = key;			
		}

	public:
		//-----------------------------------------------------------------------------------------------
		// OVERLOADED CONSTRUCTOR
		//-----------------------------------------------------------------------------------------------
		OpenHashTable(int capacity) : size(0), capacity(capacity){
			table = new HashNode[find_next_prime(capacity)];
		}
		//-----------------------------------------------------------------------------------------------
		// NO ARGUMENT CONSTRUCTOR
		//-----------------------------------------------------------------------------------------------
		OpenHashTable() : size(0), capacity(11){
			table = new HashNode[find_next_prime(capacity)];
		}		
		//-----------------------------------------------------------------------------------------------
		// DESTRUCTOR
		//-----------------------------------------------------------------------------------------------
		~OpenHashTable(){
			delete [] table;
		}	
		//-----------------------------------------------------------------------------------------------
		// PUT - place a key and a value into the map
		//-----------------------------------------------------------------------------------------------
		void put(string& key, V& value){
			if (! this->contains(key)){ 		    // check if the key being inserted is already present
				this->size ++;													  // increase size of map
				if (should_resize()){									 // check to see if resize needed
					resize();	
				}
				put_with_quadratic_probe(key, value);
				//put_with_linear_probe(key, value);	
			}
		}
		//-----------------------------------------------------------------------------------------------
		// REMOVE - remove key-value pair from hash table
		//-----------------------------------------------------------------------------------------------	
		bool remove(string& key){
			if (this->contains(key)){
				int cur_index = hash(key);
				HashNode current_bucket = this->table[cur_index];					 // find hashed index
				int quadr_fact = 2;
				while (current_bucket.key != key){				   // see if key is present at that index
					cur_index += (quadr_fact - 1) * (quadr_fact -1);
					quadr_fact ++;
					current_bucket = this->table[cur_index];				       // if not, look for it
				}
				current_bucket.deleted = true;									 // set bucket as deleted
			}
			return false;																 // nothing found
		}	
		//-----------------------------------------------------------------------------------------------
		// GET - get value associated with key
		//-----------------------------------------------------------------------------------------------	
		V get(string& key){
			if (this->contains(key)){
				int cur_index = hash(key);
				HashNode current_bucket = this->table[cur_index];					 // find hashed index
				int quadr_fact = 2;
				while (current_bucket.key != key){				   // see if key is present at that index
					cur_index += (quadr_fact - 1) * (quadr_fact -1);
					quadr_fact ++;
					current_bucket = this->table[cur_index];				       // if not, look for it
				}
				return current_bucket.value;											  // return value
			}
			throw out_of_range("KeyError");											   // if no key found
		}
		//-----------------------------------------------------------------------------------------------
		// CONTAINS - see if key exists in map
		//-----------------------------------------------------------------------------------------------
		bool contains(string& key){
			int cur_index = hash(key);
			HashNode current_bucket = this->table[cur_index];					     // find hashed index
			int quadr_fact = 2;
			while (cur_index < capacity){				  	       			// look until no buckets left
				current_bucket = this->table[cur_index];				      
				if (current_bucket.key == key){
					return true;
				}
				cur_index += (quadr_fact - 1) * (quadr_fact -1);
				quadr_fact ++;
			}
			return false;
		}
		//-----------------------------------------------------------------------------------------------
		// OVERLOADED [] 
		//-----------------------------------------------------------------------------------------------	
		V& operator[](string& key)	{
			return get(key);
		}	
		//-----------------------------------------------------------------------------------------------
		// HELPER METHODS
		//-----------------------------------------------------------------------------------------------	
		int m_size()	{return size;}			// return the number of key-value pairs in the hash table
		bool empty(){return size == 0;}								  // check if the hash table is empty
		//-----------------------------------------------------------------------------------------------
		void print() const {										// print the state of the current map
			string RESET = "\033[0m";                          				// ANSI escape code variables
			string YELLOW = "\033[33m";
			string BLUE = "\033[34m";
			for (int i = 0; i < this->capacity; ++i) {
				cout << "table[" << YELLOW << i << RESET << "]: ";
				if (table[i].length() == 0) cout << BLUE << "EMPTY" << RESET << endl; 	// is slot empty?
				else table[i].print();	
			}
		}
		//-----------------------------------------------------------------------------------------------
		int map_capacity(){return this->capacity;}					 // return the map's current capacity
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
	};
#endif
