
//--------------------------------------------------------------------------------------------------------
// Gabriel Malone / CSCI 205 / WEEK 8 / HASHMAPS
//--------------------------------------------------------------------------------------------------------
#ifndef OPEN_HASH_TABLE_HPP
#define OPEN_HASH_TABLE_HPP

#include <string>
#include <iomanip>
#include <iostream>
#include "../backend/colors.hpp"
#include "../backend/List.hpp"

using namespace std;
//--------------------------------------------------------------------------------------------------------
// OPEN HASHMAP CLASS
//--------------------------------------------------------------------------------------------------------
template<typename V>
class OpenHashTable{
	public:
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
			bool deleted = false;
			string key;
			V value;
			HashNode(){
				key = "";
			}
			HashNode(string& k, V& v){
				key = k;
				value = v;
			}
		};

		// So that you can focus on the details of hash table implementation, we will
		// implement the hash table using a fixed size array instead of a vector
		// this will allow you to focus on the details of resizing
		HashNode* table;	// dynamically allocated array of HashNodes
		int size = 0;			// number of key-value pairs in the hash table
		int capacity = 0;		// number of slots in the hash table
		int resizes = 0;
		int collisions_avoided = 0;
		int nc = 0;
		V val_assign;

		//-----------------------------------------------------------------------------------------------
		// HASH - 
		//-----------------------------------------------------------------------------------------------
		// the multiplying by a square (and never being zero, 
		// helped prevent a bunch of collisions happening near the start of every map
		int hash(const string& key) {
			int hash = 0 ;
			for (int i = 0 ; i < (int)key.length(); i ++){
				hash += static_cast<int>(key[i]) * ((i+1*1223) * (i+1*7));			
			}
			return hash % this->capacity;
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
		void resize(){ 				
			this->resizes ++;																    // track
			int old_capacity = this->capacity; 							 // for looping through og table
			this->capacity = find_next_prime(this->capacity + (this->capacity * .5)); 	 // set new size
			HashNode* new_table = new HashNode[this->capacity];					     // create new table
			for (int i = 0 ; i < old_capacity ; i ++){						   // loop through old table
				if (this->table[i].key != "") 		   							    // get the live keys
					put_with_linear_probe(this->table[i].key,this->table[i].value, new_table); // rehash 
			}
			delete[] this->table;														 // clean up mem		     						
			this->table = new_table;													 // assign table		 
		}
		//-----------------------------------------------------------------------------------------------
		// QUADRATIC PROBE - helper function to put key-value pairs in hash table with quadratic probing
		//-----------------------------------------------------------------------------------------------
		void put_with_linear_probe(const std::string& key_in, V& value_in, HashNode* new_table){
			if (key_in != ""){															// validity check			
				int i = 0;													  // to prevent infinite loop
				int quadratic = 0;										   // value for quadratic probing
				int cur_index = hash(key_in);								              // hash the key
				int og_hash = cur_index;									  // store this as a constant
				while (i < capacity ){							 // can iterate every bucket if necessary
					if (new_table[cur_index].key == key_in){	               // check if updating a key
						new_table[cur_index].value = value_in;
						return;
					}
					if (new_table[cur_index].key == ""){			// otherwise place key in empty bucket
						new_table[cur_index].key = key_in;
						new_table[cur_index].value = value_in;
						return;
					}
					cur_index = (og_hash +  ((quadratic) * (quadratic))) % capacity; // jump quadratically
					quadratic ++ ;
					i ++ ;
				}
			}
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
		OpenHashTable(int capacity){
			this->capacity = capacity;
			this->size = 0;
			table = new HashNode[find_next_prime(capacity)];
		}
		//-----------------------------------------------------------------------------------------------
		// NO ARGUMENT CONSTRUCTOR
		//-----------------------------------------------------------------------------------------------
		OpenHashTable() : size(0), capacity(11){
			this->capacity = capacity;
			this->size = 0;
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
			this->size ++;	
			if (should_resize()){									 	// check to see if resize needed
				resize();	
			}
			put_with_linear_probe(key, value, this->table);
		}
		//-----------------------------------------------------------------------------------------------
		// LOADFACTOR - helper function to determine load factor
		//-----------------------------------------------------------------------------------------------
		double loadFactor() {
			return static_cast<double>(this->size) / static_cast<double>(this->capacity);
		}
		//-----------------------------------------------------------------------------------------------
		// REMOVE - remove key-value pair from hash table
		//-----------------------------------------------------------------------------------------------	
		bool remove(string& key_in){
			int cur_index = hash(key_in);						   // see if key is present at that index
			int i = 0;
			int quadratic = 0;
			int og_hash = cur_index;
			while (i < capacity){
				if (table[cur_index].key == key_in){
					table[cur_index].key = "";							    // when found, set as deleted
					this->size -- ;	
					return (true);
													
				}		   
				cur_index = (og_hash +  ((quadratic) * (quadratic))) % capacity;
				quadratic ++ ;
				i ++;
			}
			throw out_of_range("KeyError - Key Does Not Exist");				      // if no key found
		}	
		//-----------------------------------------------------------------------------------------------
		// GET - get value associated with key
		//-----------------------------------------------------------------------------------------------	
		V& get(const string& key_in){
			this->nc = 1;															     // track N value
			int cur_index = hash(key_in);												// get hash index
			int i  = 0;
			int quadratic = 0;
			int og_hash = cur_index;								
			while (i < this->capacity){								   
				if (this->table[cur_index].key == key_in){			   // if key is present at that index	
					return this->table[cur_index].value;				// return reference to that value
				}								
				cur_index = (og_hash +  ((quadratic) * (quadratic))) % capacity;
				quadratic ++ ;
				i ++;
				this->nc ++ ;							
			}
			throw out_of_range("KeyGetError - Key Does Not Exist");					  // if no key found
		}
		//-----------------------------------------------------------------------------------------------
		// CONTAINS - see if key exists in map, 
		//-----------------------------------------------------------------------------------------------
		bool contains(const string& key_in){ 							
			int cur_index = hash(key_in);
			int i  = 0;	
			int quadratic = 0;
			int og_hash = cur_index;
			this->nc = 1;
			while (i < capacity){	
				if (table[cur_index].key == key_in){
					return true;
				}				
				cur_index = (og_hash +  ((quadratic) * (quadratic))) % capacity;
				quadratic ++ ;
				i ++;	
				this->nc ++;
			}
			return false;								 
		}
		//-----------------------------------------------------------------------------------------------
		// OVERLOADED [] and = for []= assignments in map
		//-----------------------------------------------------------------------------------------------	
		V& operator [] (const string& key_in) {
			this->size ++;	
			if (should_resize()){									 	 // check to see if resize needed
				resize();	
				}
				int i = 0;
				int quadratic = 0;
				int cur_index = hash(key_in);
				int og_hash = cur_index;
				while (i < capacity ){
					if (this->table[cur_index].key == key_in){
						return this->table[cur_index].value; //  update  - return reference to table slot
		
					}
					if (this->table[cur_index].key == ""){
						this->table[cur_index].key = key_in;
						return this->table[cur_index].value;
					}
					cur_index = (og_hash +  ((quadratic) * (quadratic))) % capacity;
					quadratic ++ ;
					i ++ ;
				}
				throw out_of_range("KeyGetError - Key Does Not Exist");				    // if no key found
			}
		
		V& operator = (V& val) {											
			return val;
		}

		//-----------------------------------------------------------------------------------------------
		// HELPER METHODS
		//-----------------------------------------------------------------------------------------------	
		int m_size()	{return size;}			// return the number of key-value pairs in the hash table
		bool empty(){return size == 0;}								  // check if the hash table is empty
		//-----------------------------------------------------------------------------------------------
		void print() const {										// print the state of the current map
			for (int i = 0; i < capacity; ++i) {
				cout << "table[" 
					 << Colors::YELLOW 
					 << i << Colors::RESET 
					 << "]: ";
				if (table[i].key == "") {
					cout << Colors::BLUE 
						 << "EMPTY" 
						 << Colors::RESET 
						 << endl; 
				}
				else{
					cout << Colors::GREEN 
						 << table[i].key 
						 << Colors::RESET
						 << ": " 
						 << table[i].value 
						 << endl;	
				} 
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
		int times_resized(){									   // how many times has this map resized
			return this->resizes;
		}
		//-----------------------------------------------------------------------------------------------
		int count_empty(){							   // return how many empty slots a map currently has
			int count = 0;
			for (int i = 0 ; i < this->capacity; i ++){
				if (table[i].key == ""){
					count ++;
				}
			}
			return count;
		}
		//-----------------------------------------------------------------------------------------------
		int count_full(){return this->capacity - count_empty();}      // return how many slots are filled
		//-----------------------------------------------------------------------------------------------
		int collisions_avoid(){return this->collisions_avoided;}      // return how many slots are filled
		//-----------------------------------------------------------------------------------------------
		int search_count(){return this->nc;}			   // return time complexity of search operations
		//-----------------------------------------------------------------------------------------------
		void reset_count(){this->nc = 0;}
	};
#endif