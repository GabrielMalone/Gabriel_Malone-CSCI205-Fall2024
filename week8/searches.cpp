#include <iostream>	// cout, cin
#include <fstream>	// ofstream and file output
#include <ctime>	// benchmarking
#include <iomanip>	// fixed display of double
#include "ClosedHashTable.hpp"

using namespace std;

// function prototypes
int binary_search(int *, int, int, int &);
int linear_search(int *, int, int, int &);
int closed_hashtable_search(int *, int, int, int &);
void fill_array(int *, int);
void benchmark(int);

int main(){
	int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}; // initial array

	ofstream f1("linear_search.txt");	// record counts of computations into a file
	ofstream f2("binary_search.txt");	// record counts of computations into a file
	ofstream f3("hashtable_search.txt");// record counts of computations into a file

	int counts 	= 0;					// counts of computations, used as a refernce parameter to functions
	int index 	= 0;					// index of key in array
	int N 		= 0;					// problem size

	// execute 100 times with increasing problem size
	for (int i = 1; i < 100; ++i){
		// allocate and fill array
		N = i*100;						// problem size
		int *array = new int[N];		// allocate array with size of N
		fill_array(array, N);			// fill array with values 1 to N

		// call functions with search key. 
		// Change 3rd parameter to -1 to test worst case
		// Change 3rd parameter to N/2 to test average case
		// Change 3rd parameter to 1 to test best case
		counts = 0;										// reset counts
		index = linear_search(array, N, -1, counts);	// linear search for -1 in array
		f1 << N << " " << counts << endl;				// record counts to file
		counts = 0;										// reset counts
		index = binary_search(array, N, -1, counts);	// binary search for -1 in array
		f2 << N << " " << counts << endl;				// record counts to file
		counts = 0;										// reset counts
		index = closed_hashtable_search(array, N, -1, counts);	// binary search for -1 in array
		f3 << N << " " << counts << endl;				// record counts to file
		delete[]  array;	// deallocate array used in this iteration
	}

	// benchmarking
	benchmark(100000);	// benchmark linear and binary search with problem size of 1000
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

int closed_hashtable_search(int *array, int size, int key, int &counts){
	string key_str = to_string(key);
	ClosedHashTable<int>cht(size);						// create a Closed HashTable of size of array
	for (int i = 0 ; i < size ; i ++){					// fill table with key, value pairs 
		string int_str = to_string(array[i]);			// (key being string of the int, value being that int)
		cht.put(int_str, i);
	}
	return cht[key_str];
}

void benchmark(int N){
	int* array = new int[N];								// allocate array with size of N
	fill_array(array, N);									// fill array with values 1 to N
	int counts = 0;

	cout << "Benchmarking with problem size of " << N << endl;

	// benchmarking linear search
	clock_t start = clock();								// start clock
	linear_search(array, N, -1, counts);					// linear search for -1 in array
	clock_t end = clock();									// end clock
	double time = (double)(end - start) / CLOCKS_PER_SEC;	// compute time
	cout << "Linear search time: " << fixed << time << endl;			// print time
	cout << "Linear Search Comparisons: " << counts << endl << endl;	// print counts

	counts = 0;												// reset counts

	// benchmarking binary search
	start = clock();										// start clock
	binary_search(array, N, -1, counts);					// binary search for -1 in array
	end = clock();											// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;			// compute time
	cout << "Binary search time: " << fixed << time << endl;// print time
	cout << "Binary Search Comparisons: " << counts << endl;// print counts

	counts = 0;												// reset counts

	// benchmarking binary search
	start = clock();										// start clock
	closed_hashtable_search(array, N, -1, counts);			// closed_hashtable_search for -1 in array
	end = clock();											// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;			// compute time
	cout << "Binary search time: " << fixed << time << endl;// print time
	cout << "Binary Search Comparisons: " << counts << endl;// print counts

	delete[] array;											// deallocate array
}
