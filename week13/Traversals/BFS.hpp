#ifndef BFS
#define BFS

#include <iostream>
#include <queue> 	// for breadth first traversal
#include <stack>	// for depth first traversal
#include "../GraphLogic/Graph.hpp"

using namespace std;

template <typename T>
void old_bfs(Graph<int>& g, Vertex<int>* v) {
	bool* seen = new bool[ g.size()+1 ]();			// boolean array to track visited nodes. +1 for 1-based indexing
	queue<Vertex<int>*> q;							// queue of Vertex pointers
	q.push(v);										// enqueue the starting node
	seen[ v->getId() ] = true;						// mark the starting node as being "seen"
	
	while ( !q.empty() ) {							// as long as the queue is not empty
		Vertex<int>* vert = q.front();				// dequeue the front vertex
		q.pop();									// remove it from the queue
		if (vert->getId() != 0){
			cout 	<< "Vertex " << vert->getId();		// print the vertex
			for (int v : vert->getConnections()){		// get all of the edges from the current vertex
				cout << "-->" 							// illustrate connection
					<< g.getVertex( v )->getId();		// print the key of the connected vertex
				if ( !seen[v] ) {						// if the current key has not been "seen"
					Vertex<int>* _v = g.getVertex(v);	// get the vertex
					q.push( _v );						// enqueue the vertext
					seen[ v ] = true;					// mark it as seen
				}
			}
		}
		cout << endl;								// just for nice printing
	}
	delete[] seen;									// free up dynamic memory
}

#endif