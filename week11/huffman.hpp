#ifndef HUFFMAN
#define HUFFMAN

#include "backend/ClosedHashTable.hpp"
#include "backend/print_graph.hpp"
#include "backend/histo_info.hpp"
#include "backend/char_code.hpp"
#include "backend/ArrayList.hpp"
#include "min_heap.hpp"
#include "binary_tree.hpp"
#include <string>
#include <vector>
#include <algorithm>


using namespace std;


class huffman {

    private:

        ClosedHashTable<int> ht;                            // hashtable for histogram
        string s_to_encode = "";                       // string that will be condoded
        List<histo_info> h_info_list;                    // list to hold the plot info
                        // this list info will hold all the unique chars in the string
                                                         // along with their frequency
        vector<BinaryTree<histo_info> > min_heap_vec;   // vector to hold binary trees   
        MinHeap<BinaryTree<histo_info> > mh;              // for creating huffman tree
        BinaryTree<histo_info> bt;                                // tree for encoding
        vector<char_code> cds;                       // array for chars and their code
        List<char>uniques;                      // list of unique chars for being lazy
        int max_freq = 0;                                       
        
    public:
    //--------------------------------------------------------------------------------
    // CONSTRUCTORS
    //--------------------------------------------------------------------------------
        huffman(){};                                        // no argument constructor
    //--------------------------------------------------------------------------------
    // CLASS METHODS
        //----------------------------------------------------------------------------
        // MAKE HISTOGRAM - count how many of each character are present, place in map
        //----------------------------------------------------------------------------
        void histogram(const string& s){
            s_to_encode = s;      // save this string at class level for other methods
            for (char c : s){               // take in the string count each character
                string a = "";                               // convert char to string   
                a += c;                                      // convert char to string
                if (! ht.contains(a)){              // if the character is not present 
                    ht.put(a, 1);                                   // place it in map
                } else {                  // otherwise increment the value at that key
                    ht.get(a) ++ ;
                }
            }
            for (char d : s){
                string b = "";                               // convert char to string   
                b += d;                                      // convert char to string
                if (ht.get(b) > max_freq){
                    max_freq = ht.get(b);                    // set max char frequency
                }
            }
            //-----------------------------------------------------------------------
            //create a list of the uniques
            //-----------------------------------------------------------------------
            for (char c : s_to_encode){                
                if (uniques.find(c) == -1)
                    uniques.insert(c);            
            }
            // for (int i  = 0 ; i  < uniques.length(); i ++){
            //     cout << uniques[i] << " ";
            // }
            // cout << endl;
            //-----------------------------------------------------------------------
            //create a list of the uniques and their frequencies
            //-----------------------------------------------------------------------
            for (int i  = 0 ; i  < uniques.length(); i ++){
                char d = uniques[i];
                string a = "";                               // convert char to string   
                a += d;                                      // convert char to string
                int val = ht.get(a);                      // get the value at that key
                histo_info h_info;
                h_info.letter = d;                    // store the histogram plot info
                h_info.frequency = val;               // store the histogram plot info
                h_info_list.insert(h_info);           // store the histogram plot info
            }
        }
        //----------------------------------------------------------------------------
        // PRINT HISTOGRAM - print the unique characters and their frequency
        //----------------------------------------------------------------------------
        void print_histogram(){    
            cout << "String to encode: " << s_to_encode << endl;                     
            printTowers(h_info_list);
            for (int w = 0; w < h_info_list.length(); w ++){
                char e = h_info_list[w].letter;
                string g = "";                               // convert char to string   
                g += e;                                      // convert char to string
                int val2 = ht.get(g);                     // get the value at that key
                cout << " " << g << " = " << val2 << " ";           
            }
            cout << endl << " " ;
        }
        //------------------------------------------------------------------------------------------
        // INITIALIZE HEAP
        //------------------------------------------------------------------------------------------
        void initialize_priority_heap(){
            for (int i = 0 ; i < h_info_list.length(); i ++ ){     // iterate the unique chars info
                histo_info h = h_info_list[i];                                 
                BinaryTree<histo_info> b = {h};               // place this data into a Binary Tree
                min_heap_vec.emplace_back(b);              // create a vector of these binary trees
            }
            mh = (min_heap_vec);  // intialize the minPriority Heap with the vector created above ^
            cout << endl;
            mh.print_tree();                                                     // confirm working
        }
        //------------------------------------------------------------------------------------------
        // BUILD TREE
        //------------------------------------------------------------------------------------------
        void build_tree(){
           
            initialize_priority_heap(); 
            for (size_t i = 0 ; i < ht.m_size()-1 ; i ++){ // iterating for duration of unique chars
                BinaryTree<histo_info> new_t;                         // create a new tree each loop
                new_t.get_key().frequency = 0;                                         // initialize
                new_t.get_key().letter = '*';                          // set to something not avail
                try                                                      // try in case no nodes lef
                {                                                          // try until out of trees
                    BinaryTree<histo_info> left = mh.extract_min();               // pull out a tree
                    BinaryTree<histo_info> right = mh.extract_min();              // pull out a tree
                    new_t.insertLeft(left);                           // make left child of new node
                    new_t.insertRight(right);                        // make right child of new node
                    new_t.get_key().frequency += left.get_key().frequency;                   // freq
                    new_t.get_key().frequency += right.get_key().frequency;                  // freq
                    mh.insert(new_t);               // insert this new binary tree into the miniheap
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return;
                }
            }
        }
        //------------------------------------------------------------------------------------------
        // CREATE HUFFMAN CODE
        //------------------------------------------------------------------------------------------
        string build_huffman_code(){

            cout << endl;
            string code = "";                        // pass this in via reference to build the code
            mh.heap[1].inorder(cds, code, ht.m_size()-1);  // create code via recursion through tree
            cout << endl;

            for (int i = 0 ; i < cds.size() ; i ++ ){// checking to see if the char and code created
                cout << cds[i] << endl;
            }
            cout << endl;
            mh.heap[1].printTree();                        // confirmation of correct tree formation
            cout << endl;

            A_List<char_code> final (26);        // array list of 27 indexes for the code placements

            for (int g = 0 ; g < cds.size(); g ++ ){    // place character and code in correct index
                char_code cc = cds[g];
                int index = cc.letter - 'A';                 // set char A = to index 0, B to 1, etc.
                final.insert(cc, index);                        
            }
            for (int i = 0 ; i  < 26 ; i ++ ){                                // confirm this worked
                cout << final[i] << endl;
            }
            return code;
        }
};

#endif 