#ifndef VECPRINT
#define VECPRINT

#include <vector>
#include <iostream>

void print_vector(std::vector<int>& vec){
	for (size_t i = 0; i < vec.size(); i++)
		std::cout<< vec[i] << " ";
	std::cout << std::endl;
}

#endif