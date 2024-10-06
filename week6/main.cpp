//-----------------------------------------------------------------------------------------------------
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
int len(int);
int dog_ears(int);
string strip(string, char);
bool nested(string);
//-----------------------------------------------------------------------------------------------------
//  MAIN
//-----------------------------------------------------------------------------------------------------
int main(){
    //-------------------------------------------------------------------------------------------------
    //  COMPARE ITERATIVE VS RECURSIVE FOR EUCLID'S GCD with a single run to confirm both work
    //-------------------------------------------------------------------------------------------------
    int a = 109872;
    int b = 102;
    //-------------------------------------------------------------------------------------------------
    //  ITERATIVE EUCLIDs ALGO
    //-------------------------------------------------------------------------------------------------
    cout << "------------------------------------------------------------------------------------------" << endl;
    algo_count_itr = 0;                                                                // reset counter
    cout << "Via the iterative method, the GCD of "     
         << a 
         << " and " 
         << b 
         << " is " 
         << EUC_GCD_ITR(a, b)                                                               // run algo
         << ". This algorithm ran " 
         << algo_count_itr                                                      // algo time complexity
         << " time(s)." 
         << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    //  RECURSIVE EUCLIDs ALGO
    //-------------------------------------------------------------------------------------------------
    algo_count_rec = 0;                                                                // reset counter 
    cout << "Via the recursive method, the GCD of "
         << a 
         << " and " 
         << b 
         << " is " 
         << EUC_GCD_REC(a, b)                                                               // run alog
         << ". This algorithm ran " 
         << algo_count_rec                                                      // algo time complexity
         << " time(s)." 
         << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    //  RUN AND COMAPRE A VRIETY OF GCD TESTS / AVERAGE AND COMPARE NUMBER OF OPERATIONS
    //-------------------------------------------------------------------------------------------------
    algo_count_itr = 0;                                                              // restet counters
    algo_count_rec = 0;
    int c = 9999;                                                    // starting value a for GCD algos
    int index = 0;

    List<int> rec_res;                                                     // hold results for rec algo
    List<int> itr_res;                                                     // hold results for itr algo    
    random_device rd;                              // random number generator for random val assignment
    mt19937 gen(rd());
                                            
    uniform_int_distribution<> dist(1,  100);               // range from 0 to 100 for the rnadom value                                            
    cout << "calculating efficiency of both algorithms over 9999 iterations... " << endl;
    for (int i = c ; i > 0; i  -- ){
        int random_int = dist(gen);  
        EUC_GCD_ITR(c,random_int);
        EUC_GCD_REC(c,random_int);                     // run the algos - dont care about actual result
        itr_res.insert(algo_count_itr, index);                         // place result of run into list
        rec_res.insert(algo_count_rec, index);                         // place result of run into list
        //cout << i << endl;                                          // see if frozen or still running
        index ++ ;
        algo_count_itr = 0;                                                           // reset counters
        algo_count_rec = 0;
    }
    //-------------------------------------------------------------------------------------------------
    //  FIND THE AVERAGE NUMBER OF OPERATIONS FOR EACH ALGO
    //-------------------------------------------------------------------------------------------------
    //-------------------------------------------------------------------------------------------------
    //  iterative algo average num of operations

    int sum_a = 0;
    Node<int>* n = itr_res.get_head();
    while (n != NULL){
        sum_a += n->data;
        n = n->next;
    }
    cout << "avg num operations for the iterative algo was: "
        << "Σ operations per run: "
        << sum_a
        << " / "
        << itr_res.length()
        << " = "
        << sum_a / itr_res.length() 
        << endl;

    //-------------------------------------------------------------------------------------------------
    //  recursive algo average num of operations

    int sum_b = 0;                                                   // iterate through list of reuslts
    Node<int>* m = rec_res.get_head();
    while (m != NULL){
        sum_b += m->data;
        m = m->next;
    }
    cout << "avg num operations for the recursive algo was: "
        << "Σ operations per run: "
        << sum_b
        << " / "
        << rec_res.length()
        << " = "
        << sum_b / rec_res.length() 
        << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // REVERSE STRING ITERATE METHOD " << endl;
    //-------------------------------------------------------------------------------------------------
    algo_count_itr = 0;                                                               // reset counters 
    algo_count_rec = 0;
    string str_to_reverse = "Gabriel123!";
    cout << "Reverse string '"
         << str_to_reverse
         << "' via iterating and Stack: "
         << reverse_string_itr(str_to_reverse)
         << ". This algo ran " 
         << algo_count_itr                                                     // algo time complexity
         << " times." 
         << endl;

    //-------------------------------------------------------------------------------------------------
    // REVERSE STRING RECURSIVE METHOD
    //-------------------------------------------------------------------------------------------------
    cout << "Reverse string '"
         << str_to_reverse
         << "' via recursion: "
         << reverse_string_rec(str_to_reverse)
         << ". This algo ran " 
         << algo_count_rec                                                      // algo time complexity
         << " times." 
         << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE COUNT METHOD
    //-------------------------------------------------------------------------------------------------   
        algo_count_rec = 0;                                                           // reset counters
        cout << "Recursively count from 1 to 22: ";
        recursive_print_count(1,22);                                                       
        cout << "This algorithm ran " 
             << algo_count_rec                                                  // algo time complexity
             << " times." 
             << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE SUM ARRAY METHOD
    //------------------------------------------------------------------------------------------------- 
        algo_count_rec = 0;                                                           // reset counters
        int arr[] = {5, 4, 3, 2, 1};
        cout 
         << "The sum of the array (via recursion) of {5, 4, 3, 2, 1} is "
         << recursive_sum_array(arr, 5)
         << ". This algo ran " 
         << algo_count_rec                                                      // algo time complexity
         << " times." 
         << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE LENGTH METHOD
    //-------------------------------------------------------------------------------------------------
        algo_count_rec = 0;                                                           // reset counters 
        cout << "The length of the digit 1234567890 is: "
             << len(1234567890) 
             << " This algo ran " 
             << algo_count_rec
             << " times."
             << endl;
        
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE DOG EARS COUNTER
    //------------------------------------------------------------------------------------------------- 
        algo_count_rec = 0;                                                           // reset counters 
        cout << "Count the number of ears for a line of 10 dogs: "      
             << dog_ears(10)
             << ". This algo ran " 
             << algo_count_rec
             << " times."
             << endl; 
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE STRING STRIPPER
    //------------------------------------------------------------------------------------------------- 
        algo_count_rec = 0;                                                           // reset counters
        cout << "strip the character '-' from the string '123-45-6789': "
             << strip("123-45-6789", '-')
             << ". This algo ran " 
             << algo_count_rec
             << " times." 
             << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE NESTED PARENTHESES CHECKER
    //------------------------------------------------------------------------------------------------- 
        algo_count_rec = 0;                                                           // reset counters
        cout << "Test for matching parentheses with '((()))'";
            if (nested("((()))")){
                cout << " = true";
            } else {
                cout << " = false";
            }
            cout 
             << ". This algo ran " 
             << algo_count_rec
             << " times." 
            << endl;
        algo_count_rec = 0;  
        cout << "Test for matching parentheses with '((())'";
            if (nested("((())")){
                cout << " = true";
            } else {
                cout << " = false";
            }
            cout 
             << ". This algo ran " 
             << algo_count_rec
             << " times." 
             << endl;
        algo_count_rec = 0;  
        cout << "Test for matching parentheses with '(((]))'";
            if (nested("(((]))")){
                cout << " = true";
            } else {
                cout << " = false";
            }
            cout 
             << ". This algo ran " 
             << algo_count_rec
             << " times." 
             << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE LIST PRINT METHOD
    //------------------------------------------------------------------------------------------------- 
    // the recursive print function requires calling print on the head node recursively until 
    // the head node reaches the tail node. The list class needed to be updated to handle the head 
    // constantly changing by this function call by implementing another variable (Node<T>* og_head)
    // that would update itself whenever the head is updated in any of the List class' functions. 
    
    List<int> newList;                                                             // create a new List
    for (size_t i = 0 ; i < 17 ; i ++){                                     // fill it with some values
        newList.insert(i);
    }

    cout << "Just created a linked list of 17 INTS. current head of list: "
         << newList.get_head_element()                          // check head element prior to printing
         << endl; 
    cout << "now printing recursively, updating head each recursive call...."  << endl;                                            
    newList.print();                                                          // check that print works
    cout << "confirming that head properly reset at end of print: ";
    cout << newList.get_head_element() << endl;           // confirm that head has been reset correctly
    cout << "------------------------------------------------------------------------------------------" << endl;
    //-------------------------------------------------------------------------------------------------
    // RECURSIVE REVERSE LIST METHOD
    //------------------------------------------------------------------------------------------------- 
    // For this method I took inspiration from the logic I used in the array list reversal --
    // using temp data from the front and back of the list for each iteration and swapping the data at
    // those positions, then moving the front of the list up by one and the back of the list down
    // by one. With recursion the base case is when the head and the tail 'meet' 
    // (are equal to eachother). I needed use global variables for original head and tail 
    // data since otherwise the original data would have been lost with the recursive functions 
    // needing to update head and tail each call. I made sure the other methods in the class updated 
    // these global variables where needed. 
    cout << "recursively reversing the list: " << endl;
    newList.reverse();
    newList.print();
    cout << "new head: " << newList.get_head_element() << endl;
    cout << "new tail: " << newList.get_tail()->data << endl;
    cout << "------------------------------------------------------------------------------------------" << endl;
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
}                                                                        // and reducing a by modulus b
                                                        // and passing 'b' as the remainder of 'a' / 'b'

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
        algo_count_itr ++;
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

// TIME COMPLEIXTY/ SPACIAL COMPLEXITY is O(n) since the function will recurse character by character

// MEMORY REQUIREMENTS for this function are : 
// 1) the return address : 8 bytes
// 2) string variable will vary depend on its size: 1byte per character in the string. 
// 3) the same will go for the 'char' back character declared in the function. 
// therefore the final mem total for this function is at least 10 bytes with no limit on its maximum,
// per placement on the stack.

string reverse_string_rec(string str){                                  
    if (str.length() == 0){                                            // base case is string size = 0
        return str;                                                                   // str = "" here
    }
    algo_count_rec ++;
    char back = str[str.length()-1];                                   // get back character of string
    return back + reverse_string_rec(str.substr(0, str.length()-1));   // build back char by back char
}
//-----------------------------------------------------------------------------------------------------
// RECURSIVE PRINT COUNT METHOD
//-----------------------------------------------------------------------------------------------------

// this method is similar to the above method, but instead of building up the stack, since nothing
// needs to unwound, you can simply print 'n' and its updates (n+1). the function will then break and 
// exit its scope when n equals the base case. 

// TIME COMPLEXITY / SPACIAL COMPLEXITY is O(n) since the function will recurse character by character

//  MEMORY REQUIREMENTS for this function are:
// 1) memory address for the function - 8 bytes
// 2) the two ints passed in as parameters (4 bytes each) - 8 bytes
// 3) no new variables declared within the function, thus
// the total memory for each placement of this function on the stack will be 16 bytes. 

void recursive_print_count(int n, int base){                             // pass in start and end value
    algo_count_rec ++ ;
    if (n == base){                                                               // if n = base , quit
        cout << n << endl;
        return;
    }
    cout << n << " ";                                                          // print current n value     
    recursive_print_count(n + 1, base);                                             // increment n by 1
}

//-----------------------------------------------------------------------------------------------------
// RECURSIVE SUM ARRAY METHOD
//-----------------------------------------------------------------------------------------------------

// Same pattern as above, but now this one uses the stack like the string reverse method,
// to unwind and sum the values that have been stored on the stack.
// the values being the last item in the array.
// the last item in the array is then altered each recursion call decrementing the array size by 1

// TIME COMPLEXITY for this recursive function is O(n) since the size is reduced by 1 each recursion.

// MEMORY REQUIREMENTS for this function are:
// 1) the address for the function: 8 bytes
// 2) the pointer to the array passed in as a parameter: 8 bytes
// 3) the int for the size of the array passed in as a parameter: 4 bytes
// no other variables set in the function itself, 
// thus total mem required per placement on stack: 12 bytes

int recursive_sum_array(int* arr, int size){            // pass in pointer to array and the array size
    algo_count_rec ++ ;
    if (size == 0){                                                                       // base case
        return 0;                                                          // no values left, return 0
    }
    return arr[size-1] + recursive_sum_array(arr, size - 1); // get value at back/decrement array by 1
}

//-----------------------------------------------------------------------------------------------------
// RECURSIVE LENGTH METHOD
//-----------------------------------------------------------------------------------------------------
// To find the length of a digit (that is in base 10), just perform recursive division by 10 until 
// that division results in 0. We don't actually care about the values that result from the division
// so we just return '1' to serve as a count for each time the recursion occurs. 
// Thus: 
// 1) base case = the number passed in equals 0
// 2) function is recursively called
// 3) 'n' the number passed in is reduced by n / 10 each recursive call.
// this method will run and place values on the stack for the length of the digit that is entered.

// TIME COMPLEXITY / SPACIAL COMPLEXITY I think linear O(n) even though using division, the division
// will happen for however long the digit entered is (base 10 numbers).

int len(int n){ 
    algo_count_rec ++;                                                                            
    if (n / 10 == 0){
        return 1;
    }
    return 1 + len(n/10);
}


//-----------------------------------------------------------------------------------------------------
// RECURSIVE DOG EARS COUNTER
//-----------------------------------------------------------------------------------------------------

// To find the number of dog ears of the dogs in line when dogs in an even position have 3 ears
// and dogs in an odd posiition have 2 ears, is another addition via stack returns algo. 
// This time we just need to check whether to return a 2 or a 3 to the stack via modulus division 
// (aka checking for even vs odd). The function satisfies the recursive requirements by:
// 1) base case  exists , function knows to exit its scop when num_dogs = 0
// 2) num_dogs reduces its value each recursive call
// 3) num_dogs called recursively until base case met. 
// call stack unwinds once function exits its scope and adds the numbers placed on the stack.

// TIME / SPACIAL COMPLEXITY is O(n) linear, since the var is reduced by 1 for each recursion. 

// MEMORY REQUIREMENTS :
// 1) the int passed in as a variable will require 4 bytes,
// 2_ the 0, 2, and 3 are al ints declared in the function and will require 4 bytes (12 total).
// Thus 16 bytes + the memory address for the function, 8 bytes, is 24 bytes total per placement
// on the stack. 

int dog_ears(int num_dogs){
    algo_count_rec ++ ;
    if (num_dogs == 0){                                                                    // base case
        return 0;                                                 // no new values to add at this point
    }
    if (num_dogs % 2 != 0 ){                                           // if a dog in odd line position
        return 2 + dog_ears(num_dogs - 1);                                        // add 2 to the stack
    }
    return 3 + dog_ears(num_dogs - 1);        // otherwise its a dog with 3 ears, so add 3 to the stack
}

//-----------------------------------------------------------------------------------------------------
// RECURSIVE STRING STRIP METHOD
//-----------------------------------------------------------------------------------------------------

// This is the same logic as the string reversal, but instead of taking the back index and returning
// that to the stack, we are taking the front index of the string and returning that to the stack.
// in addition, we are decreasing the size of the string from the front instead of from the back
// in order to continually shift that front index character. 

// TIME / SPACIAL REQUIREMENTS = O(n) since the string is reduced by one from both ends (2 total)
// reach recursive call. 

// MEMORY REQUIREMENTS 
// 1) string variable will be based on size of string passed in (1 byte per char)
// 2) 1 byte for the char passed in (to be stripped)
// 3) 1 byte for the "" blank string added to the return value
// 4) 8 bytes for the memory address
// for a total of at least 11 bytes per placement on the stack

string strip(string str, char c){   
    if (str.length() == 0){        // base case, return from scope of function when str length is zero
        algo_count_rec ++ ;
        return str;                                                                  // str will be ""
    }
    if (str[0] != c){  
        algo_count_rec ++ ;                       // check front of string against char to be stripped
        return str[0] + strip(str.substr(1, str.length()), c);  // if char to keep, return it to stack
    }
    algo_count_rec ++ ;
    return "" + strip(str.substr(1, str.length()), c);                 // otherwise return "" to stack
}

//-----------------------------------------------------------------------------------------------------
// RECURSIVE NESTED PARENTHESES PAIR CHECKER 
//-----------------------------------------------------------------------------------------------------
// This function returns whether the front and back chars of a string are matched parentheses pairs.
// Similar to the previous methods, but this time using mulitplication in the recursion. 
// if the front and back chars are a pair, a 1 is returned to the stack (bool true). 
// if they are not a pair, a 0 is returned to the stack.
// both are returned to the stack with the multiplication operator
// function is called recurisevly with the string incremented to next char from the front and
// the char decremented to previous char from the back. 
// when the stack unwinds, if ever there was a false in the stack, due to multiplying by zero, false
// will be returned as the final result. Otherwise all multiplication of 1 by itself will return true

// TIME / SPACIAL REQUIREMENTS - O(n) liner since the function recusrively iterates through a string

// MEMORY REQUIREMENTS :
// 1) string passed in as parameter will be at least 1 byte (1 byte per character)
// 2) two chars set at the top = 1 + 1, 2 bytes
// 3) '2' in condtional is, INT, 4 bytes
// 4) memory address of function = 8 bytes
// for a total of at least 14 bytes per placement on the stack

bool nested(string str){
    algo_count_rec ++ ;
    if (str.length() % 2 == 0){                               // can proceed if string length is even
        char front = str[0];                                                        // get front char
        char back = str[str.length()-1];                                             // get back char
        if (str.length() == 2){// base case, if last two chars, check to see if a pair of parentheses
            return (front == '(' && back == ')');              // return to stack true or false (1/0)
            
        }
        str = str.substr(1, str.length()-2);                         // adjust string from both sides
        return (front == '(' && back == ')') && nested(str); // return 1 or 0 to stack, linux threw a 
    }                                               // warning with '*' though, suggested && instead.
    return false;                                           // if uneven string to start with = false
}  // with the && , if front and back arent equal, nested(str) won't be called false returned overall
    // I don't know why I had to do minus 2 instead of minus 1, though, debugger showed was necessary
        // degubber showing no difference between setting end of str equal to lenth() vs length() - 1

////---------------------------------------------------------------------------------------------------



