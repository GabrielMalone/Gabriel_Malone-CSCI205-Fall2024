// ----------------------------------------------------------------------------
// GABRIEL MALONE / CS205 / WEEK 13 / GRAPHS
// ----------------------------------------------------------------------------
#include "GraphLogic/Graph.hpp"
#include "GraphLogic/CreateGraph.hpp"
#include "Traversals/BFS.hpp"
#include "BinaryTree/binaryTree.hpp"

using namespace std;

int main(){
    // ------------------------------------------------------------------------
    cout << "--------------------------------------------------------" << endl;
    cout << "  TASK ONE - PRINT EACH LEVEL OF A BINARY TREE BIA BFS "  << endl;
    cout << "--------------------------------------------------------" << endl;
    // ------------------------------------------------------------------------
    AVL_BinarySearchTree<int> bst;         // this just left over from last lab
    bst.initialize(25, 'r', false);
    bst.print();
    cout << Colors::RESET << endl;
    // ------------------------------------------------------------------------
    cout << "--------------------------------------------------------" << endl;
    cout << "             TASK TWO - FIND SHORTEST PATH "              << endl;
    cout << "--------------------------------------------------------" << endl;
    // ------------------------------------------------------------------------
    int graph_size = 16;    // create graph of size with randamized connections
    Graph<int> g_s = create_graph(graph_size, 'r');       // r for random graph
    g_s.create_matrix(); //  graph via BFS
    g_s.shortestPath();
    // ------------------------------------------------------------------------
    cout << "--------------------------------------------------------" << endl;
    cout << "         TASK THREE - CHECK IF STRONGLY CONNECTED "       << endl;
    cout << "--------------------------------------------------------" << endl;
    // ------------------------------------------------------------------------
    graph_size = 10;        // create graph of size with randamized connections
    Graph<int> g3 = create_graph(graph_size, 'c');        // r for random graph
    if (g3.stronglyConnected()){
        cout << "graph strongly connected " << endl;
    } else {
        cout << "graph not strongly connected" << endl;
    }
     // ------------------------------------------------------------------------
    return 0;
}