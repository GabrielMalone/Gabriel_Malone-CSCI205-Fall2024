// ----------------------------------------------------------------------------
// GABRIEL MALONE / CS205 / WEEK 13 / GRAPHS
// ----------------------------------------------------------------------------
#include "GraphLogic/Graph.hpp"
#include "GraphLogic/CreateGraph.hpp"
#include "Traversals/BFS.hpp"
#include "BinaryTree/binaryTree.hpp"

using namespace std;

int main(){

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
    int graph_size = 16;    // create graph of size with randamized connections
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
    if (g3.stronglyConnected()){
        cout << "graph strongly connected " << endl;
    } else {
        cout << "graph not strongly connected" << endl;
    }
    // ------------------------------------------------------------------------
    cout << Colors::GRAY;
    cout << "" << endl;
    cout << "TASK FOUR - CYCLE DETECTION"                             << endl;
    cout << "" << endl;
    cout << Colors::RESET;
    // ------------------------------------------------------------------------
    graph_size = 10;        // create graph of size with randamized connections
    Graph<int> g5 = create_graph(graph_size, 'd');    // 't' for control graph
    g5.cyclesPresent();

    return 0;
}