#include <iostream>
#include "Disc.hpp"
#include "../backend/Stack.hpp"
#include "../backend/List.hpp"

using namespace std;

List<Disc>tower_A;
List<Disc>tower_B;
List<Disc>tower_C;

void towers_of_hanoi();
void initializeGame(size_t);
void printTower(List<Disc>&);



int main(){

    initializeGame(10);
    printTower(tower_A);
    return 0;
}

void towers_of_hanoi(){}

/**
 * Method to start the game with tower A's discs 
 * placed to desired height,
 * starting with widest disc on the bottom, 
 * decrementing in size by one on the way up
 */
void initializeGame(size_t towerHeight){
    for (size_t i =  0 ; i < towerHeight ; i ++){
        Disc d(i+1);
        tower_A.insert(d, i);
    }
}

/**
 * graphically display the current tower in terminal
 */
void printTower(List<Disc>& tower){
    Node<Disc>* n = tower.get_head();
    while (n != NULL){
        n->data.print_disc();
        n = n->next;
    }
}