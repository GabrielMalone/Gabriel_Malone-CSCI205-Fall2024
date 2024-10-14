#include <iostream>	// cout, cin
#include <fstream>	// ofstream and file output
#include <ctime>	// benchmarking
#include <iomanip>	// fixed display of double
#include <random>
#include "hash_tables/ClosedHashTable.hpp"
#include "hash_tables/OpenHashTable.hpp"

using namespace std;

// function prototypes
int binary_search(int *, int, int, int &);
int linear_search(int *, int, int, int &);
int closed_hashtable_search(int, int &, ClosedHashTable<int>&);
int open_hashtable_search(int, int &, OpenHashTable<int>&);
void fill_array(int *, int);
void benchmark(int);



int main(){

	random_device rd;                                 
	mt19937 gen(rd());
	          
	int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // initial array

	ofstream f1("linear_search.txt");	// record counts of computations into a file
	ofstream f2("binary_search.txt");	// record counts of computations into a file
	ofstream f3("closed_hashtable_search.txt");// record counts of computations into a file
	ofstream f4("open_hashtable_search.txt");// record counts of computations into a file

	int counts 	= 0;					// counts of computations, used as a refernce parameter to functions
	int index 	= 0;					// index of key in array
	int size 	= 0;					// problem size

	// execute 100 times with increasing problem size
	for (int i = 1; i < 1000; ++i){
		// allocate and fill array  
		size = i*10;						// problem size
		uniform_int_distribution<> rand(1, size-1);   
		int *array = new int[size];		// allocate array with size of N
		fill_array(array, size);			// fill array with values 1 to N
		int rand_key = size; 
		ClosedHashTable<int>cht(size);						// create a Closed HashTable of size of array
		for (int i = 0 ; i < size ; i ++){					// fill table with key, value pairs 
			string int_str = to_string(array[i]);			// (key being string of the int, value being that int)
			cht.put(int_str, i);
		}
		OpenHashTable<int>oht(size);						// create a Closed HashTable of size of array
		for (int i = 0 ; i < size ; i ++){					// fill table with key, value pairs 
			string int_str = to_string(array[i]);			// (key being string of the int, value being that int)
			oht.put(int_str, i);
		}
		// call functions with search key. 
		// Change 3rd parameter to -1 to test worst case
		// Change 3rd parameter to N/2 to test average case
		// Change 3rd parameter to 1 to test best case
		counts = 0;										// reset counts
		index = linear_search(array, size, rand_key, counts);	// linear search for -1 in array
		f1 << size << " " << counts << endl;				// record counts to file
		counts = 0;										// reset counts
		index = binary_search(array, size, rand_key, counts);	// binary search for -1 in array
		f2 << size << " " << counts << endl;				// record counts to file
		counts = 0;										// reset counts
		closed_hashtable_search(rand_key, counts, cht);	// binary search for -1 in array
		f3 << size << " " << counts << endl;				// record counts to file
		open_hashtable_search(rand_key, counts, oht);	// binary search for -1 in array
		f4 << size << " " << counts << endl;				// record counts to file
		delete[]  array;	// deallocate array used in this iteration
	}

	// benchmarking
	benchmark(10000000);	// benchmark linear and binary search with problem size of 1000
	return 0;
}

// fill array with values 1 to size
void fill_array(int *array, int size){
	for(int i = 0; i < size; ++i)
		array[i] = i + 1;
}

// perform linear search on array. Should be O(N)
// linear search does not require a sorted array
int linear_search(int *array, int size, int key, int &counts){
	for(int i = 0; i < size; ++i){		// iterate through array
		counts++;						// increment counts
		if(array[i] == key) return i;	// if key is found return index
	}
	return -1;							// key not found in array
}

// perform binary search on array should be O(logN)
// binary search requires a sorted array
int binary_search(int *array, int size, int key, int &counts){
	int index	= -1;		// index of search key in array
	int low		= 0;		// beginning index of current range
	int high	= size - 1; // ending index of current range
	bool found	= false;	// flag to indicate if key is found

	while (low <= high && !found){						// while range is valid and key not found
		++counts;										// increment counts
		int midpoint = (low + high) / 2;				// compute midpoint of current range
		if (array[midpoint] == key) return midpoint;	// if key is found return index
		if (key < array[midpoint]) high = midpoint - 1;	// if key is less than midpoint, search left
		else low = midpoint + 1;						// if key is greater than midpoint, search right
	}
	return index;
}

int closed_hashtable_search(int key, int &counts, ClosedHashTable<int>& cht){
	string key_str = to_string(key);
	try {
		return cht.get(key_str);
	} catch (error_code){
		return -1;
	}
	counts = cht.search_count();
}

int open_hashtable_search(int key, int &counts, OpenHashTable<int>& oht){
	string key_str = to_string(key);
	try {
		return oht.get(key_str);
	} catch (error_code){
		return -1;
	}
	counts = oht.search_count();
}

void benchmark(int size){
	int* array = new int[size];								// allocate array with size of N
	fill_array(array, size);									// fill array with values 1 to N
	int counts = 0;
	ClosedHashTable<int>cht2(size);
	for (int i = 0 ; i < size ; i ++){					// fill table with key, value pairs 
		string int_str = to_string(array[i]);			// (key being string of the int, value being that int)
		cht2.put(int_str, i);
	}
	cout << "Benchmarking with problem size of " << size << endl;

	// benchmarking linear search
	clock_t start = clock();								// start clock
	linear_search(array, size, size, counts);					// linear search for -1 in array
	clock_t end = clock();									// end clock
	double time = (double)(end - start) / CLOCKS_PER_SEC;	// compute time
	cout << "Linear search time: " << fixed << time << endl;			// print time
	cout << "Linear Search Comparisons: " << counts << endl << endl;	// print counts

	counts = 0;												// reset counts

	// benchmarking binary search
	start = clock();										// start clock
	binary_search(array, size, size, counts);					// binary search for -1 in array
	end = clock();											// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;			// compute time
	cout << "Binary search time: " << fixed << time << endl;// print time
	cout << "Binary Search Comparisons: " << counts << endl;// print counts

	counts = 0;												// reset counts

	//benchmarking binary search
	start = clock();										// start clock
	closed_hashtable_search(size, counts, cht2);			// closed_hashtable_search for -1 in array
	end = clock();											// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;			// compute time
	cout << "closed_hash_table search time: " << fixed << time << endl;// print time
	cout << "closed_hash_table Search Comparisons: " << counts << endl;// print counts

	delete[] array;											// deallocate array
}
