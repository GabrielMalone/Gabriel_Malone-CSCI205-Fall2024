#include <string>
#include <iostream>
#include <unordered_map>
#include "Stack.h"

using namespace std;

string postfixConversion(string exp){
    // postfix expression string
    string pfexp = "";
  
    //we will use a hash map called prec to hold the precedence values for the operators which will be implemented with an unordered map.
    unordered_map<char, int>prec = {
        {'*',3},
        {'/',3},
        {'+',2},
        {'-',2},
        {'(',1},
    };
    //Create an empty stack called opstack for keeping operators. Create an empty vector for output.
    Stack<string> opstack;
    // Scan all the symbols one by one from left to right in the given Infix Expression.
    for (char c : exp){
        // If the reading symbol is an operand, then immediately append it to the Postfix Expression.
        if (c > 64 && c < 91 || c >= 0 && c <= 9)
        {
            pfexp += c ;
        }
    }

    return pfexp;

}

int main(){

    postfixConversion("goobertGOOBERT");

    return 0;
}