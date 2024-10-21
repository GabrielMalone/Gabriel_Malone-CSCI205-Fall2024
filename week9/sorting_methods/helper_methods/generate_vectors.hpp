#ifndef VECTORGENERATOR
#define VECTORGENERATOR
#include <random>

using namespace std;
random_device rd;                // random number generator for random val assignment
mt19937 gen(rd());
uniform_int_distribution<> dist(1,  100); // range from 0 to 100 for the rnadom value
//------------------------------------------------------------------------------------
//  generates a random vector of size "size" with type "type"
//  type = 'a' for ascending, 'd' for descending, 'r' for random, 'p' for partially 
//------------------------------------------------------------------------------------
void generate_vector(int size, char type, std::vector<int>& temp){
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
			for(int i = 0; i < size; i++)
				temp[i] = dist(gen);
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
