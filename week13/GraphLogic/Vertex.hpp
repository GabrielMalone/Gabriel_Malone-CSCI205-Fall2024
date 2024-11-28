#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include <map>
#include <iostream>

template <class T>
class Vertex {
	public:										// got tired of writing getters and setters
		int id;									// vertex key
		std::map<int, int> connectedTo;			// list of neighbors ids and edge weights
		T payload;								// add payload here
		int xCoord = -1;
		int yCoord = -1;
		int distanceFromSource = 0;
		bool valid_path = false;
		bool visited = false;
		bool source = false;
		bool end = false;
		bool truePath = false;
		bool reached = false;

	public:
		Vertex() {}				// default constructor
		Vertex( T pl) { this->payload = pl; }	// constructor with key and payload
		Vertex(int key, T pl) {					// constructor with key and payload
			this->id 	  = key;				// set key
			this->payload = pl;					// set payload
		}

		//Vertex(const Vertex&) = delete;		// Delete copy constructor

		void addNeighbor(int nbr, int weight = 0) {						// adds neighbor
			connectedTo[nbr] = weight;									// if neighbor exists the weight will be updated
																		// if not, the neighbor will be added
		}
		std::vector<int> getConnections() const {
			std::vector<int> keys;  // will return a vector containing all neighbors
			for (std::map<int, int>::const_iterator it = connectedTo.begin(); it != connectedTo.end(); ++it)
				keys.push_back(it->first);  // add to vector
			return keys;  // return vector
		}
		T getPayload(){ return this->payload; }	// get payload
		void setPayload(int& p){ this->payload = p; }
		int getId() { return this->id; }								// return this vector's id
		void setID(int id) { this->id = id; }
		int getWeight(int nbr) { return this->connectedTo[nbr]; }		// get weight of single edge from this vertex to nbr
		std::map<int, int> getAllneighbors() const { return this->connectedTo; }
		void setAllNeighbors(std::map<int, int> neibhbors ){ this->connectedTo = neibhbors; }
		void setXc(const int& x){ this->xCoord = x; }
		void setYc(const int& y){ this->yCoord = y; }
		int getXc(){ return this->xCoord; }
		int getYc(){ return this->yCoord; }
		int getDist(){ return this->distanceFromSource; }
		bool valid(){ return this->valid_path; }
		void set_valid(bool v){ this->valid_path = v;}
		bool wasVisited(){ return this->visited; }
		void setVisited(bool v) { this->visited = v; }
		void setDistance(int d) { this->distanceFromSource = d; }
		void setSource(bool s){ this->source = s; }
		bool isSource(){ return this->source; }
		bool isEnd(){ return this->end; }
		void setEnd(bool e){ this->end = e; }
	
		friend std::ostream &operator<<(std::ostream &stream, Vertex<T> &vert) {
			std::vector<int> connects = vert.getConnections();			// get all neighbors
			for (unsigned int i = 0; i < connects.size(); i++)			// iterate through neighbors
				stream	<< "( " << vert.id << " , " 					// print this vertex's id
						<< connects[i] << " ) \n";						// print neighbor's id
			return stream;												// return stream
		}
};
#endif