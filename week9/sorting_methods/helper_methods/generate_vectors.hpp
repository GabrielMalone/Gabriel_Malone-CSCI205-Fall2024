#ifndef VECTORGENERATOR
#define VECTORGENERATOR

#include <random>
#include "../../backend/List.hpp"

using namespace std;

//------------------------------------------------------------------------------------
//  generates a random vector of size "size" with type "type"
//  type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially 
//------------------------------------------------------------------------------------
void generate_vector(int size, char type, std::vector<int>& temp, int range){
    random_device rd;                // random number generator for random val assignment
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1,  size); // range from 0 to 100 for the rnadom value
	List<int> used;
    int val = 0;
    int step = 0;
	switch (type){
		case 'a': // ascending
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			break;
		case 'd': // descending
			for(int i = 0; i < size; i++)
				temp[i] = size - i;
			break;
		case 'r': // random
            val = 0;
			step = 0;	
			while(step < range){			// while not 100 #s found yet
				val = dist(gen);			// get random number
				if (used.find(val) == -1){	// if number hasn't been used yet
					temp[step] = val;		// place in array
					used.insert(val);		// save that value for checking
					step ++ ;				// keep track of how many numbers found
				}
			}
			break;
		case 'p': // partially sorted
			for(int i = 0; i < size; i++)
				temp[i] = i + 1;
			// swap every 5th item
			for (size_t i = 4; i < temp.size(); i += 5) 
				swap(temp[i], temp[i - 4]);
	}
}

#endif
