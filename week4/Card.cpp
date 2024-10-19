#include "Card.h"

using namespace std;

//Constructor that creates a Card object given its suit and value
Card::Card(char s, char v){
    suit    = s;
    value   = v;
    faceUp  = false;
}

//Copy constructor that creates a Card object with the same properties as toCopy
Card::Card(const Card& toCopy){
    suit    = toCopy.suit;
    value   = toCopy.value;
    faceUp  = toCopy.faceUp;
}

//Default constructor that acts as a "blank card" (for clearing the game board)
Card::Card(){
    suit    = '-';
    value   = '-';
}

//Returns the suit of the Card (C, S, D, or H)
char Card::getSuit(){
    return suit;
}

//Returns the value of the Card (2-10, J, Q, K, or A)
char Card::getValue(){
    return value;
}

//Returns whether or not the Card is turned face up
bool Card::isFaceUp(){
    return faceUp;
}

//Turns a card face up
void Card::turnFaceUp(){
    faceUp = true;
}

//Turns a card face down
void Card::turnFaceDown(){
    faceUp = false;
}

//Returns true if this Card has the same suit and value as otherCard
bool Card::operator ==(const Card& otherCard){
    return suit == otherCard.suit && value == otherCard.value;
}

//Displays the card as its value and suit (e.g. 2 of Clubs is displayed as 2C)
ostream& operator <<(ostream& stream, const Card& card){
    stream << card.value << card.suit << "";
    return stream;
}

