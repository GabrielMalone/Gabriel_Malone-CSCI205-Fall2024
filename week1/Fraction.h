/**
 * Gabriel Malone / CSCI205 / FALL 2024 / Lab I - Fractions Lab
 */

#ifndef Fraction_File
#define Fraction_File

#include <iostream>

/**
 * Class for creating and manipulating fractions
 */
class Fraction {
public:

	// CONSTRUCTORS ---------------------------------- //

	//constructor with defaults set to 0/1
	Fraction(int top=0, int bottom=1);

	// deleted copy constructor
//	Fraction(const Fraction&) = delete;
	// move constructor
//	Fraction(Fraction&&) noexcept {}

	// OPERATOR OVERRIDES ------------------------------------ //

	// cout '<<' operator override
	friend std::ostream &operator << (std::ostream &stream, const Fraction &frac);

	// pass all objects by reference

	// '+' operator override
	Fraction operator + (Fraction& otherFrac);
	// '+=' operator override
	Fraction operator += (Fraction& otherFrac);
	// '-' operator override
	Fraction operator - (Fraction& otherFrac);
	// '*' operator override
	Fraction operator * (Fraction& otherFrac);
	// '/' operator override
	Fraction operator / (Fraction& otherFrac);
	// '>' operator override
	bool operator > (Fraction& otherFrac);
	// '<' operator override
	bool operator < (Fraction& otherFrac);
	// '<=' operator override
	bool operator <= (Fraction& otherFrac);
	// '>=' operator override
	bool operator >= (Fraction& otherFrac);
	// '!=' operator override
	bool operator != (Fraction& otherFrac);
	// '==' operator override
	bool operator == (Fraction &otherFrac);
	// get and return methods

	// GETTERS -------------------------------------- //

	int getNumerator(){ return num; }
	int getDenominator(){ return den ;};

private:
	int num, den;
};

#endif