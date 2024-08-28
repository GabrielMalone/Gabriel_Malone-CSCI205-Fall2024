/**
 * Gabriel Malone / CSCI205 / FALL 2024 / Lab I - Fractions Lab
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "Fraction.h"
using namespace std;

/**
 * Method to read fractions from a text file and create Fraction objects from the data
 * @return
 */
vector<Fraction> insertFracToVec()
{
	// vector of fractions
	vector<Fraction> frVect;
	// filestream
	fstream frFile;
	// string for each fraction in file
	string frString;
	// open file write using file object
	// check if file is open
	frFile.open("fractions.txt", ios::in);
	// read data
	if (frFile.is_open())
	{
		while (getline(frFile, frString))
		{
			// find the comma
			int splitIndx = frString.find(',');
			// get the numerator
			string numStr = frString.substr(0, splitIndx);
			// get the denominator
			string denStr = frString.substr(splitIndx + 1);
			// convert string to int
			int num = stoi(numStr);
			int den = stoi(denStr);
			// create fraction object
			Fraction f(num, den);
			// place the fraction in vector
			frVect.emplace_back(f);
		}
		frFile.close();
	}
	return frVect;
}

/**
 * Method to find the largest Fraction
 * @param frVect
 * @return
 */
Fraction find_largestFr(vector<Fraction> &frVect)
{
	// initialize largest place holder
	Fraction largest;
	// iterate through the vector
	for (const auto& f : frVect)
	{
		if (f > largest)
		{
			largest = f;
		}
	}
	return largest;
}

/**
 * Print five fractions per line form the Fraction vector
 * @param frVect
 */
void print(const vector<Fraction> &frVect)
{
	// initialize counter
	int index = 0;
	// iterate through vector
	for (int i = 0; i < frVect.size(); i++)
	{
		// print out a fraction, no new line data
		cout << "( " << frVect[i] << " )" << "  ";
		// increment counter
		index++;
		if (index == 5)
		{
			// at 5, endl and reset counter
			cout << endl;
			index = 0;
		}
	}
}

int main()
{
	// create vector
	vector<Fraction> frVect = insertFracToVec();

	// FIND LARGEST
	Fraction largestFr = find_largestFr(frVect);
	cout << endl
		 << "The largest positive fraction in the file is: " << largestFr << endl
		 << endl;

	// PRINT 5 IN A ROW
	print(frVect);
	cout << endl;

	// OVERLOADED ADDITION (with double forms for confirmation)
	Fraction f1 = frVect[0]; // pick some fractions from the vector
	Fraction f2 = frVect[1];
	double decF1 = ((double)f1.getNumerator() / (double)f1.getDenominator());
	double decF2 = ((double)f2.getNumerator() / (double)f2.getDenominator());
	cout << "OVERLOADED ADDITION (with double forms for confirmation)" << endl;
	cout << f1 << " (" << decF1 << ")" << " + " << f2 << " (" << decF2 << ")"
																		  " = "
		 << f1 + f2 << " (" << decF1 + decF2 << ")" << endl
		 << endl;

	// OVERLOADED SUBTRACTION
	Fraction f3 = frVect[2];
	Fraction f4 = frVect[3];
	double decF3 = ((double)f3.getNumerator() / (double)f3.getDenominator());
	double decF4 = ((double)f4.getNumerator() / (double)f4.getDenominator());
	cout << "OVERLOADED SUBTRACTION (with double forms for confirmation)" << endl;
	cout << f3 << " (" << decF3 << ")" << " - " << f4 << " (" << decF4 << ")"
																		  " = "
		 << f3 - f4 << " (" << decF3 - decF4 << ")" << endl
		 << endl;

	// OVERLOADED MULTIPLICATION
	Fraction f5 = frVect[4];
	Fraction f6 = frVect[5];
	double decF5 = ((double)f5.getNumerator() / (double)f5.getDenominator());
	double decF6 = ((double)f6.getNumerator() / (double)f6.getDenominator());
	cout << "OVERLOADED MULTIPLICATION (with double forms for confirmation)" << endl;
	cout << f5 << " (" << decF5 << ")" << " * " << f6 << " (" << decF6 << ")"
																		  " = "
		 << f5 * f6 << " (" << decF5 * decF6 << ")" << endl
		 << endl;

	// OVERLOADED DIVISION
	Fraction f7 = frVect[6];
	Fraction f8 = frVect[7];
	double decF7 = ((double)f7.getNumerator() / (double)f7.getDenominator());
	double decF8 = ((double)f8.getNumerator() / (double)f8.getDenominator());
	cout << "OVERLOADED DIVISION (with double forms for confirmation)" << endl;
	cout << f7 << " (" << decF7 << ")" << " / " << f8 << " (" << decF8 << ")"
																		  " = "
		 << f7 / f8 << " (" << decF7 / decF8 << ")" << endl
		 << endl;

	return 0;
}
