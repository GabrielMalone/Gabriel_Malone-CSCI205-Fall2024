#ifndef CARD_H
#define CARD_H
#include <iostream>

using namespace std;

class Card{
	private:
		char suit;					// 'H' = hearts, 'D' = diamonds, 'S' = spades, 'C' = clubs
		char value;					// 'A' = ace, '2' = 2, '3' = 3, ..., 'J' = jack, 'Q' = queen, 'K' = king
		bool faceUp;				// true = face up, false = face down
	public:
		Card(char s, char v);		// constructor
		Card(const Card& toCopy);	// copy constructor
		Card();						// default constructor

		char getSuit();				// accessor
		char getValue();			// accessor
		bool isFaceUp();			// accessor
		void turnFaceUp();			// mutator
		void turnFaceDown();		// mutator
		bool operator ==(const Card& otherCard);	// overloaded == operator

		friend ostream& operator <<(ostream& stream, const Card& Card); // overloaded << operator
};

#endif
