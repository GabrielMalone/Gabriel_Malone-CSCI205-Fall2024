#ifndef GRAPH_HEIGHT
#define GRAPH_HEIGHT

#include <iostream>

//------------------------------------------------------------------------------------
// OUTPUT GRAPHS
//------------------------------------------------------------------------------------
void graph_height() {
	int status = system("python3 backend/plot_height_tests.py"); 
	if (status == -1)
	{
		std::cerr << "\npython script failed :[\n" << std::endl;
	} else {
		std::cout << "\n  graphs created successfully!\n" << std::endl;
		std::cout << "  all .txt data cleared\n" << std::endl;
	}
}

#endif