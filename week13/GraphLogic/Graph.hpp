//----------------------------------------------------------------------------------------------------------------------
// GABRIEL MALONE / WEEK 13 / GRAPHS
//----------------------------------------------------------------------------------------------------------------------
#ifndef GRAPH_H
#define GRAPH_H
//----------------------------------------------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include "../Backend/colors.hpp"
#include "../Backend/print_vector.hpp"
#include <vector>
#include <map>
#include "Vertex.hpp"
#include <random>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stack>
//----------------------------------------------------------------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------------------------------------------------------------
template <class T>
class Graph {
private:
	map<int, Vertex<int>> vertList;							                         // the adjacancy list key -> Vertex
	int numVertices;																                    // size of graph
	vector<vector<Vertex<int>>> matrix;								                    // visual rep of adjacency graph
	vector<Vertex<int>*> validNodes;										                   // nodes present for maze
	vector<Vertex<int>*> visited;
	vector<vector<int>> detectedCycles;    				                                       // To track unique cycles
	int cost = 0;                                                                                      // for prims algo
	//------------------------------------------------------------------------------------------------------------------
	// Breadth first search
	//------------------------------------------------------------------------------------------------------------------
	int bfs(Vertex<int>* v) {
		int seen_nodes = 0;
		bool* seen = new bool[ size() + 1 ]();				                     // boolean array to track visited nodes
		queue<Vertex<int>*> q;												                 // queue of Vertex pointers
		q.push(v);                                                                          // enqueue the starting node
		visited.emplace_back(v);
		seen[ v->getId() ] = true;                     // mark starting node as being "seen" for strongly connected algo
		seen_nodes ++ ;
		while ( !q.empty() ) {									                    // as long as the queue is not empty
			Vertex<int>* vert = q.front();									                 // dequeue the front vertex
			q.pop();														                 // remove it from the queue
			for ( int a : vert->getConnections()){		                 // get all of the edges from the current vertex
				if ( !seen[a] ) {							                   // if the current key has not been "seen"
					Vertex<int>* _v = getVertex(a);									                   // get the vertex
					for (auto node : validNodes){
						if (node->getId() == a){
							visited.emplace_back(node);
						}
					}
					q.push( _v );												                  // enqueue the vertext
					seen[ a ] = true;												                  // mark it as seen
					seen_nodes ++ ;
				}
			}
		}
		delete[] seen;														                   // free up dynamic memory
		return seen_nodes;
	}
	//------------------------------------------------------------------------------------------------------------------
	// Depth first search way easier to find the paths of the loops.
	//------------------------------------------------------------------------------------------------------------------
	void dfs(Vertex<int>* r) {
	    stack<Vertex<int>* > s;                                               // Stack of Vertex pointers to store edges
	    unordered_set<int> v;                   // Tracks visited nodes of current path (answers y/n has node been seen)
	    vector<int> path;                 					                 // Tracks the current actual traversal path
		//--------------------------------------------------------------------------------------------------------------
	    s.push(r);                        											             // Push starting vertex
		//--------------------------------------------------------------------------------------------------------------
	    while (!s.empty()) {              							                // As long as the stack is not empty
	        Vertex<int>* vert = s.top();  											               // Get current Vertex
	        int key = vert->getId();      							                // Get the key of the current vertex
			//----------------------------------------------------------------------------------------------------------
	        if (v.find(key) == v.end()) {          		   				                // Has this vertex been visited?
				v.insert(key);  													                  // mark as visited
	            path.push_back(key);      									               // Add it to the current path
	            v.insert(key);     								                 // Mark it as part of the current stack
				//------------------------------------------------------------------------------------------------------
	            for (int conn : vert->getConnections()) {                  // Loop through edges from the current vertex
	                if (v.find(conn) != v.end()) {     			                   // if connection already in the stack
					vector<int> cycle_code;
					for (auto p : path) {
						cycle_code.push_back(p);
					}										                     // create the unique key for this cycle
					cycle_code.push_back(cycle_code[0]);              // Close loop visually (eg if starts w 2, end w 2)
					detectedCycles.push_back(cycle_code);
	                } else if (v.find(conn) == v.end()) {  						 		                      //no cycle
	                    s.push(getVertex(conn));                                           // push unvisited connections
	                }
	            }
	        } else {
	            s.pop();  													                     // Fully processed node
			}
	    }
	}

//----------------------------------------------------------------------------------------------------------------------
public:
	//------------------------------------------------------------------------------------------------------------------
	Graph(){ numVertices = 0; };												                  // default constructor
	//------------------------------------------------------------------------------------------------------------------
	void addVertex(int key, T payload){						                    // add isolated vertex by specifying key
		numVertices++;																                   // increase count
		Vertex<T> newVertex = Vertex<T>(key, payload);							                    // create the vertex

		this->vertList[key] = newVertex;						                 // put the vertex in the adjacancy list
	}
	//------------------------------------------------------------------------------------------------------------------
	Vertex<T>* getVertex(int key){									                   // get pointer to vertex with key
		if (this->contains( key )){													                  // does key exits?
			Vertex<T> *vpntr = &vertList[ key ];								                  // yes, return pointer
			return vpntr;
		}
		return NULL;							                  // return NULL if not found, don't want to add new key
	}
	//------------------------------------------------------------------------------------------------------------------
	int size(){ return this->numVertices; }								                    // return number of vertices
	//------------------------------------------------------------------------------------------------------------------
	bool contains(int key){											                    // does key exist in this graph?
		for (typename std::map<int, Vertex<T>>::iterator it = vertList.begin();                  // get key via iterator
		     it != vertList.end(); ++it){
			if (it->first == key) return true;
		}
		return false;
	}
	//------------------------------------------------------------------------------------------------------------------
	void addEdge(int from, int to, int cost = 0) {					                  // add the edge from key -> to key
		if (!this->contains(from)) {						                    // the source vertext does not exist yet
			//std::cout << from << " was not found, adding!" << std::endl;                            // helpful message
			this->addVertex(from, cost);												 		               // add it
		}
		if (!this->contains(to)){							                    // destination vertex does not exist yet
			//std::cout << to << " was not found, adding!" << std::endl;				              // helpful message
			this->addVertex(to, cost);													  	                   // add it
		}
		vertList[from].addNeighbor(to, cost);			                  // add the destination as neighbor to "source"
	}

	std::vector<int> getVertices() {									                 // returns a vector of all keys
		std::vector<int> verts;													                  // vector to hold keys
		for (const std::pair<const int, Vertex<T>>& vertex : vertList)
		{
			verts.push_back(vertex.first);
		}																			                    // add to vector
		return verts;																                    // return vector
	}
	//------------------------------------------------------------------------------------------------------------------
	// GRAPHICALLY CREATE AN ADJACENCY GRAPH MATRIX
	//------------------------------------------------------------------------------------------------------------------
	vector<vector<Vertex<int>>> create_matrix(){
		//--------------------------------------------------------------------------------------------------------------
		vector<int> nodes = getVertices();   								                 // get all the unique nodes
		int rows = nodes.size();                                      // num nodes determines length and width of matrix
		int cols = rows;
		//--------------------------------------------------------------------------------------------------------------
		matrix = vector<vector<Vertex<int>>>(rows + 1, vector<Vertex<int>>(cols + 1));                    // init matrix
		//--------------------------------------------------------------------------------------------------------------
		for (const std::pair<const int, Vertex<int>>& vertex : vertList){                     // iterate map of vertices
			int matrix_row = vertex.first;										                    // current node's ID
			vector<int> neighbors = vertex.second.getConnections(); 			                    // and its neighbors
			int i = 0;
			for (auto neighbor : neighbors){									                    // get each neighbor
				int payload = 1;                 // setting payload to 1 indicates to matrix this spot is a valid vertex
				matrix[matrix_row][neighbor].setPayload(payload);					                  // set the payload
				if (i == 0){                   // i = 0: root for row. copy over neighbors for node that starts each row
					std::map<int, int> allneigh = vertex.second.getAllneighbors();                  // get all neighbors
					matrix[matrix_row][neighbor].setAllNeighbors(allneigh);                     // set [ID][NEIGHBOR_ID]
				}
				i ++ ;
			}
		}								                 // now iterate through matrix and set the remaining information
		for (int i = 0; i < rows + 1; i++) {                 // plus one for col and row for the numbering of the matrix
			for (int j = 0; j < cols + 1; j++) {
				if (matrix[i][j].getPayload() != 0){						                  // if vertex has a payload
					matrix[i][j].setXc(i);					   		                    // set the x coord for this node
					matrix[i][j].setYc(j);					   		                    // set the y coord for this node
					matrix[i][j].set_valid(true);			   		                    // set this node as a valid path
					matrix[i][j].setID(i);
					validNodes.push_back(&matrix[i][j]);     	                 // add to list of nodes for other tasks
				}
			}
		}
		return matrix;
	}
	//------------------------------------------------------------------------------------------------------------------
	// PRINT THE ADJACENY GRAPH
	//------------------------------------------------------------------------------------------------------------------
	void printMatrix(){
		//--------------------------------------------------------------------------------------------------------------
		vector<int> nodes = getVertices();   								                 // get all the unique nodes
		for (int i = 0 ; i < (int)matrix.size() ; i ++ ){
			for (int j = 0 ; j < (int)matrix.size() ; j ++ ){
				if (i == 0 && j == 0){                                                // top left corner should be blank
					cout << "    ";                    // enough blank spaces to position the column numbering correctly
				} else if (i == 0 && j > 0){                                                    // if at colum positions
					cout << setw(3) << setfill(' ') << left << nodes[j-1];                         // number the columns
				} else if (j == 0){                                   // if at column zero (reserved for numbering rows)
					cout << setw(3) << setfill(' ') << left << nodes[i-1];                            // number the rows
				} else if (matrix[i][j].getPayload() == 0){     	 				                    // no connection
					cout << Colors::empty;
				} else { 											                   // if a valid node, see what type
					if (matrix[i][j].source)
						cout  << Colors::start;								                    // the start of the path
					else if (matrix[i][j].end)
						cout << Colors::finish;										                  // end of the path
					else if (matrix[i][j].visited){
							cout << Colors::v_node;
					}
					else if (matrix[i][j].truePath)
						cout << Colors::path;									                   // actual path to end
					else if (matrix[i][j].reached)
						cout << Colors::finished;			                  // mark end point as finished once reached
					else
						cout << Colors::node;                                                              // plain node
				}
			}
			cout << endl;
		}
	}
	//------------------------------------------------------------------------------------------------------------------
	// DETERMINE THE SHORTEST PATH BETWEEN TWO POINTS IN A GRAPH
	//------------------------------------------------------------------------------------------------------------------
	int shortestPath(){
		//--------------------------------------------------------------------------------------------------------------
		random_device rd;               		                   // random number generator for random node assignment
		mt19937 gen(rd());												                  // first pick two random nodes
		uniform_int_distribution<> dist(1,  validNodes.size()-1); 	                  // range from 0 to num valid nodes
		//--------------------------------------------------------------------------------------------------------------
		//printMatrix();
		//--------------------------------------------------------------------------------------------------------------
		int rand_index = dist(gen);
		Vertex<int>*source = validNodes[rand_index];							  	                  // get source node
		int rand_index2 = dist(gen);
		while (rand_index2 == rand_index){						                   // let's make sure we pick a diff num
			rand_index2 = dist(gen);
		}
		Vertex<int>*end = validNodes[rand_index2];										                 // get end node
		int end_x = end->getXc();							                    // get the end coords ready for checking
		int end_y = end->getYc();
		matrix[end_x][end_y].setEnd(true);
		//--------------------------------------------------------------------------------------------------------------
		std::unordered_map<Vertex<int>*, Vertex<int>*> parent;			                 // path reconstruction purposes
		std::unordered_map<Vertex<int>*, bool> visited_n; 	                  // Track visited nodes path reconstruction
		int distance = 0;
		queue<Vertex<int>*> q;													                   // queue for Vertices
		//--------------------------------------------------------------------------------------------------------------
		q.push(source);								                 // queue the source vertices and mark it as visited
		visited_n[source] = true;										                    // for backtrackign puproses
		matrix[source->getXc()][source->getYc()].setVisited(true);
		matrix[source->getXc()][source->getYc()].setDistance(0);
		matrix[source->getXc()][source->getYc()].setSource(true);
		parent[source] = nullptr; 						                  // source has no parent // path reconstruction
		//--------------------------------------------------------------------------------------------------------------
		while (q.size() > 0){                 // get all neighbors, queue up ones that are valid and havent been visited
			Vertex<int>* cur_node = q.front(); 												                  // dequeue
			distance += matrix[cur_node->getXc()][cur_node->getYc()].getDist();
			//----------------------------------------------------------------------------------------------------------
			q.pop();																			                  // pop
			//----------------------------------------------------------------------------------------------------------
			if (cur_node->getXc() == end_x && cur_node->getYc() == end_y){	                      // if we found the end
				matrix[cur_node->getXc()][cur_node->getYc()].setVisited(true);
				//------------------------------------------------------------------------------------------------------
				std::vector<Vertex<int>*> path;										                 // reconstruct path
				for (auto v = end; v != nullptr; v = parent[v])	                  // parent by parent staring w end node
					path.push_back(v);
				reverse(path.begin(), path.end());
				//------------------------------------------------------------------------------------------------------
				int i = 0;												                  // print the path step by step
				for (auto node : path) {
					matrix[node->xCoord][node->yCoord].visited = false;
					matrix[node->xCoord][node->yCoord].truePath = true;
					if (i == (int)path.size()-1){
						matrix[end->xCoord][end->yCoord].truePath = false;
						matrix[end->xCoord][end->yCoord].end = false;
						matrix[end->xCoord][end->yCoord].reached = true;
					}
					// Colors::clearScreen(200);
					// printMatrix();
					i ++ ;
					//--------------------------------------------------------------------------------------------------
				}
				//------------------------------------------------------------------------------------------------------
				//Colors::clearScreen(0);
				printMatrix();														                  // show final path
				//------------------------------------------------------------------------------------------------------
				cout <<"   Shortest path between (" << source->getXc() << ", " 			                  // print logic
				     << source->getYc()  <<") and (" << end->getXc() << ", "
				     << end->getYc() << ") is: "
				     << matrix[cur_node->getXc()][cur_node->getYc()].getDist()
				     << endl;
				//------------------------------------------------------------------------------------------------------
				return matrix[cur_node->getXc()][cur_node->getYc()].getDist();
			}
			////--------------------------------------------------------------------------------------------------------
			int xc = cur_node->getXc();							                     // get current nodes x and y coords
			int yc = cur_node->getYc();
			distance = matrix[cur_node->getXc()][cur_node->getYc()].getDist();	                   // set distance value
			int next_distance = distance + 1;
			//----------------------------------------------------------------------------------------------------------
			if (xc-1>0 && matrix[xc-1][yc].valid() && ! matrix[xc-1][yc].wasVisited()){		                    // north
				matrix[xc-1][yc].setVisited(true);
				matrix[xc-1][yc].setDistance(next_distance);
				parent[&matrix[xc-1][yc]] = cur_node;		                 // save parent info for path reconstruction
				q.push(&matrix[xc-1][yc]);
			}
			if (xc+1 < (int)matrix.size() && matrix[xc+1][yc].valid() && ! matrix[xc+1][yc].wasVisited()){      // south
				matrix[xc+1][yc].setVisited(true);
				matrix[xc+1][yc].setDistance(next_distance);
				parent[&matrix[xc+1][yc]] = cur_node;
				q.push(&matrix[xc+1][yc]);
			}
			if (yc-1 > 0 && matrix[xc][yc-1].valid() && ! matrix[xc][yc-1].wasVisited()){ 		                 // west
				matrix[xc][yc-1].setVisited(true);
				matrix[xc][yc-1].setDistance(next_distance);
				parent[&matrix[xc][yc-1]] = cur_node;
				q.push(&matrix[xc][yc-1]);
			}
			if (yc+1 < (int)matrix.size() && matrix[xc][yc+1].valid() && ! matrix[xc][yc+1].wasVisited()){       // east
				matrix[xc][yc+1].setVisited(true);
				matrix[xc][yc+1].setDistance(next_distance);
				parent[&matrix[xc][yc+1]] = cur_node;
				q.push(&matrix[xc][yc+1]);
			}
			//----------------------------------------------------------------------------------------------------------
		}
		printMatrix();
		cout << "   end point not reachable" << endl;
		return -1;
	}
	//------------------------------------------------------------------------------------------------------------------
	// DETERMINE IF A GRAPH IS STRONGLY CONNECTED
	//------------------------------------------------------------------------------------------------------------------
	bool stronglyConnected(){
		int rr = 0;				                  // rows reached will be the total sum of rows reached from each vertex
		int rows_reached = 0;							                   // the sum of reachable rows from each vertex
//		create_matrix();												                    // build the proximity graph
//		printMatrix();														                 // show the proximity graph
		vector<int> nc;																                    // nodes checked
		for (auto node : validNodes){
			if (node->getId() != 0 && find(nc.begin(), nc.end(), node->getId()) == nc.end()){
				matrix[node->xCoord][node->yCoord].source = true;
				rows_reached = bfs(node);
				for (auto seen : visited){
					matrix[seen->xCoord][seen->yCoord].end = false;
				}
				visited.clear();
				matrix[node->xCoord][node->yCoord].source = false;
				nc.emplace_back(node->getId());
				rr += rows_reached;
			}
		}
		cout << "\n  " << ((double)rr/(double)((matrix.size()-1) * (matrix.size()-1))) * 100
		     << "% connected. ";
		visited.clear();
		return rr == (int)((matrix.size()-1) * (matrix.size()-1));
	}
	//------------------------------------------------------------------------------------------------------------------
	// DETECT ANY CYCLES IN A GRAPH
	//------------------------------------------------------------------------------------------------------------------
	bool cyclesPresent(){
		bool cycles = false;
		vector<int> nc;																                    // nodes checked
		for (auto node : validNodes){				                    // iterate through the valid nodes in the matrix
			if (node->getId() != 0 && find(nc.begin(), nc.end(), node->getId()) == nc.end()){                // !checked
				dfs(node);                 // fun dfs on valid nodes. this will detect and save loops in detected Cycles
			}
		}
		unordered_map<string, bool> yet_detected_codes;                                 // map to detect duplicate loops
		for (auto v_code: detectedCycles){                                             // iterate through detected loops
			int index = 1;
			string final_path; // build final loop, don't build as go because will need to sometimes erase entire string
			while (index < (int)v_code.size()){
				if (index == 1){
					final_path += Colors::BRIGHT_YELLOW + to_string(v_code[0]) + Colors::BRIGHT_BLUE + "->";
				}
				int prev = v_code[index - 1];
				int cur = v_code[index];
				int id = matrix[prev][cur].id;
				if (id != prev){
					final_path = "";
					break;
				}
				if (id == prev){
					final_path += Colors::BRIGHT_YELLOW + to_string(cur) + Colors::BRIGHT_BLUE + "->";
					index ++ ;
				}
			}
			if (! yet_detected_codes[final_path])
				yet_detected_codes[final_path] = true;
		}
		for (auto & yet_detected_code : yet_detected_codes) {
			if (yet_detected_code.first.length() > 1) {
				cout << yet_detected_code.first.substr(0, yet_detected_code.first.length() - 2) << endl;
				cycles = true;
			}
		}
		cout << Colors::RESET << endl;
		if (!cycles){
			cout << "No cycles present.";
		}
		return cycles;
	}
	//------------------------------------------------------------------------------------------------------------------
	friend std::ostream &operator<<(std::ostream &stream, Graph<T> &grph) {
		stream << std::endl;
		for (auto&&v : grph.vertList )
			stream << v.second;
		return stream;
	}
	//------------------------------------------------------------------------------------------------------------------
	void printWeights(){
		bfs(validNodes[0]);
		for (auto v : visited){
			bool visit = false;
			for (auto n : v->getConnections()) {
				if (v->getWeight(n) > 0) {
					visit = true;
					cout << " " << v->id << Colors::BRIGHT_BLUE << "--" << Colors::RESET << Colors::YELLOW << "("
					     << v->getWeight(n) << ")" << Colors::BRIGHT_BLUE << Colors::RESET << Colors::BRIGHT_BLUE
					     << "-->" << Colors::RESET << n;
				}
			}
			if (visit)
				cout << endl;
		}
	}
	//------------------------------------------------------------------------------------------------------------------
	Graph<T> primsAlgo(){                                                 // https://www.youtube.com/watch?v=jsmMtJpPnhU
		//--------------------------------------------------------------------------------------------------------------
		// Data structures required for this algo: a min heap and a way to track visited nodes
		//--------------------------------------------------------------------------------------------------------------
		cost = 0;
		Graph<int> MST;                                                           // to create MST version of this Graph
		vector<int>uniqueNodes;
		vector<int>visitedUniqueNodes;
		for (auto n : validNodes){                                           // get number of unique edges in this graph
			if (find(uniqueNodes.begin(), uniqueNodes.end(), n->id) == uniqueNodes.end())
				uniqueNodes.emplace_back(n->id);
		}
		for (int i = 1; i < (int)uniqueNodes.size() + 1; i++) 			                             // set up the graph
			MST.addVertex(i, 0);
		using Triple = std::tuple<int, int, int>;                                                  // weight, id, parent
		// Min-heap using std::priority_queue with a triple tuple
		std::priority_queue<Triple, std::vector<Triple>, std::greater<>> minHeap;
		//--------------------------------------------------------------------------------------------------------------
		Vertex<int>* s = getVertex(uniqueNodes[0]);                   // start at first unique node (can start anywhere)
		visitedUniqueNodes.emplace_back(s->id);                                                   // add this to visited
		for (int n : s->getConnections()){
			minHeap.emplace(s->getWeight(n), n, s->id);                                           // weight, id , parent
		}
		while (!minHeap.empty()){
			auto [weight, id, parent] = minHeap.top();
			minHeap.pop();
			if (find(visitedUniqueNodes.begin(), visitedUniqueNodes.end(), id) == visitedUniqueNodes.end()){
				MST.addEdge(id, parent, weight);             // do twice for both directions since this undirected graph
				MST.addEdge(parent, id, weight);
				cost += weight;                                                                        // sum the weight
				visitedUniqueNodes.emplace_back(id);
				for (int n : getVertex(id)->getConnections()) {
					if (find(visitedUniqueNodes.begin(), visitedUniqueNodes.end(), n) == visitedUniqueNodes.end()) {
						minHeap.emplace(getVertex(id)->getWeight(n), n, id);
					}
				}
			}
		}
		//--------------------------------------------------------------------------------------------------------------
		// could seperate this out but this shows the new graph created from the algo
		//--------------------------------------------------------------------------------------------------------------
		MST.create_matrix();
		MST.printMatrix();
		cout << endl;
		MST.printWeights();
		//--------------------------------------------------------------------------------------------------------------
		return MST;
	}
	int getCost(){
		return cost;
	}
};

#endif