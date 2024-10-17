#include <iostream>	// cout, cin
#include <fstream>	// ofstream and file output
#include <ctime>	// benchmarking
#include <iomanip>	// fixed display of double
#include <random>
#include "hash_tables/ClosedHashTable.hpp"
#include "hash_tables/OpenHashTable.hpp"
#include "backend/List.hpp"
#include "backend/ArrayList.hpp"


using namespace std;
void closed_hashtable_search(int, ClosedHashTable<int>&);
void open_hashtable_search(int, OpenHashTable<int>&);
void binary_search(int, A_List<int>&);
void linear_search(int, A_List<int>&);
void graph();
void benchmark(int);
void fillMaps(A_List<int>&,ClosedHashTable<int>&, OpenHashTable<int>&);

//-----------------------------------------------------------------------------------------------------------
// TEST VARIABLES
//-----------------------------------------------------------------------------------------------------------
int problem_size;
int num_experiments = 500;														// num experiements to run
int counts;
int key = 0;
//-----------------------------------------------------------------------------------------------------------
// TEST VARIABLES
//-----------------------------------------------------------------------------------------------------------


int main(){

	
	//--------------------------------------------------------------------------------------------------------
    // OUTPUT FILES
    //--------------------------------------------------------------------------------------------------------
	ofstream f1("linear_search.txt");						// record counts of computations into a file
	ofstream f2("binary_search.txt");						// record counts of computations into a file
	ofstream f3("closed_hashtable_search.txt");				// record counts of computations into a file
	ofstream f4("open_hashtable_search.txt");				// record counts of computations into a file

	//--------------------------------------------------------------------------------------------------------
    // SET UP MAPS
    //--------------------------------------------------------------------------------------------------------
	for (int i = 1 ; i < num_experiments ; i ++ ){
		problem_size = i * 10;

		ClosedHashTable<int>cht(num_experiments);										// maps for testing
		OpenHashTable<int>oht(num_experiments);											// maps for testing
		A_List<int>list;																// list for testing	
		fillMaps(list, cht, oht);	
																						// fill maps with data
		int front = list[0];
		int middle = list[list.length()/2];
		int end = list[list.length()-1];
		int not_found = -1;

		key = end;


		counts = 0;										
		// linear_search(key, list);	
		// f1 << problem_size << " " << counts << endl;				
		counts = 0;										
		binary_search(key, list);
		f2 << problem_size << " " << counts << endl;				
		counts = 0;										
		closed_hashtable_search(key, cht);	
		f3 << problem_size << " " << counts << endl;				
		counts = 0;
		open_hashtable_search(key, oht);	
		f4 << problem_size << " " << counts << endl;				
	}
	
	benchmark(key);
	graph();

	return 0;
}

//-------------------------------------------------------------------------------------------------------------
// TEST FUNCTIONS
//-------------------------------------------------------------------------------------------------------------
void fillMaps(A_List<int>&list, ClosedHashTable<int>&cht, OpenHashTable<int>&oht){
	for (int i = 0; i < problem_size; i ++){
		string key = to_string(i);
		cht.put(key, i);
		oht.put(key, i);
		list.insert(i, list.length());
	}
}

void linear_search(int key, A_List<int>& list){
	for(int i = 0; i < list.length(); ++i){					// iterate through array
		counts++;											// increment counts
		if(list[i] == key) return;							// if key is found return index
	}
}

void binary_search(int key, A_List<int>&list){
	int low		= 0;										// beginning index of current range
	int high	= list.length(); 							// ending index of current range
	bool found	= false;									// flag to indicate if key is found
	while (low <= high && !found){							// while range is valid and key not found
		++counts;											// increment counts
		int midpoint = (low + high) / 2;					// compute midpoint of current range
		if (list[midpoint] == key) return;
		if (key < list[midpoint]) high = midpoint - 1;		// if key is less than midpoint, search left
		else low = midpoint + 1;							// if key is greater than midpoint, search right
	}
}

void closed_hashtable_search(int key, ClosedHashTable<int>&cht){
	string key_str = to_string(key);
	try {
		cht.get(key_str);
		counts = cht.search_count();
	} catch (out_of_range){cout<<"error closed" <<endl;}
}
	
void open_hashtable_search(int key, OpenHashTable<int>&oht){
	string key_str = to_string(key);
	try {
		oht.get(key_str);
		counts = oht.search_count();
	} catch (out_of_range){cout<<"error open trying to get: " << key << endl;}
}

void graph() {
	int status = system("python3 backend/plot.py"); 
	if (status == -1)
	{
		cerr << "\npython script failed :[\n" << endl;
	} else {
		cout << "\n  graphs created successfully!\n" << endl;
		cout << "  all .txt data cleared\n" << endl;
	}
}

void benchmark(int key){
	ClosedHashTable<int>cht2(num_experiments);										// maps for testing
	OpenHashTable<int>oht2(num_experiments);											// maps for testing
	A_List<int>list2;																// list for testing	
	fillMaps(list2, cht2, oht2);	
	

	cout << "Benchmarking with problem size of " << problem_size << endl;

	counts = 0;
	// benchmarking linear search
	clock_t start = clock();															  // start clock
	linear_search(key, list2);											
	clock_t end = clock();																	// end clock
	double time = (double)(end - start) / CLOCKS_PER_SEC;								 // compute time
	cout << "Linear search time: " << fixed << time << endl;							   // print time
	cout << "Linear Search Comparisons: " << counts << endl << endl;					 // print counts

	counts = 0;																			 // reset counts

	start = clock();																	  // start clock
	binary_search(key, list2);										
	end = clock();																			// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;										 // compute time
	cout << "Binary search time: " << fixed << time << endl;							   // print time
	cout << "Binary Search Comparisons: " << counts << endl << endl;					 // print counts

	counts = 0;																			 // reset counts

	start = clock();																	  // start clock
	open_hashtable_search(key, oht2);										
	end = clock();																			// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;										 // compute time
	cout << "Open Hash search time: " << fixed << time << endl;							   // print time
	cout << "Open Hash Search Comparisons: " << counts << endl << endl;					  // print counts

	counts = 0;																			 // reset counts

	start = clock();																	  // start clock
	closed_hashtable_search(key, cht2);										
	end = clock();																			// end clock
	time = (double)(end - start) / CLOCKS_PER_SEC;										 // compute time
	cout << "Closed Hash search time: " << fixed << time << endl;						   // print time
	cout << "Closed Hash Search Comparisons: " << counts << endl << endl;				 // print counts

}