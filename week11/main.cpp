#include "huffman.hpp"
#include "backend/FileOpener.hpp"

using namespace std;

int main(){
    
    huffman h;
    string text = textLoader("text_to_encode.txt");
    //string text = "goobert";
    string compressed_t = h.compress(text); // can enter whatever text you want here
    string decompressed_t = h.inflate(compressed_t);
    cout << decompressed_t << endl;

    return 0;
}