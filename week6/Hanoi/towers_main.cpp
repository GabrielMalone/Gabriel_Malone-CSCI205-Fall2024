// Gabriel Malone // CSCI205 // WEEK 6
//-----------------------------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>
#include "Disc.hpp"
#include "../backend/List.hpp"
#include <chrono>
#include <thread>

using namespace std;
//-----------------------------------------------------------------------------------------------------
// List of Discs to serve as towers
//-----------------------------------------------------------------------------------------------------
List<Disc>tower_A;
List<Disc>tower_B;
List<Disc>tower_C;
//-----------------------------------------------------------------------------------------------------
// vars for initializing the game via user input
//-----------------------------------------------------------------------------------------------------
size_t tower_depth;
int speed;
int counter = 0;
string CLEAR_SCREEN  = "\033[2J";                                                  
string CURSOR_TOP_LEFT = "\033[H";
//-----------------------------------------------------------------------------------------------------
// tower methods
//-----------------------------------------------------------------------------------------------------
void initializeGame(size_t);                 // this will fill tower A with the desired number of discs
void printTowers();                                      // this will print all three towers every turn
void moveDisk(List<Disc>&, List<Disc>&);                  // runestone logic for the recursive function
void towers_of_hanoi_logic(int, List<Disc>&, List<Disc>&, List<Disc>&);   // runetone's logic for hanoi
void towers_of_hanoi();                                             // parameterless method to run game

int main(){
    //-------------------------------------------------------------------------------------------------
    // Give the towers a name for GUI output
     //------------------------------------------------------------------------------------------------
    tower_A.setName("Tower A");
    tower_B.setName("Tower B");
    tower_C.setName("Tower C");
    //-------------------------------------------------------------------------------------------------
    // collect input from user
    //-------------------------------------------------------------------------------------------------
    cout << "Welcome to the Towers of Hanoi\nPlease enter size of tower: ";
    cin >> tower_depth;
    initializeGame(tower_depth * 2);
    printTowers();
    cout << "Enter speed (0-100)";     // 0 fastest, 100 slowest, can enter any number you want, though
    cin >> speed;
    //-------------------------------------------------------------------------------------------------
    // run the algo and GUI
    //-------------------------------------------------------------------------------------------------
    towers_of_hanoi();
    return 0;
}
//-----------------------------------------------------------------------------------------------------
// logic adapted from runestone, just plugged in my towers, GUI, and print statements
//-----------------------------------------------------------------------------------------------------
void moveDisk(List<Disc>& fp, List<Disc>& tp){
    //-----------------------------------------------------------------
    counter ++ ;                                        // count moves 
    //-----------------------------------------------------------------
    // PRINT HEADER
    //-----------------------------------------------------------------
    cout << CLEAR_SCREEN;                           // Clear the screen
    cout << CURSOR_TOP_LEFT;            // keep terminal from scrolling
    cout << setw(136) << setfill('-') << "" << endl; 
    cout <<"MOVE NUMBER: " 
         << counter 
         << " Moving disk "; fp.get_head_element().print_disc(); cout 
         << "from " << fp.getName() 
         << " to " << tp.getName() << endl;
    cout << setw(136) << setfill('-') << "" << setfill(' ')<< endl;
    //-----------------------------------------------------------------
    Disc top = fp.remove(0);            // pop the top of the from pole
    tp.insert(top);                          // place it on the to pole
    //-----------------------------------------------------------------
    printTowers();                                  // show the results
}
//-----------------------------------------------------------------------------------------------------
// logic adapted from runestone, just plugged in my towers, graphics, and print statements
//-----------------------------------------------------------------------------------------------------
void towers_of_hanoi_logic(int height, List<Disc>& tower_A, List<Disc>& tower_C, List<Disc>& tower_B){
    //-----------------------------------------------------------------------------
    // base case is when height == 0
    //-----------------------------------------------------------------------------
    if (height >= 1){
        //-------------------------------------------------------------------------
        // first recursive call swaps towers B and C continuously until base case
        //-------------------------------------------------------------------------
        towers_of_hanoi_logic(height-1, tower_A, tower_B, tower_C); //Recursive call
        //-------------------------------------------------------------------------
        // move disk called each unwind of the stack, 
        // tower C will differ each unwind (and A will differ when second 
        // recursive function calls its own move disk (with A and C still swapping))
        //-------------------------------------------------------------------------
        moveDisk(tower_A, tower_C);
        //-------------------------------------------------------------------------
        // second recursive call placed on stack each time first recursive call is 
        // placed on stack. second recursive call will run during each unwind and 
        // will place its own recursive calls (acting as the first recursive call
        // above) for however large the 'height' variable is at that time. 
        //-------------------------------------------------------------------------
        towers_of_hanoi_logic(height-1, tower_B, tower_C, tower_A); //Recursive call
    }
}   
//-----------------------------------------------------------------------------------------------------
// Helper functions
//-----------------------------------------------------------------------------------------------------
/**
 * Method to start the game with tower A's discs 
 * placed to desired height,
 * starting with widest disc on the bottom, 
 * decrementing in size by one on the way up
 */
void initializeGame(size_t towerHeight){
    int index = 0;
    for (size_t i =  1 ; i < towerHeight ; i += 2){
        Disc d(i);
        tower_A.insert(d, index);
        index ++;
    }                                             
}

void towers_of_hanoi(){
    towers_of_hanoi_logic(tower_A.length(), tower_A, tower_C, tower_B);
}
//-----------------------------------------------------------------------------------------------------
// Graphic output
//-----------------------------------------------------------------------------------------------------
/**
 * graphically display the current tower in terminal
 */
void printTowers(){
    int spacing = 45;                                            // for blank spaces in graphical output
    Node<Disc>* a = tower_A.get_head();//get the head of each tower so you can iterate through the discs
    Node<Disc>* b = tower_B.get_head();
    Node<Disc>* c = tower_C.get_head();
    int height = 0;// this will serve as a way to track what height of the tower the print function is at
    if ((int)tower_A.length() > height){                     // now let's find which tower is the tallest
        height = tower_A.length();
    }
    if ((int)tower_B.length() > height){
        height = tower_B.length();
    }
    if ((int)tower_C.length() > height){
        height = tower_C.length();
    }                                                 
    int start_print_heightA = tower_A.length(); // these used to see when tower can start printing discs
    int start_print_heightB = tower_B.length();
    int start_print_heightC = tower_C.length();
    bool A_can_print = false;                        // bool switches for each tower's go ahead to print
    bool B_can_print = false;
    bool C_can_print = false;                    
    cout << setw(26) <<"tower a"
         << setw(45) <<"tower b"
         << setw(48) <<"tower c\n" 
         << endl;
    for (size_t i = 0 ; i < tower_depth ; i ++){         // iterate for duration of the GUI height I set
        if (start_print_heightA == height){         // once these trigger, that tower can start printing
            A_can_print = true;
        }
        if (start_print_heightB == height){
            B_can_print = true;
        }
        if (start_print_heightC == height){
            C_can_print = true;
        }
        if (a != NULL && A_can_print && tower_A.length() >= tower_depth - i){           
            a->data.print_disc();
            a = a->next;
        } else {
            cout << "["<<setw(spacing)<<"] ";                           // if cant print, place a blank
        }
        if (b != NULL && B_can_print && tower_B.length() >= tower_depth - i){
            b->data.print_disc();
            b = b->next;  
        } else {
            cout << "["<<setw(spacing)<<"] ";                           // if cant print, place a blank
        }
        if (c != NULL && C_can_print && tower_C.length() >= tower_depth - i){
            c->data.print_disc();
            c = c->next;
        } else {
            cout << "["<<setw(spacing)<<"] ";                           // if cant print, place a blank
        }
        cout << endl;
        height -- ;                                     // decrement height at which printing can occur
    }
    this_thread::sleep_for(chrono::milliseconds(speed));                    // speed of display of algo
}