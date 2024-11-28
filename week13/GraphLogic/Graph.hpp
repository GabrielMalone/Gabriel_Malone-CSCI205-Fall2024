#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include "../Backend/colors.hpp"
#include <vector>	
#include <map>		
#include "Vertex.hpp"
#include <random>
#include <algorithm>


using namespace std;

template <class T>
class Graph {
	private:
		std::map<int, Vertex<int>> vertList;							// the adjacancy list key -> Vertex
		int numVertices;																   // size of graph
		vector<vector<Vertex<int>>> matrix;								   // visual rep of adjacency graph
		vector<Vertex<int>*> validNodes;										  // nodes present for maze
		vector<Vertex<int>*> visited;

		//-------------------------------------------------------------------------------------------------
		// Helper function for create_matrix()
		//-------------------------------------------------------------------------------------------------
		void _fillMatrix(){
			//---------------------------------------------------------------------------------------------
			vector<int> nodes = getVertices();   								// get all the unique nodes
			int rows = nodes.size();                     // num nodes determines length and width of matrix
			int cols = rows;
			for (int i = 0; i < rows + 1; i++) {// plus one for col and row for the numbering of the matrix                                        
				for (int j = 0; j < cols + 1; j++) { 
					if (i == 0 && j == 0){}                         
					else if (i == 0 && j > 0){                                     // if at colum positions                       
					} else {
						if (j == 0){                     // if at column zero (reserved for numbering rows)      
						} else {     
							if (matrix[i][j].getPayload() == 0){						   // no connection
							} else { 			
								matrix[i][j].setXc(i);					   // set the x coord for this node
								matrix[i][j].setYc(j);					   // set the y coord for this node
								matrix[i][j].set_valid(true);			   // set this node as a valid path 
								matrix[i][j].setID(i);
								validNodes.push_back(&matrix[i][j]);     // add to list of nodes for task 2						 
							} 
						}
					}
				}                
			} 
		}
		//-------------------------------------------------------------------------------------------------
		int bfs(Vertex<int>* v) {
			Colors::clearScreen();	
			int seen_nodes = 0;
			bool* seen = new bool[ size() -1 ]();			// boolean array to track visited nodes.
			queue<Vertex<int>*> q;							// queue of Vertex pointers
			q.push(v);										// enqueue the starting node
			seen[ v->getId() ] = true;						// mark the starting node as being "seen"
			seen_nodes ++ ;
			
			while ( !q.empty() ) {							// as long as the queue is not empty
				
				Vertex<int>* vert = q.front();				// dequeue the front vertex
				q.pop();									// remove it from the queue
				for (int v : vert->getConnections()){		// get all of the edges from the current vertex
					if ( !seen[v] ) {						// if the current key has not been "seen"
						Vertex<int>* _v = getVertex(v);		// get the vertex
						for (auto node : validNodes){
							if (node->getId() == v){
								matrix[node->xCoord][node->yCoord].end = true;
								visited.emplace_back(node);
							}
						}
						q.push( _v );						// enqueue the vertext
						seen[ v ] = true;					// mark it as seen
						seen_nodes ++ ;
					}
					Colors::clearScreen();
					printMatrix();
					std::this_thread::sleep_for(std::chrono::milliseconds(30));
				}
				//cout << endl;								// just for nice printing
			}
			delete[] seen;									// free up dynamic memory
			return seen_nodes;
		}

		//-------------------------------------------------------------------------------------------------
	public:
		Graph(){ numVertices = 0; };												 // default constructor
		//-------------------------------------------------------------------------------------------------
		void addVertex(int key, T payload){						   // add isolated vertex by specifying key
			numVertices++;																  // increase count
			Vertex<T> newVertex = Vertex<T>(key, payload);							   // create the vertex

			this->vertList[key] = newVertex;						// put the vertex in the adjacancy list
		}
		//-------------------------------------------------------------------------------------------------
		Vertex<T>* getVertex(int key){									  // get pointer to vertex with key
			if (this->contains( key )){													 // does key exits?
				Vertex<T> *vpntr = &vertList[ key ];								 // yes, return pointer
				return vpntr;
			}
			return NULL;							 // return NULL if not found, don't want to add new key
		}
		//-------------------------------------------------------------------------------------------------
		int size(){ return this->numVertices; }								   // return number of vertices
		//-------------------------------------------------------------------------------------------------
		bool contains(int key){											   // does key exist in this graph?
			for (typename std::map<int, Vertex<T>>::iterator it = vertList.begin(); // get key via iterator
										it != vertList.end(); ++it){
				if (it->first == key) return true;
			}
			return false;
		}
		//-------------------------------------------------------------------------------------------------
		void addEdge(int from, int to, int cost = 0) {					 // add the edge from key -> to key
			if (!this->contains(from)) {						   // the source vertext does not exist yet
				std::cout << from << " was not found, adding!" << std::endl;             // helpful message
				this->addVertex(from, -1);												 		  // add it
			}
			if (!this->contains(to)){							   // destination vertex does not exist yet
				std::cout << to << " was not found, adding!" << std::endl;				 // helpful message
				this->addVertex(to, -1);													  	  // add it
			}
			vertList[from].addNeighbor(to, cost);			 // add the destination as neighbor to "source"
		}
		
		std::vector<int> getVertices() {									// returns a vector of all keys
			std::vector<int> verts;													 // vector to hold keys
			for (const std::pair<const int, Vertex<T>>& vertex : vertList)
			{
				verts.push_back(vertex.first);
			}																			   // add to vector
			return verts;																   // return vector
		}
		//-------------------------------------------------------------------------------------------------
		vector<vector<Vertex<int>>> create_matrix(){
			//---------------------------------------------------------------------------------------------
			vector<int> nodes = getVertices();   								// get all the unique nodes
			int rows = nodes.size();                     // num nodes determines length and width of matrix
			int cols = rows;
			//---------------------------------------------------------------------------------------------
			matrix = vector<vector<Vertex<int>>>(rows + 1, vector<Vertex<int>>(cols + 1));   // init matrix      
			//---------------------------------------------------------------------------------------------
			for (const std::pair<const int, Vertex<int>>& vertex : vertList){    // iterate map of vertices
				int matrix_row = vertex.first;												// current node 
				vector<int> neighbors = vertex.second.getConnections(); 			   // and its neighbors
				int i = 0;
				for (auto neighbor : neighbors){									   // get each neighbor
					int payload = 1;
					matrix[matrix_row][neighbor].setPayload(payload);			// mark its spot in the row
					if (i == 0){				// copy over the neighbor for the node that starts each row
						std::map<int, int> allneigh = vertex.second.getAllneighbors();
						matrix[matrix_row][neighbor].setAllNeighbors(allneigh);
					}
					i ++ ;
				}
			}
			_fillMatrix();
			return matrix;
		}

		//-------------------------------------------------------------------------------------------------
		void printMatrix(){
			//---------------------------------------------------------------------------------------------
			vector<int> nodes = getVertices();   								// get all the unique nodes
			for (int i = 0 ; i < matrix.size() ; i ++ ){
				for (int j = 0 ; j < matrix.size() ; j ++ ){
					if (i == 0 && j == 0){                               // top left corner should be blank
						cout << "    ";   // enough blank spaces to position the column numbering correctly
					} else if (i == 0 && j > 0){                                   // if at colum positions                       
						cout << setw(3) << setfill(' ') << left << nodes[j-1];        // number the columns
					} else if (j == 0){                  // if at column zero (reserved for numbering rows)  
						cout << setw(3) << setfill(' ') << left << nodes[i-1];           // number the rows
					} else {     
						if (matrix[i][j].getPayload() == 0){						       // no connection
							cout << Colors::empty;		
						} else { 
							if (matrix[i][j].isSource()){
								cout << Colors::source;
							}else if (matrix[i][j].isEnd()){
								cout << Colors::end;
							}else if (matrix[i][j].wasVisited()){
								cout << Colors::v_node;
							} else {
								cout << Colors::node;
							}	
						}
					}
				}	
			cout << endl;
			}
		}
		//-------------------------------------------------------------------------------------------------
		int shortestPath(){
			//---------------------------------------------------------------------------------------------
			random_device rd;               		  // random number generator for random node assignment
			mt19937 gen(rd());												 // first pick two random nodes
			uniform_int_distribution<> dist(1,  validNodes.size()-1); 	 // range from 0 to num valid nodes
			//---------------------------------------------------------------------------------------------
			printMatrix();
			int rand_index = dist(gen);
			Vertex<int>*source = validNodes[rand_index];							  	 // get source node
			int rand_index2 = dist(gen);
			while (rand_index2 == rand_index){						  // let's make sure we pick a diff num
				rand_index2 = dist(gen);
			}
			Vertex<int>*end = validNodes[rand_index2];										// get end node
			int end_x = end->getXc();							   // get the end coords ready for checking
			int end_y = end->getYc();
			matrix[end_x][end_y].setEnd(true);

			//---------------------------------------------------------------------------------------------
			int distance = 0;
			queue<Vertex<int>*> q;													  // queue for Vertices
			q.push(source);								// queue the source vertices and mark it as visited
			matrix[source->getXc()][source->getYc()].setVisited(true);
			matrix[source->getXc()][source->getYc()].setDistance(0);
			matrix[source->getXc()][source->getYc()].setSource(true);

			while (q.size() > 0){// get all neighbors, queue up ones that are valid and havent been visited
				
				Vertex<int>* cur_node = q.front(); 												 // dequeue
				distance += matrix[cur_node->getXc()][cur_node->getYc()].getDist();	
				q.pop();																			 // pop
				if (cur_node->getXc() == end_x && cur_node->getYc() == end_y){	     // if we found the end
					matrix[cur_node->getXc()][cur_node->getYc()].setVisited(true);	
					printMatrix();
					cout <<"   Shortest path between (" << source->getXc() << ", " 
						 << source->getYc()  <<") and (" << end->getXc() << ", " 
						 << end->getYc() << ") is: " 
						 << matrix[cur_node->getXc()][cur_node->getYc()].getDist() 
						 << endl;
					return matrix[cur_node->getXc()][cur_node->getYc()].getDist();
				}
				int xc = cur_node->getXc();							    // get current nodes x and y coords
				int yc = cur_node->getYc();

				distance = matrix[cur_node->getXc()][cur_node->getYc()].getDist();	  // set distance value
		
				int next_distance = distance + 1;				 
				if (xc-1>0 && matrix[xc-1][yc].valid() && ! matrix[xc-1][yc].wasVisited()){		   // north
					matrix[xc-1][yc].setVisited(true);
					matrix[xc-1][yc].setDistance(next_distance);
					q.push(&matrix[xc-1][yc]);
				}																				   // south
				if (xc+1 < matrix.size() && matrix[xc+1][yc].valid() && ! matrix[xc+1][yc].wasVisited()){  
					matrix[xc+1][yc].setVisited(true);
					matrix[xc+1][yc].setDistance(next_distance);
					q.push(&matrix[xc+1][yc]);
				}
				if (yc-1 > 0 && matrix[xc][yc-1].valid() && ! matrix[xc][yc-1].wasVisited()){ 		// west
					matrix[xc][yc-1].setVisited(true);
					matrix[xc][yc-1].setDistance(next_distance);
					q.push(&matrix[xc][yc-1]);
				}																					// east
				if (yc+1 < matrix.size() && matrix[xc][yc+1].valid() && ! matrix[xc][yc+1].wasVisited()){ 
					matrix[xc][yc+1].setVisited(true);
					matrix[xc][yc+1].setDistance(next_distance);
					q.push(&matrix[xc][yc+1]);
				}	
			}
			printMatrix();
			cout << "   end point not reachable" << endl;
			return -1;																							
		}
		//-------------------------------------------------------------------------------------------------
		bool stronglyConnected(){
			int reachable_rows = 0;				  // will be the total sum of rows reached from each vertex
			int rows_reached = 0;							  // the sum of reachable rows from each vertex
			create_matrix();												   // build the proximity graph					
			printMatrix();														// show the proximity graph
			vector<int> nodes_checked;	
			for (auto node : validNodes){
				if (node->getId() != 0 && find(nodes_checked.begin(), nodes_checked.end(), node->getId()) == nodes_checked.end()){
					matrix[node->xCoord][node->yCoord].source = true;
					rows_reached = bfs(node);
					for (auto seen : visited){
						matrix[seen->xCoord][seen->yCoord].end = false;
					}
					visited.clear();
					matrix[node->xCoord][node->yCoord].source = false;
					nodes_checked.emplace_back(node->getId());
					reachable_rows += rows_reached;
				}	
    		}
			cout << "\n  " << ((double)reachable_rows/(double)((matrix.size()-1) * (matrix.size()-1))) * 100 << "% of graph connected. ";										
			return reachable_rows == (matrix.size()-1) * (matrix.size()-1);
		}
		//-------------------------------------------------------------------------------------------------
		friend std::ostream &operator<<(std::ostream &stream, Graph<T> &grph) {
			stream << std::endl;
			for (auto&&v : grph.vertList )
				stream << v.second;
			return stream;
		}
		//-------------------------------------------------------------------------------------------------
		vector<Vertex<int>*> getValidNodes(){
			return this->validNodes;
		}
		//-------------------------------------------------------------------------------------------------
};

#endif