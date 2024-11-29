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
	// ------------------------------------------------------------------------
	Graph<int> g;										 // create graph object
	for (int i = 1; i <= range; i++) 			 // create range vertex objects
		g.addVertex(i, -1);					 		  // keys will be 1 - range
	// ------------------------------------------------------------------------
	if (type == 's'){ 					  // control - strongly connected graph
		g.addEdge(1, 2, 1);
		g.addEdge(1, 5, 1);
		g.addEdge(5, 6, 1);
		g.addEdge(5, 8, 1);
		g.addEdge(1, 9, 1);
		g.addEdge(2, 3, 1);
		g.addEdge(9, 10, 1);
		g.addEdge(3, 4, 1);
		g.addEdge(5, 7, 1);
		g.addEdge(6, 1, 1);   
		g.addEdge(8, 2, 1);  
		g.addEdge(10, 5, 1);  
		g.addEdge(4, 9, 1);   
		g.addEdge(7, 3, 1); 
	}
	// ------------------------------------------------------------------------
	if (type == 'r'){		  // randomly generated graph with more connections
		random_device rd;           
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1,  range);     // range from 0 to ange
		for (int i = 1; i <= range * 20 ; i++){  // create range vertex objects
			int from = dist(gen);
			int to  = dist(gen);
			int weight = -1;
			g.addEdge(from, to , weight);  
		}
	}
    // ------------------------------------------------------------------------
	if (type == 'c'){		 // randomly generated graph with fewer connections
		random_device rd;          // better for the strongly connected testing
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1,  range); 
		for (int i = 1; i <= range * 3 ; i++){   // create range vertex objects
			int from = dist(gen);
			int to  = dist(gen);
			int weight = -1;
			g.addEdge(from, to , weight);  
		}
	}
	if (type == 'd'){  // randomly generated graph with even fewer connections
		random_device rd;      					// better for the loop testing  
		mt19937 gen(rd());
		uniform_int_distribution<> dist(1,  range); 
		for (int i = 1; i <= range  ; i++){   // create range vertex objects
			int from = dist(gen);
			int to  = dist(gen);
			int weight = -1;
			g.addEdge(from, to , weight);  
		}
	}
    // ------------------------------------------------------------------------
	if (type == 't'){				     // control - create graph with a cycle
		g.addEdge(1, 2, 1);
		g.addEdge(2, 3, 1);
		g.addEdge(3, 4, 1);
		g.addEdge(4, 5, 1);
		g.addEdge(5, 1, 1);// This edge closes the cycle (1 → 2 → 3 → 4 → 5 → 1)
		g.addEdge(6, 7, 1); 					  // Additional non-cyclic edges
		g.addEdge(7, 8, 1);
		g.addEdge(8, 9, 1);
		g.addEdge(9, 10, 1);
	}
	if (type == 'z'){
		g.addEdge(2, 4, 1);
		g.addEdge(4, 3, 1);
		g.addEdge(4, 9, 1);
		g.addEdge(5, 5, 1);  
		g.addEdge(6, 10, 1);
		g.addEdge(7, 6, 1);
		g.addEdge(8, 7, 1);
		g.addEdge(8, 9, 1);  
		g.addEdge(9, 8, 1);
		g.addEdge(10, 2, 1);
	}
	// ------------------------------------------------------------------------
    return g;
}

#endif