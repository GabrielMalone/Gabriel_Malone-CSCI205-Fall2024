#ifndef H_COLORS
#define H_COLORS

#include <string>

using namespace std;

namespace Colors {

    string RESET = "\033[0m";   // ANSI escape code variables
    string BLACK = "\033[30m";
    string RED = "\033[31m";
    string GREEN = "\033[32m";
    string YELLOW = "\033[33m";
    string BLUE = "\033[34m";
    string MAGENTA = BLUE;
    string CYAN = "\033[36m";
    string WHITE = "\033[37m"; 
    
}

#endif