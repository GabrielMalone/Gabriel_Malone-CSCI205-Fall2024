#ifndef DFS
#define DFS

#include <iostream>
#include <queue> 	// for breadth first traversal
#include <stack>	// for depth first traversal
#include "Graph.hpp"

using namespace std;

void dfs(Graph<string>& g, Vertex<string>* r) {		// iterative depth first search using explicit stack
	char* c = new char[ g.size()+1 ]();				// array to store "visited" status. +1 for 1-based indexing
	stack< Vertex<string>* > s;						// stack of Vertex pointers to store edges
	s.push(r);										// push starting vertex

	while( s.size() > 0 ) {							// as long as the stack is not empty
		Vertex< string >* vert = s.top();			// get current Vertex
		int key = vert->getId();					// get the key of the current vertex
		cout << key << endl;						// print so we can see
		s.pop();									// pop current Vertex from Stack
		if( c[ key ] != 'v' ){						// has this vertex been visited?
			c[ key ]  = 'v';						// It has not. Mark it as visited
			vector<int> edges = g.getVertices();	// edges connected to i
			for (int key : vert->getConnections())	// loop through edges stemming from current vertex
				s.push( g.getVertex( key ) );		// push each vertext on to stack
		}
	}
	delete[] c;										// free up dynamic memory
}

#endif