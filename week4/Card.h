#ifndef CARD_H
#define CARD_H
#include <iostream>

using namespace std;

class Card{

    private:
        char suit;      // 'H', 'D', 'S', 'C'
        char value;     // '2' - '9', 'T', 'J', 'Q', 'K', 'A'
        bool faceUp;    // true if card is face up, false if card is face down

    public:
        Card(char s, char v);
        Card(const Card& toCopy);
        Card();

        char getSuit();     
        char getValue();
        bool isFaceUp();
        void turnFaceUp();
        void turnFaceDown();
        bool operator ==(const Card& otherCard);    // compare suit and value

        friend ostream& operator <<(ostream& stream, const Card& Card); // print card to stream
};

#endif
