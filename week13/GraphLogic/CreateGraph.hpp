#ifndef CREATE_GRAPH
#define CREATE_GRAPH

#include <iostream>
#include <queue> 	// for breadth first traversal
#include <stack>	// for depth first traversal
#include "Graph.hpp"
#include <random>
#include <thread>
#include <chrono>

using namespace std;

Graph<int> create_graph(int range, char type){

	Graph<int> g;						// create graph object
	for (int i = 1; i <= range; i++) 	// create range vertex objects
		g.addVertex(i, -1);				// keys will be 1 - range

	if (type == 'z'){					// zigzag connected graph
		g.addEdge(1, 1, 5); 
		g.addEdge(1, 2, 5);  
		g.addEdge(2, 2, 2);   
		g.addEdge(2, 3, 4);   
		g.addEdge(3, 3, 7);   
		g.addEdge(3, 4, 3);   
		g.addEdge(4, 4, 8);   
		g.addEdge(4, 5, 6);   
		g.addEdge(5, 5, 5);   
		g.addEdge(5, 6, 7); 
		g.addEdge(6, 6, 2);   
		g.addEdge(6, 7, 9);   
		g.addEdge(7, 7, 4);   
		g.addEdge(7, 8, 3);   
		g.addEdge(8, 8, 6);  
		g.addEdge(8, 9, 5);  
		g.addEdge(9, 9, 8);   
		g.addEdge(9, 10, 2);  
		g.addEdge(10, 10, 7); 
		g.addEdge(10, 11, 4);
		g.addEdge(11, 11, 6); 
		g.addEdge(11, 12, 5); 
		g.addEdge(12, 12, 8); 
		g.addEdge(12, 13, 3);
		g.addEdge(13, 13, 7); 
		g.addEdge(13, 14, 9); 
		g.addEdge(14, 14, 6); 
		g.addEdge(14, 15, 2); 
		g.addEdge(15, 15, 4); 
		g.addEdge(15, 16, 7); 

	}
	if (type == 's'){ 				// strongly connected graph
		g.addEdge(1, 2, 5);
		g.addEdge(1, 5, 2);
		g.addEdge(5, 6, 4);
		g.addEdge(5, 8, 7);
		g.addEdge(1, 9, 3);
		g.addEdge(2, 3, 8);
		g.addEdge(9, 10, 1);
		g.addEdge(3, 4, 1);
		g.addEdge(5, 7, 9);
		g.addEdge(6, 1, 1);   
		g.addEdge(8, 2, 1);  
		g.addEdge(10, 5, 1);  
		g.addEdge(4, 9, 1);   
		g.addEdge(7, 3, 1); 
	}
	if (type == 'w'){ 				// weakly connected graph
		g.addEdge(1, 2, 5);
		g.addEdge(1, 5, 2);
		g.addEdge(5, 6, 4);
		g.addEdge(5, 8, 7);
		g.addEdge(1, 9, 3);
		g.addEdge(2, 3, 8);
		g.addEdge(9, 10, 1);
		g.addEdge(3, 4, 1);
		g.addEdge(5, 7, 9);
		g.addEdge(6, 1, 1);   
		g.addEdge(8, 2, 1);  
		g.addEdge(10, 5, 1);  
		g.addEdge(4, 9, 1);   
	}
	if (type == 'r'){		// randomly generated graph
		random_device rd;           
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1,  range); // range from 0 to 100 for the rnadom value
		for (int i = 1; i <= range * 20 ; i++){ 	// create range vertex objects
			int from = dist(gen);
			int to  = dist(gen);
			int weight = -1;
			g.addEdge(from, to , weight);  
		}
	}
	if (type == 'c'){		// randomly generated graph
		random_device rd;           
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1,  range); // range from 0 to 100 for the rnadom value
		for (int i = 1; i <= range * 2 ; i++){ 	// create range vertex objects
			int from = dist(gen);
			int to  = dist(gen);
			int weight = -1;
			g.addEdge(from, to , weight);  
		}
	}
    return g;
}

#endif