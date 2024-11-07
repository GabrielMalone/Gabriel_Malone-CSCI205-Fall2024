#include "huffman.hpp"
#include "backend/random_string.hpp"
#include <chrono>
#include <thread>

using namespace std;


int main(){
    huffman h;
    //while (true){
        // cout << "\033[2J";                        // for animation effect                                              
        // cout << "\033[H";                        // for animation effect 
        int string_len = 25;
        string rand = get_random_string(string_len);
        h.histogram("GOOBERT");
        h.print_histogram();
        h.build_tree();
        // this_thread::sleep_for(chrono::milliseconds(100));   // speed of display of algo
        h.build_huffman_code();
    // }
    return 0;
}