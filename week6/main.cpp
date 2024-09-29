// GABRIEL MALONE // CSCI205 // WEEK 6 // RECURSION
//-----------------------------------------------------------------------------------------------------
#include <iostream>
#include<random>        
#include "backend/List.hpp"                                   // seeing how my data structure does here
#include "backend/FileSaver.hpp"
#include "backend/Stack.hpp"
 
using namespace std;            
//-----------------------------------------------------------------------------------------------------
// Global vars
int algo_count_rec = 0;                                            // track how many times an algo runs
int algo_count_itr = 0;
//-----------------------------------------------------------------------------------------------------
int EUC_GCD_REC(int, int);
int EUC_GCD_ITR(int, int);
string reverse_string_itr(string&);
string reverse_string_rec(string);
void recursive_print_count(int, int);
int recursive_sum_array(int*, int);
//-----------------------------------------------------------------------------------------------------
//  MAIN
//-----------------------------------------------------------------------------------------------------
int main(){
    //-------------------------------------------------------------------------------------------------
    //  COMPARE ITERATIVE VS RECURSIVE FOR EUCLID'S GCD with a single run to confirm both work
    //-------------------------------------------------------------------------------------------------
    int a = 120000;
    int b = 89;
    //-------------------------------------------------------------------------------------------------
    //  ITERATIVE EUCLIDs ALGO
    //-------------------------------------------------------------------------------------------------
    algo_count_itr = 0;                                                                // reset counter                                            
    cout << "Via the iterative method, the GCD of "     
         << a 
         << " and " 
         << b 
         << " is " 
         << EUC_GCD_ITR(a, b)                                                               // run algo
         << ". this algorith ran " 
         << algo_count_itr                                                      // algo time complexity
         << " time(s)." 
         << endl;
    //-------------------------------------------------------------------------------------------------
    //  RECURSIVE EUCLIDs ALGO
    //-------------------------------------------------------------------------------------------------
    algo_count_rec = 0;                                                                // reset counter 
    cout << "Via the recursive method, the GCD of "
         << a 
         << " and " 
         << b 
         << " is " 
         << EUC_GCD_REC(a, b)                                                              // run alog
         << ". this algorith ran " 
         << algo_count_rec                                                     // algo time complexity
         << " time(s)." 
         << endl;
    //-------------------------------------------------------------------------------------------------
    //  RUN AND COMAPRE A VRIETY OF GCD TESTS / AVERAGE AND COMPARE NUMBER OF OPERATIONS
    //-------------------------------------------------------------------------------------------------
    algo_count_itr = 0;                                                              // restet counters
    algo_count_rec = 0;
    int c = 999;                                                    // starting value a for GCD algos
    int index = 0;

    List<int> rec_res;                                                     // hold results for rec algo
    List<int> itr_res;                                                     // hold results for itr algo    
    random_device rd;                             // random number generator for random dorm assignment
    mt19937 gen(rd());
                                            
    uniform_int_distribution<> dist(1,  100);     // range from 0 index to num of dorms - 1 for 0 index                                                
    cout << "calculating efficiency of both algorithms over 99999 iterations... " << endl;
    for (int i = c ; i > 0; i  -- ){
        int random_int = dist(gen);  
        EUC_GCD_ITR(c,random_int);
        EUC_GCD_REC(c,random_int);                     // run the algos - dont care about actual result
        itr_res.insert(algo_count_itr, index);                         // place result of run into list
        rec_res.insert(algo_count_rec, index);                         // place result of run into list
        //cout << i << endl;                                          // see if frozen or still running
        index ++ ;
        algo_count_itr = 0;                                                          // restet counters
        algo_count_rec = 0;
    }
    //-------------------------------------------------------------------------------------------------
    //  FIND THE AVERAGE NUMBER OF OPERATIONS FOR EACH ALGO
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //  iterative algo average num of operations
    //-------------------------------------------------------------------------------------------------
    int sum_a = 0;
    Node<int>* n = itr_res.get_head();
    while (n != NULL){
        sum_a += n->data;
        n = n->next;
    }

    cout << "The average number of operations for the iterative algorithm was: "
        << "length of list: "
        << itr_res.length()
        << " / "
        << "sum of results in list: "
        << sum_a
        << " = "
        << sum_a / itr_res.length() 
        << endl;

    //-------------------------------------------------------------------------------------------------
    //  recursive algo average num of operations
    //-------------------------------------------------------------------------------------------------
    int sum_b = 0;                                                   // iterate through list of reuslts
    Node<int>* m = rec_res.get_head();
    while (m != NULL){
        sum_b += m->data;
        m = m->next;
    }
    
    cout << "The average number of operations for the recursive algorithm was: "
        << "length of list: "
        << rec_res.length()
        << " / "
        << "sum of results in list: "
        << sum_b
        << " = "
        << sum_b / rec_res.length() 
        << endl;

    //-------------------------------------------------------------------------------------------------
    // REVERSE STRING ITERATE METHOD
    //-------------------------------------------------------------------------------------------------
    string str_to_reverse = "Gabriel123!";
    cout << "Reverse string '"
         << str_to_reverse
         << "' via iterating and Stack: "
         << reverse_string_itr(str_to_reverse)
         << endl;

    //-------------------------------------------------------------------------------------------------
    // REVERSE STRING RECURSIVE METHOD
    //-------------------------------------------------------------------------------------------------
    cout << "Reverse string '"
         << str_to_reverse
         << "' via recursion: "
         << reverse_string_rec(str_to_reverse)
         << endl;

    //-------------------------------------------------------------------------------------------------
    // RECURSIVE COUNT METHOD
    //-------------------------------------------------------------------------------------------------   
        recursive_print_count(1,50);

    //-------------------------------------------------------------------------------------------------
    // RECURSIVE SUM ARRAY METHOD
    //------------------------------------------------------------------------------------------------- 
        int arr[] = {5, 4, 3, 2, 1};
        cout << recursive_sum_array(arr, 5) << endl;
    //-------------------------------------------------------------------------------------------------
    // run graphs
    //-------------------------------------------------------------------------------------------------
    saveData(rec_res, "Euclid's Recursive Algorithm");
    saveData(itr_res, "Euclid's Iterative Algorithm");
    int status = system("python3 backend/plot.py"); 
	if (status == -1)
	{
		cerr << "\npython script failed :[\n" << endl;
	} else {
		cout << "\n  graphs created successfully!\n" << endl;
		cout << "  all .txt data cleared\n" << endl;
	}

    
    
    return 0;
}

//-----------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS

//-----------------------------------------------------------------------------------------------------
// EUCLID'S GCD RECURSIVE ALGO
//-----------------------------------------------------------------------------------------------------

int EUC_GCD_REC(int a, int b){                                // take in two numbers and find their GCD
    if (b == 0){                                                          // base case, if b = 0, done.
        return a;                                                                     // return the GCD
    }
    algo_count_rec ++;
    return EUC_GCD_REC(b, a%b);                         // recursively call, switching parameter values
                                                       // and passing 'b' as the remainder of 'a' / 'b'
}    

//-----------------------------------------------------------------------------------------------------
// EUCLID'S GCD ITERATIVE ALGO
//-----------------------------------------------------------------------------------------------------

int EUC_GCD_ITR(int a, int b){                                             // time complexity O(log(n)) 
        while (a != b) {                              // since problem size cut in half every iteration
        if (a > b)
            a = a - b;
        else
            b = b - a;
        algo_count_itr ++;
    }
   
    return a;
}

//-----------------------------------------------------------------------------------------------------
// ITERATIVE REVERSE STRING METHOD
//-----------------------------------------------------------------------------------------------------

string reverse_string_itr(string& str){                             // time complexity for this is O(n)
    string rev_str;                                                    // since two un-nested for-loops
    Stack<char>char_stack;                                                  // stack to hold characters 
    for (int i = 0 ; i  < (int)str.length() ; i ++){    // stack is LIFO, this will result in a reverse 
        char_stack.push(str[i]);// string by pushing to stack each character during a forward iteration
    }                                                                         // of the original string
    for (int i = 0 ; i < (int)str.length() ; i ++ ){
        rev_str += char_stack.pop();
    }
    return rev_str;
}
//-----------------------------------------------------------------------------------------------------
// RECURSIVE REVERSE STRING METHOD
//-----------------------------------------------------------------------------------------------------

// This function takes in a string as a parameter.
// If the string's length is 0, the function returns the string ("") and exits the functions's scope.
// At which point whatever was returned to the stack unwinds in a LIFO pattern.
// Otherwise, the function takes the back character of the current string and returns it to the stack,
// with the operand '+'.
// then the function is called recursively, passing the same string (minus the back character) as 
// a parameter, thus reudcing the string size by one and satfisfying all three requirements for a 
// recursive function (base case, manipulation of size of main variable (reduction in this case)) and  
// the calling of the same function until base case met. 

string reverse_string_rec(string str){                                  
    if (str.length() == 0){                                            // base case is string size = 0
        return str;
    }
    char back = str[str.length()-1];                                   // get back character of string
    return back + reverse_string_rec(str.substr(0, str.length()-1));   // build back char by back char
}
//-----------------------------------------------------------------------------------------------------
// RECURSIVE PRINT COUNT METHOD
//-----------------------------------------------------------------------------------------------------

// this method is similar to the above method, but instead of building up the stack, since nothing
// needs to unwound, you can simply print 'n' and its updates (n+1). the function will then break and 
// exit its scope when n equals the base case. 

void recursive_print_count(int n, int base){                            // pass in start and end value
    if (n == base){                                                              // if n = base , quit
        cout << n << endl;
        return;
    }
    cout << n << " ";                                                         // print current n value     
    recursive_print_count(n + 1, base);                                            // increment n by 1
}

//-----------------------------------------------------------------------------------------------------
// RECURSIVE SUM ARRAY METHOD
//-----------------------------------------------------------------------------------------------------

// Same pattern as above, but now this one uses the stack like the string reverse method,
// to unwind and sum the values that have been stored on the stack.
// the values being the last item in the array.
// the last item in the array is then altered each recursion call decrementing the array size by 1


int recursive_sum_array(int* arr, int size){            // pass in pointer to array and the array size
    if (size == 0){                                                                       // base case
        return 0;                                                          // no values left, return 0
    }
    return arr[size-1] + recursive_sum_array(arr, size - 1); // get value at back/decrement array by 1
}
////---------------------------------------------------------------------------------------------------



