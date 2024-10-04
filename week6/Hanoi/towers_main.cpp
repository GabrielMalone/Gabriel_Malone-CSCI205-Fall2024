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
void towers_of_hanoi(int, List<Disc>&, List<Disc>&, List<Disc>&);// runeton's recursive logic for hanoi

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
    string towersize;
    cout << "Welcome to the Towers of Hanoi\nPlease enter size of tower: ";
    cin >> towersize;
    tower_depth = stoi(towersize);
    initializeGame(stoi(towersize) * 2);
    printTowers();
    cout << "Enter speed (0-100)";     // 0 fastest, 100 slowest, can enter any number you want, though
    cin >> speed;
    //-------------------------------------------------------------------------------------------------
    // run the algo and GUI
    //-------------------------------------------------------------------------------------------------
    towers_of_hanoi(tower_A.length(), tower_A, tower_C, tower_B);
    return 0;
}
//-----------------------------------------------------------------------------------------------------
// logic adapted from runestone, just plugged in my towers, GUI, and print statements
//-----------------------------------------------------------------------------------------------------
void moveDisk(List<Disc>& fp, List<Disc>& tp){
    cout << CLEAR_SCREEN;    // Clear the screen
    cout << CURSOR_TOP_LEFT;
    cout << setw(136) << setfill('-') << "" << endl;
    cout <<"MOVE NUMBER: " 
         << counter 
         << " Moving disk "; fp.get_head_element().print_disc(); cout 
         << "from " << fp.getName() 
         << " to " << tp.getName() << endl;
    cout << setw(136) << setfill('-') << "" << setfill(' ')<< endl;
    Disc top = fp.remove(0);
    tp.insert(top);
    printTowers();

}
//-----------------------------------------------------------------------------------------------------
// logic adapted from runestone, just plugged in my towers, GUI, and print statements
//-----------------------------------------------------------------------------------------------------
void towers_of_hanoi(int height, List<Disc>& fromPole, List<Disc>& toPole, List<Disc>& withPole){
    if (height >= 1){
        counter ++ ;
        towers_of_hanoi(height-1, fromPole, withPole, toPole); //Recursive call
        moveDisk(fromPole, toPole);
        towers_of_hanoi(height-1, withPole, toPole, fromPole); //Recursive call
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

/**
 * graphically display the current tower in terminal
 */
void printTowers(){
    int spacing = 45;                                             // for blank spaces in graphical output
    Node<Disc>* a = tower_A.get_head();// get the head of each tower so you can iterate through the discs
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
        if (start_print_heightA  - height == 0){    // once these trigger, that tower can start printing
            A_can_print = true;
        }
        if (start_print_heightB  - height == 0){
            B_can_print = true;
        }
        if (start_print_heightC -  height == 0 ){
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
            cout << "["<<setw(spacing)<<"] ";                          // if cant print, place a blank
        }
        cout << endl;
        height -- ;                                    // decrement height at which printing can occur
    }
    this_thread::sleep_for(chrono::milliseconds(speed));                   // speed of display of algo
}