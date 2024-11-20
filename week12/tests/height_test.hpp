#ifndef HEIGHT_TEST
#define HEIGHT_TEST

#include <vector>
#include <cmath>
#include "../backend/Height_Data.hpp"
#include "../backend/generate_vectors.hpp"
#include "../backend/ClosedHashTable.hpp"
#include "../backend/saveHeightData.hpp"
#include "../backend/graph_height_tests.hpp"
#include "../backend/avg_height.hpp"
#include "../bst_helpers.hpp/divide_conquer.hpp"
#include "../avl_t.hpp"

using namespace std;

random_device rd;                                                   // random number generator for random val assignment
mt19937 gen(rd());
//----------------------------------------------------------------------------------------------------------------------
ClosedHashTable<Height_Data> results_random_random;                                      // tables to save the test data
ClosedHashTable<Height_Data> results_ordered_random;
ClosedHashTable<Height_Data> results_ordered_BME;
ClosedHashTable<Height_Data> results_ordered_ordered;
ClosedHashTable<Height_Data> results_ordered_MIDDLE;
ClosedHashTable<Height_Data> results_ordered_LR_optimized;
ClosedHashTable<Height_Data> results_ordered_Divide_Conquer;
ClosedHashTable<Height_Data> results_ordered_AVL;
ClosedHashTable<Height_Data> results_ordered_AVL_DandQ;
ClosedHashTable<Height_Data> ideal_results;                            // for comparing to the ideal tree height (log2N)
//----------------------------------------------------------------------------------------------------------------------
void height_testing(){

    int i = 0 ; 
    while (i < 100){                                                                           // num experiments to run

        int tree_size = 1000;                                                           // tree size for each experiment
        //--------------------------------------------------------------------------------------------------------------
        // CONTROL - IDEAL TREE HEIGHT FOR COMPARISON  - LOG 2 N
        //--------------------------------------------------------------------------------------------------------------
        Height_Data ideal;
        ideal.tree_height = log2(tree_size) * 1.44;
        ideal.trial_num = i + 1;
        ideal.trial_method = "ideal";
        ideal_results.put(to_string(i+1), ideal);
        //--------------------------------------------------------------------------------------------------------------
        // TEST 1 - RANDOMIZED VECTOR WITH RANDOMIZED INSERTION
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_a;
        BinarySearchTree<int>bst_a;                                                                           // new bst
        int size = tree_size;
        char type = 'r';
        int range = size;
        vector<int>a(size);
        generate_vector(size, type, a, range);  
        while (a.size() > 0){     
            uniform_int_distribution<> dist(0,  a.size()-1);         // range from 0 to vector size for the rnadom value
            int rand_index = dist(gen);                                                    // get the valid random index                                            
            bst_a.insert(a[rand_index]);
            a.erase(a.begin() + rand_index);                                          // remove that val from the vector
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_a.tree_height = bst_a.get_height();                                   // save the data from the above run
        h_data_a.trial_num = i + 1;                                                    // place the data into the struct
        h_data_a.trial_method = "random_random";
        results_random_random.put(to_string(i+1), h_data_a);                         // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 2 - ORDERED VECTOR WITH RANDOMIZED INSERTION O(N) + O(logN)
        //          randomly select an index from a vector of ordered items. works fairly well, results in a tree that
        //          is, on average, 2x the height of the ideal tree. 
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_b;
        BinarySearchTree<int>bst_b;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>b(size+1);
        generate_vector(size, type, b, range);
        while (b.size() > 0){     
            uniform_int_distribution<> dist(0,  b.size()-1);         // range from 0 to vector size for the rnadom value
            int rand_index = dist(gen);                                                    // get the valid random index                                                         
            bst_b.insert(b[rand_index]);
            b.erase(b.begin() + rand_index);                                          // remove that val from the vector
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_b.tree_height = bst_b.get_height();                                   // save the data from the above run
        h_data_b.trial_num = i + 1;                                                    // place the data into the struct
        h_data_b.trial_method = "ordered_random";
        results_ordered_random.put(to_string((i+1)), h_data_b);                      // then place the struct in the map
        //----------------------------------q---------------------------------------------------------------------------
        // TEST 3 - ORDERED VECTOR W LEFT, MIDDLE, RIGHT INSERTIONS - results in a tree of height = N/2 | O(N) + O(logN)
        //       Idea here was to take the left side of a vector, insert, take the middle, insert, tke the right, insert
        //       results in a very unbalanced tree.
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_c;
        BinarySearchTree<int>bst_c;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>c(size);
        generate_vector(size, type, c, range);
        while (c.size() > 3){
            int middle = c[c.size()/2];
            bst_c.insert(middle);
            c.erase(c.begin() + c.size()/2);           
            int left = c[0];
            bst_c.insert(left);
            c.erase(c.begin() + 0);                                                   // remove that val from the vector
            int right = c[c.size()-1];
            bst_c.insert(right);
            c.erase(c.begin() + c.size()-1);                                        
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_c.tree_height = bst_c.get_height();                                   // save the data from the above run
        h_data_c.trial_num = i + 1;                                                    // place the data into the struct
        h_data_c.trial_method = "ordered_BME";
        results_ordered_BME.put(to_string((i+1)), h_data_c);                         // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 4 - ORDERED VECTOR WITH ORDERED INSERTS - results in a linked list, Tree size = N |  O(N) + O(logN)
        //          results in a linked list
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_d;
        BinarySearchTree<int>bst_d;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>d(size);
        generate_vector(size, type, d, range);
        while (d.size() > 0){       
            int left = d[0];
            bst_d.insert(left);
            d.erase(d.begin() + 0);                                                   // remove that val from the vector                                 
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_d.tree_height = bst_d.get_height();                                   // save the data from the above run
        h_data_d.trial_num = i + 1;                                                    // place the data into the struct
        h_data_d.trial_method = "ordered_ordered";
        results_ordered_ordered.put(to_string((i+1)), h_data_d);                     // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 5 - ORDERED VECTOR WITH MIDDLE INSERTS -  results in tree height of N/3 |  O(N) + O(logN)
        //          results in something similar as to when inserting data in descending order
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_e;
        BinarySearchTree<int>bst_e;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>e(size);
        generate_vector(size, type, e, range);
        while (e.size() > 3){
            int middle = e[(e.size()/2)];
            bst_e.insert(middle);
            e.erase(e.begin() + e.size()/2);           
            int left = e[(e.size()/2)-1];
            bst_e.insert(left);
            e.erase(e.begin() + e.size()/2)-1;                                        // remove that val from the vector
            int right = e[(e.size()/2)+1];
            bst_e.insert(right);
            e.erase(e.begin() + e.size()/2)+1;                                        
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_e.tree_height = bst_e.get_height();                                   // save the data from the above run
        h_data_e.trial_num = i + 1;                                                    // place the data into the struct
        h_data_e.trial_method = "ordered_MIDDLE";
        results_ordered_MIDDLE.put(to_string((i+1)), h_data_e);                      // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 6 - ORDERED VECTOR WITH RANDOM INSERTION + LEFT AND RIGHT OPTIMIZATION |  O(N) + O(logN)
        //          Idea here was I'd take a random index of an ordered array then take the values to the left and right 
        //          of this to be inserted as well. performs basically as well as random inserts alone. 
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_f;
        BinarySearchTree<int>bst_f;   
        size = tree_size;
        type = 'r';
        range = size;
        vector<int>f(size);
        generate_vector(size, type, f, range);
        while (f.size() > 0){ 
            uniform_int_distribution<> dist(0, f.size()-1);          // range from 0 to vector size for the rnadom value  
            int rand_index = dist(gen);
            int m = f[rand_index];
            bst_f.insert(m);
            f.erase(f.begin() + rand_index); 
            if (rand_index-1 > 0){
                int m_1 = f[rand_index-1];
                bst_f.insert(m_1);
                f.erase(f.begin() + rand_index-1);
            }
            if (rand_index + 1 < f.size()){
                int m_2 = f[rand_index+1];
                bst_f.insert(m_2);
                f.erase(f.begin() + rand_index+1);                              
            }
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_f.tree_height = bst_f.get_height();                                   // save the data from the above run
        h_data_f.trial_num = i + 1;                                                    // place the data into the struct
        h_data_f.trial_method = "ordered_LR_optimized";
        results_ordered_LR_optimized.put(to_string((i+1)), h_data_f);                // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 7 - DIVIDE AND CONQUER RECURSIVE METHOD |  O(logN) + O(logN)
        //          This perofrms at ideal or nearly ideal levels because the ideal middle/parent node is selecting each
        //          time and so there is a greater liklihood of each subtree being perfectly balanced
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_g;
        BinarySearchTree<int>bst_g;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>g(size);
        generate_vector(size, type, g, range);
        divide_conquer(g, bst_g);
        //--------------------------------------------------------------------------------------------------------------
        h_data_g.tree_height = bst_g.get_height();                                   // save the data from the above run
        h_data_g.trial_num = i + 1;                                                    // place the data into the struct
        h_data_g.trial_method = "ordered_Divide_Conquer";
        results_ordered_Divide_Conquer.put(to_string((i+1)), h_data_g);              // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 8 - SELF BALANCING AVL TREE |  O(logN)
        //          This perofrms at ideal or nearly ideal levels because the ideal middle/parent node is selecting each
        //          time and so there is a greater liklihood of each subtree being perfectly balanced
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_h;
        AVL_BinarySearchTree<int>bst_h;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>h(size);
        generate_vector(size, type, h, range);
        while (h.size() > 0){       
            int left = h[0];
            bst_h.insert(left);
            h.erase(h.begin() + 0);                                                   // remove that val from the vector                                 
        }
        //--------------------------------------------------------------------------------------------------------------
        h_data_h.tree_height = bst_h.get_height();                                   // save the data from the above run
        h_data_h.trial_num = i + 1;                                                    // place the data into the struct
        h_data_h.trial_method = "ordered_AVL";
        results_ordered_AVL.put(to_string((i+1)), h_data_h);              // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        // TEST 9 - SELF BALANCING AVL TREE with DIVIDE AN CONQUER |  O(logN)
        //          This perofrms at ideal or nearly ideal levels because the ideal middle/parent node is selecting each
        //          time and so there is a greater liklihood of each subtree being perfectly balanced
        //--------------------------------------------------------------------------------------------------------------
        Height_Data h_data_j;
        AVL_BinarySearchTree<int>bst_j;   
        size = tree_size;
        type = 'a';
        range = size;
        vector<int>j(size);
        generate_vector(size, type, j, range);
        divide_conquer(j, bst_j);
        //--------------------------------------------------------------------------------------------------------------
        h_data_j.tree_height = bst_j.get_height();                                   // save the data from the above run
        h_data_j.trial_num = i + 1;                                                    // place the data into the struct
        h_data_j.trial_method = "ordered_AVL_DandQ";
        results_ordered_AVL_DandQ.put(to_string((i+1)), h_data_j);              // then place the struct in the map
        //--------------------------------------------------------------------------------------------------------------
        i ++ ;                                                                                // move to next test round
    }
    
    //------------------------------------------------------------------------------------------------------------------
    // saveHeightData(results_ordered_BME, "ordered_BME");
    // saveHeightData(results_ordered_ordered, "ordered_ordered");  
    // saveHeightData(results_ordered_MIDDLE, "ordered_MIDDLE");  
    saveHeightData(results_random_random, "random_random");
    saveHeightData(results_ordered_random, "ordered_random");
    saveHeightData(results_ordered_LR_optimized, "ordered_LR_optimized");
    saveHeightData(results_ordered_Divide_Conquer, "ordered_Divide_Conquer");
    saveHeightData(results_ordered_AVL, "ordered_AVL");
    saveHeightData(results_ordered_AVL_DandQ, "ordered_AVL_DandQ");
    saveHeightData(ideal_results, "IDEAL HEIGHT");

    // cout << "avg ordered_BME height: "  << avg_height(results_ordered_BME) << endl;
    // cout << "avg ordered_ordered height: " << avg_height(results_ordered_ordered) << endl;
    // cout << "avg ordered_MIDDLE height: " << avg_height(results_ordered_MIDDLE) << endl;
    cout << "avg random_random height: " << avg_height(results_random_random) << endl;
    cout << "avg ordered_random height: " << avg_height(results_ordered_random) << endl;
    cout << "avg LR_optimized height: " << avg_height(results_ordered_LR_optimized) << endl;
    cout << "avg Divide_Conquer height: " << avg_height(results_ordered_Divide_Conquer) << endl;
    cout << "avg ordered_AVL: " << avg_height(results_ordered_AVL) << endl;
    cout << "avg ordered_AVL_DandQ: " << avg_height(results_ordered_AVL_DandQ) << endl;

    cout << "ideal height: " << avg_height(ideal_results) << endl;

    //------------------------------------------------------------------------------------------------------------------
    graph_height();
}
//----------------------------------------------------------------------------------------------------------------------

#endif  