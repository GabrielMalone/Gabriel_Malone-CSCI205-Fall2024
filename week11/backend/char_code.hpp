#ifndef CHAR_CODE
#define CHAR_CODE

#include <string>
#include <iostream>

using namespace std;

struct char_code {

    char letter;
    string code;

    char_code(char l, string c){
        this->letter = l;
        this->code = c;
    }

    bool operator<(const char_code& other){
        return this->letter < other.letter;
    }
    bool operator>(const char_code& other){
        return this->letter > other.letter;
    }
};

 ostream& operator << (ostream &stream, const char_code& char_code)  {
        stream << "[" << char_code.letter << "  " << char_code.code << "]";
	    return stream;
    }

#endif