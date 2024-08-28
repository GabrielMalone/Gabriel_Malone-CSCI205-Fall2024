/**
 * Gabriel Malone / CSCI205 / FALL 2024 / Lab I - Fractions Lab
 */

#include "Fraction.h"


/**
 * Euclid's algo to find GCD - from runestone
 * @param m
 * @param n
 * @return the GCD
 */
int GCD(int m, int n) {
	while (m % n != 0) {
		int oldm = m;
		int oldn = n;
		m = oldn;
		n = oldm % oldn;
	}
	return n;
}
/**
 * Fraction Constructor with no arguments
 * @param top
 * @param bottom
 */
Fraction::Fraction(){
	// default values
	this->num = 0;
	this->den = 1;
}

/**
 * Fraction Constructor with two arguments
 * @param top
 * @param bottom
 */
Fraction::Fraction(int top, int bottom){
	// handle negative denominator
	// change denominator to positive and numerator to its opposite sign
	if (bottom < 0)
	{
		bottom *= -1;
		top *= -1;
	}
	// absolute value to prevent negative sign switching
	int common = abs(GCD(top, bottom));
	this->num = top / common;
	this->den = bottom / common;
}

/**
 * Copy constructor
 * @param other
 */
Fraction::Fraction(const Fraction &other) {
	//std::cout << "Copy constructor called for " << other.num << "/" << other.den << std::endl;
	this->num = other.num;
	this->den = other.den;
}

/**
 * Destructor (although just using ints for this lab, so just stack memory allocated, not heap)
 */
Fraction::~Fraction() {
	// nothing for us to destruct here, but c++ will call these things automatically for us
	//std::cout << "Destructor called for " << num << "/" << den << std::endl;
}

/**
 * Fraction 'cout <<' override
 * @param stream
 * @param frac
 * @return stream
 */
std::ostream &operator << (std::ostream &stream, const Fraction &frac) {
	int mixedNumber;
	int newNum;
	// if evenly disivible mixed fraction
	if (frac.num % frac.den == 0)
	{
		stream << frac.num / frac.den;
	}
	// if not evenly divisible mixed fraction
	// need absolute value to account for someting like (-1/2) being considered a mixed fraction
	else if (abs(frac.num) > abs(frac.den))
	{
		mixedNumber = frac.num / frac.den;
		// if the mixed number is negative, remove the negative sign from the denominator in the fraction
		if (mixedNumber < 0 )
		{
			newNum = frac.num * -1;
		// if the mixed number is not negative, no changes to denominator sign
		}
		else
		{
			newNum = frac.num * 1;
		}
		// absolute value needed to prevent a negative mixedNumber from throwing off the conversion
		stream << mixedNumber << " " << newNum - abs(frac.den * mixedNumber) << "/" << frac.den;
	// regular fractiom outpout
	}
	else
	{
		stream << frac.num << "/" << frac.den;
	}
	return stream;
}

/**
 * Fraction '+' operator override
 * @param otherFrac
 * @return reduced sum of two fractions
 */
Fraction Fraction::operator + (Fraction &otherFrac) {
	int newNum = num * otherFrac.den + den * otherFrac.num;
	int newDen = den * otherFrac.den;
	return Fraction(newNum,newDen);
}

/**
 * Fraction '+=' operator override
 * @param otherFrac
 * @return reduced sum of this fraction plus another fraction
 */
Fraction Fraction::operator += (Fraction &otherFrac) {
	 this->num = num * otherFrac.den + den * otherFrac.num;
	 this->den = den * otherFrac.den;
	return Fraction(this->num,this->den);
}

/**
 * Fraction '-' operator override
 * @param otherFrac
 * @return reduced difference of two fractions
 */
Fraction Fraction::operator - (Fraction &otherFrac) {
	int newNum = this->num * otherFrac.den - this->den * otherFrac.num;
	int newDen = this->den * otherFrac.den;
	return Fraction(newNum,newDen);
}

/**
 * Fraction '*' operator override
 * @param otherFrac
 * @return reduced product of two fractions
 */
Fraction Fraction::operator * (Fraction &otherFrac) {
	int newNum = this->num * otherFrac.num;
	int newDen = this->den * otherFrac.den;
	return Fraction(newNum,newDen);
}

/**
 * Fraction '/' operator override
 * @param otherFrac
 * @return reduced quotient of two fractions
 */
Fraction Fraction::operator / (Fraction &otherFrac) {
	int newNum = this->num * otherFrac.den;
	int newDen = this->den * otherFrac.num;
	return Fraction(newNum,newDen);
}

/**
 * Fraction '>' operator override
 * @param otherFrac
 * @return bool whether left fraction greater than right fraction
 */
bool Fraction::operator > (Fraction &otherFrac) const {
	double thisFraction = (double)this->num/(double)this->den; /** Need to convert ints to doubles */
	double otherFraction = (double)otherFrac.num/(double)otherFrac.den;
	return thisFraction > otherFraction;
}

/**
 * Fraction '<' operator override
 * @param otherFrac
 * @return bool whether left fraction less than right fraction
 */
bool Fraction::operator < (Fraction &otherFrac) {
	double thisFraction = (double)this->num/(double)this->den; // Need to convert ints to doubles
	double otherFraction = (double)otherFrac.num/(double)otherFrac.den;
	return thisFraction < otherFraction;
}

/**
 * Fraction '<=' operator override
 * @param otherFrac
 * @return bool whether left fraction less than or equal to right fraction
 */
bool Fraction::operator <= (Fraction &otherFrac) {
	double thisFraction = (double)this->num/(double)this->den;
	double otherFraction = (double)otherFrac.num/(double)otherFrac.den;
	return thisFraction <= otherFraction;
}

/**
 * Fraction '>=' operator override
 * @param otherFrac
 * @return bool whether left fraction greater than or equal to right fraction
 */
bool Fraction::operator >= (Fraction &otherFrac) {
	double thisFraction = (double)this->num/(double)this->den;
	double otherFraction = (double)otherFrac.num/(double)otherFrac.den;
	return thisFraction >= otherFraction;
}

/**
 * Fraction '!=' operator override
 * @param otherFrac
 * @return bool whether left fraction does not equal the right fraction
 */
bool Fraction::operator != (Fraction &otherFrac) {
	double thisFraction = (double)this->num/(double)this->den;
	double otherFraction = (double)otherFrac.num/(double)otherFrac.den;
	return thisFraction != otherFraction;
}

/**
 *  Fraction '==' operator override
 * @param otherFrac
 * @return
 */
bool Fraction::operator == (Fraction &otherFrac) {
	int firstnum = this->num * otherFrac.den;
	int secondnum = otherFrac.num * den;
	return firstnum == secondnum;
}


