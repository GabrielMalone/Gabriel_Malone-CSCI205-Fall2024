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
		for (int i = 1; i <= range * 25 ; i++){  // create range vertex objects
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
			int weight = dist(gen);
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
	if (type == 'z'){                                       // debugging graphs
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
	if (type == 'g'){                                      // debugging graphs
		g.addEdge(2, 6, 1);
		g.addEdge(3, 7, 1);
		g.addEdge(3, 10, 1);
		g.addEdge(5, 2, 1);  
		g.addEdge(5, 3, 1);
		g.addEdge(5, 6, 1);
		g.addEdge(6, 5, 1);
		g.addEdge(6, 6, 1);  
		g.addEdge(10, 1, 1);
		g.addEdge(10, 7, 1);
	}
	if (type == 'p'){                             // let's make a graph for prims algo
		g.addEdge(1, 2, 28);
		g.addEdge(2, 1, 28);
		g.addEdge(2, 3, 16);                // this will mirror the one in the lab pdf
		g.addEdge(3, 2, 16);
		g.addEdge(2, 7, 14);
		g.addEdge(7, 2, 14);
		g.addEdge(4, 3, 12);
		g.addEdge(3, 4, 12);
		g.addEdge(5, 4, 22);
		g.addEdge(4, 5, 22);
		g.addEdge(6, 1, 10);
		g.addEdge(1, 6, 10);
		g.addEdge(6, 5, 25);
		g.addEdge(5, 6, 25);
		g.addEdge(7, 5, 24);
		g.addEdge(5, 7, 24);
		g.addEdge(7, 4, 18);
		g.addEdge(4, 7, 18);
	}
	if (type =='w'){                // the other pdf prims algo shown in the lab
		g.addEdge(1, 2, 1);
		g.addEdge(2, 1, 1);
		g.addEdge(1, 3, 2);
		g.addEdge(3, 1, 2);
		g.addEdge(2, 3, 3);
		g.addEdge(3, 2, 3);
		g.addEdge(3, 4, 4);
		g.addEdge(4, 3, 4);
		g.addEdge(4, 5, 7);
		g.addEdge(5, 4, 7);
		g.addEdge(3, 5, 5);
		g.addEdge(5, 3, 5);
		g.addEdge(5, 6, 8);
		g.addEdge(6, 5, 8);
		g.addEdge(6, 3, 6);
		g.addEdge(3, 6, 6);
	}
	// ------------------------------------------------------------------------
    return g;
}

#endif