//-------------------------------------------------------------------------------------------------
// GABRIEL MALONE / CS205 / WEEK 11 / HEAPS & BINARY TREES
//-------------------------------------------------------------------------------------------------
#include "huffman.hpp"
#include "backend/FileOpener.hpp"

using namespace std;

int main(){
    string text = textLoader("passage.txt");              // get a string of text or enter your own
    huffman h;                 // create huffman object that can handle all the compression methods       
    string compressed_t = h.compress(text);                // can enter whatever text you want here
    string decompressed_t = h.inflate(compressed_t);         // take huffman code and decompress it
    cout << decompressed_t << endl;                                                 // show results
    
    return 0;

}