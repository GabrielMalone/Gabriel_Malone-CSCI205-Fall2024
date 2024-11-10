//-------------------------------------------------------------------------------------------------
// GABRIEL MALONE / CS205 / WEEK 11 / HEAPS & BINARY TREES
//-------------------------------------------------------------------------------------------------
#ifndef HUFFMAN
#define HUFFMAN

#include "backend/ClosedHashTable.hpp"
#include "backend/print_graph.hpp"
#include "backend/histo_info.hpp"
#include "backend/char_code.hpp"
#include "backend/ArrayList.hpp"
#include "backend/min_heap.hpp"
#include "backend/binary_tree.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>


using namespace std;

class huffman {
    //---------------------------------------------------------------------------------------------
    private:

        ClosedHashTable<int> ht;                                         // hashtable for histogram
        ClosedHashTable<string>decoder;                 // map to handle final decoding of a string
        string s_to_encode = "";                                    // string that will be condoded
        string decoded_str = "";                                 // string to form a decoded string
        List<histo_info> h_info_list;                                 // list to hold the plot info
                                     // this list info will hold all the unique chars in the string
                                                                      // along with their frequency
        vector<BinaryTree<histo_info> > min_heap_vec;                // vector to hold binary trees   
        MinHeap<BinaryTree<histo_info> > mh;                           // for creating huffman tree
        BinaryTree<histo_info> bt;                                             // tree for encoding
        vector<char_code> cds;                                    // array for chars and their code
        List<char>uniques;                                   // list of unique chars for being lazy
        int max_freq = 0;                                     
        string my_compresssed_str = "";                 // hold at class level for easy portability
        
    public:
    //---------------------------------------------------------------------------------------------
    // CONSTRUCTORS
    //---------------------------------------------------------------------------------------------
        huffman(){};                                                     // no argument constructor
    //---------------------------------------------------------------------------------------------
    // CLASS METHODS
        //-----------------------------------------------------------------------------------------
        // MAKE HISTOGRAM - count how many of each character are present, place in map
        //-----------------------------------------------------------------------------------------
        void histogram(const string& s){
            s_to_encode = s;                   // save this string at class level for other methods
            for (char c : s){                            // take in the string count each character
                string a = "";                                            // convert char to string   
                a += c;                                                   // convert char to string
                if (! ht.contains(a)){                           // if the character is not present 
                    ht.put(a, 1);                                                // place it in map
                } else {                               // otherwise increment the value at that key
                    ht.get(a) ++ ;
                }
            }
            for (char d : s){
                string b = "";                                            // convert char to string   
                b += d;                                                   // convert char to string
                if (ht.get(b) > max_freq){
                    max_freq = ht.get(b);                                 // set max char frequency
                }
            }
            //--------------------------------------------------------------------------------------
            //create a list of the uniques
            //--------------------------------------------------------------------------------------
            for (char c : s_to_encode){                
                if (uniques.find(c) == -1)
                    uniques.insert(c);            
            }
            // for (int i  = 0 ; i  < uniques.length(); i ++){
            //     cout << uniques[i] << " ";
            // }
            // cout << endl;
            //--------------------------------------------------------------------------------------
            //create a list of the uniques and their frequencies
            //--------------------------------------------------------------------------------------
            for (size_t i  = 0 ; i  < uniques.length(); i ++){
                char d = uniques[i];
                string a = "";                                             // convert char to string   
                a += d;                                                    // convert char to string
                int val = ht.get(a);                                    // get the value at that key
                histo_info h_info;
                h_info.letter = d;                                  // store the histogram plot info
                h_info.frequency = val;                             // store the histogram plot info
                h_info_list.insert(h_info);                         // store the histogram plot info
            }
        }
        //------------------------------------------------------------------------------------------
        // PRINT HISTOGRAM - print the unique characters and their frequency
        //------------------------------------------------------------------------------------------
        void print_histogram(){    
            cout << endl; 
            int max_width = 0;                                              // set width of each bar
            string max_freq_str = "";
            max_freq_str = to_string(max_freq);  // width determinded by the length of longest digit
            max_width = 5 + max_freq_str.length(); // constant relates to spaces used no matter what         
            printTowers(h_info_list, max_width);                                    // print the bar 
            for (size_t w = 0; w < h_info_list.length(); w ++){                // print the bar info                               
                int val2 = ht.get(char_to_str(h_info_list[w].letter)); //convert char2string for key                                
                cout << " " 
                     << char_to_str(h_info_list[w].letter) 
                     << " = " 
                     << setw(max_freq_str.length()+2) 
                     << val2;           
            }
            cout << endl << " " ;
        }
        //------------------------------------------------------------------------------------------
        // INITIALIZE HEAP
        //------------------------------------------------------------------------------------------
        void initialize_priority_heap(){
            for (size_t i = 0 ; i < h_info_list.length(); i ++ ){   // iterate the unique chars info
                histo_info h = h_info_list[i];                                 
                BinaryTree<histo_info> b = {h};                // place this data into a Binary Tree
                min_heap_vec.emplace_back(b);               // create a vector of these binary trees
            }
            mh = (min_heap_vec);   // intialize the minPriority Heap with the vector created above ^
            cout << endl;
            cout << "Current MiniHeap" << endl;
            cout << "----------------" << endl;
            mh.print_tree();                                                      // confirm working
        }
        //------------------------------------------------------------------------------------------
        // BUILD TREE
        //------------------------------------------------------------------------------------------
        void build_tree(){
           
            initialize_priority_heap(); 

            for (int i = 0 ; i < (ht.m_size()-1) ; i ++){          // iterating for num unique chars
                BinaryTree<histo_info> *new_t = new BinaryTree<histo_info>();   // create a new tree 
                new_t->get_key().frequency = 0;                                        // initialize
                new_t->get_key().letter = '*';                         // set to something not avail
                try                                                      // try in case no nodes lef
                {                                                          // try until out of trees
                    BinaryTree<histo_info>* left = new BinaryTree<histo_info>(mh.extract_min()); //
                    new_t->insertLeft(*left);                         // make left child of new node
                    new_t->get_key().frequency += left->get_key().frequency;                 // freq
                    delete left;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return;
                }
                   try                                                   // try in case no nodes lef
                {                                                          // try until out of trees
                    BinaryTree<histo_info>* right = new BinaryTree<histo_info>(mh.extract_min());  
                    new_t->insertRight(*right);                      // make right child of new node
                    new_t->get_key().frequency += right->get_key().frequency;                // freq
                    delete right;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    return;
                }

                mh.insert(*new_t);                  // insert this new binary tree into the miniheap
                delete new_t;
            }
            bt = mh.heap[1];          // save the final binary tree at class level for other methods
        }
        //------------------------------------------------------------------------------------------
        // BUILD CODE via recursive method in the binary class 'inorder'
        //------------------------------------------------------------------------------------------
        string create_code(){
            string code = "";                        // pass this in via reference to build the code
            bt.inorder(cds, code);             // also pass in vector to store the code as it builds
            return code;                        
        }
        //------------------------------------------------------------------------------------------
        // PRINT THE CODES STORED IN THE VECTOR OF STRUC 'CHAR_CODE"
        //------------------------------------------------------------------------------------------
        void print_codes(){
            cout << endl;
            cout  << "Huffman Codes for Each Char" << endl;
			cout  << "---------------------------" << endl;
            cout << endl;
            for (unsigned long i = 0 ; i < cds.size() ; i ++ ){   // to see if the char code created
                cout << cds[i] << endl;
            }
            cout << endl;
            cout << endl;
        }
        //-------------------------------------------------------------------------------------------
        // PRINT THE CODES STORED IN THE VECTOR OF STRUC 'CHAR_CODE"
        //-------------------------------------------------------------------------------------------
        void print_final_tree(){
            cout << endl;
            cout  << "Final Heapified Tree" << endl;
			cout  << "--------------------" << endl;
            bt.printTree();                                 // confirmation of correct tree formation
        }
        //-------------------------------------------------------------------------------------------
        // CREATE THE KEY - didn't end up using this
        //-------------------------------------------------------------------------------------------
        A_List<char_code> create_huffman_key(){
            A_List<char_code> final (28);         // array list of 27 indexes for the code placements

            for (unsigned long g = 0 ; g < cds.size(); g ++ ){     // character code in correct index
                char_code cc = cds[g];
                int index = cc.letter - 'A';                 // set char A = to index 0, B to 1, etc.
                if (cc.letter == ' ')         // set these special chars so they aren't out of bounds
                    index = 26;
                if (cc.letter == '\\')        // set these special chars so they aren't out of bounds
                    index = 27;
                final.insert(cc, index);                 // place character and code in correct index              
            }
            return final;
        }
        //-------------------------------------------------------------------------------------------
        // CREATE HUFFMAN CODE - didn't end up using this
        //-------------------------------------------------------------------------------------------
         A_List<char_code> build_huffman_code(){
            string code = create_code();        // string passed as reference to be built recursively              
            print_codes();// string will placed into a vector at its various build stages //  confirm
            print_final_tree();                     // confirm the final tree is properly constructed
            return create_huffman_key(); // create a list that holds the char and key at proper index
        }
        //-------------------------------------------------------------------------------------------
        // CREATE THE KEY via map
        //-------------------------------------------------------------------------------------------
        void create_huffman_key_map(){
            for (unsigned long g = 0 ; g < cds.size(); g ++ ){   // place character and code in index
                char_code cc = cds[g];
                string current_char = "";
                current_char += cc.letter;
                decoder.put(current_char, cc.code);                      // key = char , value = code
            }
        }

        //-------------------------------------------------------------------------------------------
        // CREATE HUFFMAN CODE MAP, seems like this way will be simpler
        //-------------------------------------------------------------------------------------------
         void build_huffman_code_map(){
            string code = create_code();        // string passed as reference to be built recursively              
            print_codes();// string will placed into a vector at its various build stages //  confirm
            print_final_tree();                     // confirm the final tree is properly constructed
            create_huffman_key_map();    // create a list that holds the char and key at proper index
        }

        //-------------------------------------------------------------------------------------------
        // COMPRESS A STRING INTO HUFFMAN CODE
        //-------------------------------------------------------------------------------------------
        string compress(const string& og_string){
            string compressed_string = "";      // call all these varius stages for building the code
            this->s_to_encode = og_string;            // set the passed in sting to the class' string
            histogram(this->s_to_encode);                                         // create histogram
            print_histogram();                                                     // print histogram
            build_tree();                                       // build the binary tree via miniheap
            build_huffman_code_map();                        // build huffman code based on this tree
            for (char c : og_string){
                string next_letter = decoder.get(char_to_str(c));
                compressed_string += next_letter;
            }
            cout << "ORIGINAL" << endl << endl 
            << og_string << endl << endl 
            << "COMPRESSED " << endl << endl;
            return compressed_string;
        }
        //-------------------------------------------------------------------------------------------
        // MORE READABLE VESION WITH SPACES BETWEEN EACH CHAR
        //-------------------------------------------------------------------------------------------
        void print_compressed_string(const string& og_string){
            this->s_to_encode = og_string;           // set the passed in string to the class' string
            histogram(this->s_to_encode);                                         // create histogram
            print_histogram();                                                     // print histogram
            build_tree();                                       // build the binary tree via miniheap
            build_huffman_code_map();                        // build huffman code based on this tree
            cout << endl;
            for (char c : og_string){
                string next_letter = decoder.get(char_to_str(c));
                cout << next_letter;
                cout << " ";
            }
            cout << endl;
        }
        //-------------------------------------------------------------------------------------------
        // INFLATE A STRING INTO HUFFMAN CODE RECURSIVELY
        //-------------------------------------------------------------------------------------------
        string inflate (string& huff_code){              // pass in the code built during compression
            cout << huff_code << endl;                                    // for visualization output
            unsigned long index = 0;
            while (index < huff_code.length())        // index will move along the length of the code
                bt.inflate(this->decoded_str, huff_code, index);   // recursively follow path of code
            cout << endl <<  "INFLATED" << endl << endl;       // decoded string will build each loop 
            return this->decoded_str;                                  
        }
};

#endif 