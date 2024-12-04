// ----------------------------------------------------------------------------
// GABRIEL MALONE / CS205 / WEEK 13 / GRAPHS
// ----------------------------------------------------------------------------
#include "GraphLogic/Graph.hpp"
#include "GraphLogic/CreateGraph.hpp"
#include "BinaryTree/binaryTree.hpp"

using namespace std;

int main(){
	// ------------------------------------------------------------------------
    Colors::clearScreen(0);
    cout << Colors::GRAY;
    // ------------------------------------------------------------------------
    cout << "" << endl;
    cout << "TASK ONE - PRINT EACH LEVEL OF A BINARY TREE BIA BFS  "   << endl;
    cout << "" << endl;
    cout << Colors::RESET;
    // ------------------------------------------------------------------------
    AVL_BinarySearchTree<int> bst;         // this just left over from last lab
    bst.initialize(25, 'r', false);
    bst.print();
    cout << Colors::RESET << endl;
    cout << Colors::GRAY;
    // ------------------------------------------------------------------------
    cout << "" << endl;
    cout << "TASK TWO - FIND SHORTEST PATH "                           << endl;
    cout << "" << endl;
    cout << Colors::RESET;
    // ------------------------------------------------------------------------
    int graph_size = 20;    // create graph of size with randamized connections
    Graph<int> g_s = create_graph(graph_size, 'r');       // r for random graph 
    g_s.create_matrix(); //  graph via BFS
    g_s.shortestPath();
    // ------------------------------------------------------------------------
    cout << Colors::GRAY;
    cout << "" << endl;
    cout << "TASK THREE - CHECK IF STRONGLY CONNECTED "                << endl;
    cout << "" << endl;
    cout << Colors::RESET;
    // ------------------------------------------------------------------------
    graph_size = 10;        // create graph of size with randamized connections
    Graph<int> g3 = create_graph(graph_size, 'c');       // s for control graph
	g3.create_matrix();
	g3.printMatrix();
    if (g3.stronglyConnected()){
        cout << "graph strongly connected " << endl;
    } else {
        cout << "graph not strongly connected" << endl;
    }
    // ------------------------------------------------------------------------
    cout << Colors::GRAY;
    cout << "" << endl;
    cout << "TASK FOUR - CYCLE DETECTION"                              << endl;
    cout << "" << endl;
    cout << Colors::RESET;
    // ------------------------------------------------------------------------
    graph_size = 10;        // create graph of size with randamized connections
    Graph<int> g5 = create_graph(graph_size, 'c');     // 'z' for control graph
	g5.create_matrix();
	g5.printMatrix();
	cout << endl;
    g5.cyclesPresent();
	// ------------------------------------------------------------------------
	cout << Colors::GRAY;
	cout << "TASK FIVE - PRIMS ALGORITHM"                              << endl;
	cout << "" << endl;
	cout << Colors::RESET;
	// ------------------------------------------------------------------------
	graph_size = 7;      // create the graph given in the pdf for this section
	Graph<int> g6 = create_graph(graph_size, 'p'); // 'p''w' - pdf prims graph
	g6.create_matrix();
	g6.printMatrix();                         // show the untrimmed graph first
	cout << endl;
	g6.printWeights();                          // and its weighted connections
	cout << "\nCost of graph: " << g6.getCost() << endl;
	cout << endl;
	g6.primsAlgo();
	cout << "\nCost of graph: " << g6.getCost() << endl;
    // ------------------------------------------------------------------------
    return 0;
}