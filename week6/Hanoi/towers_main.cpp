// Gabriel Malone 

#include <iostream>
#include <iomanip>
#include "Disc.hpp"
#include "../backend/List.hpp"

using namespace std;

List<Disc>tower_A;
List<Disc>tower_B;
List<Disc>tower_C;

int counter = 0;

void initializeGame(size_t);
void printTowers();
void moveDisk(List<Disc>&, List<Disc>&);
void towers_of_hanoi(int, List<Disc>&, List<Disc>&, List<Disc>&);

int main(){
    tower_A.setName("Tower A");
    tower_B.setName("Tower B");
    tower_C.setName("Tower C");
    string towersize;
    cout << "Welcome to the Towers of Hanoi\nPlease enter size of tower: ";
    cin >> towersize;
    initializeGame(stoi(towersize) * 2);
    printTowers();
    char whatever;
    cout << "Press 's' then Enter to solve ";
    cin >> whatever;
    towers_of_hanoi(tower_A.length(), tower_A, tower_C, tower_B);
    return 0;
}

void moveDisk(List<Disc>& fp, List<Disc>& tp){
    cout <<"\nMOVE NUMBER: " << counter << " Moving disk "; fp.get_head_element().print_disc(); cout << "from " << fp.getName() << " to " << tp.getName() << "\n" << endl;
    Disc top = fp.remove(0);
    tp.insert(top);
    printTowers();
}

void towers_of_hanoi(int height, List<Disc>& fromPole, List<Disc>& toPole, List<Disc>& withPole){
    if (height >= 1){
        counter ++ ;
        towers_of_hanoi(height-1, fromPole, withPole, toPole); //Recursive call
        moveDisk(fromPole, toPole);
        towers_of_hanoi(height-1, withPole, toPole, fromPole); //Recursive call
    }
}   


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
    // get heighest stack to iterate from
    Node<Disc>* tallest;                            // this will guide when each tower can start printing their discs
    Node<Disc>* a = tower_A.get_head();             // get the head of each tower so you can iterate through the discs
    Node<Disc>* b = tower_B.get_head();
    Node<Disc>* c = tower_C.get_head();
    int height = 0;                                 // this will serve as a way to track what height of the tower the print function is at
    if (tower_A.length() > height){                 // now let's find which tower is the tallest
        height = tower_A.length();
        tallest = tower_A.get_head(); 
      
    }
    if (tower_B.length() > height){
        height = tower_B.length();
        tallest = tower_B.get_head();
      
    }
    if (tower_C.length() > height){
        height = tower_C.length();
        tallest = tower_C.get_head();
   
    }                                              // start printing from the tallest tower's height
    int start_print_heightA = tower_A.length();    // these will be used to see when each tower can start printing their discs
    int start_print_heightB = tower_B.length();
    int start_print_heightC = tower_C.length();
    bool A_can_print = false;                      // bool switches for each tower's go ahead to print
    bool B_can_print = false;
    bool C_can_print = false;                   
    cout << "                   tower a                                      tower b                                        tower c\n" << endl;
    while (tallest != NULL){                        // iterate for duration of tallest tower
        if (start_print_heightA  - height == 0){    // once these trigger, that tower can start printing
            A_can_print = true;
        }
        if (start_print_heightB  - height == 0){
            B_can_print = true;
        }
        if (start_print_heightC -  height == 0 ){
            C_can_print = true;
        }
        if (a != NULL && A_can_print){           
            a->data.print_disc();
            a = a->next;
         
        } else {
            cout << "[                                           ] ";    // if null or cant print, place a blank
        }
        if (b != NULL && B_can_print){
            b->data.print_disc();
            b = b->next;
         
        } else {
            cout << "[                                           ] ";
        }
        if (c != NULL && C_can_print){
            c->data.print_disc();
            c = c->next;
        } else {
            cout << "[                                           ] ";
        }
        tallest = tallest->next;
        cout << endl;
        height -- ;
    }
}