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
vector<Fraction> insertFracToVec(){
	vector<Fraction>frVect;                                              // vector of fractions
	fstream frFile;                                                      // filestream
	string frString;                                                     // string for each fraction in file
	char split = ',';
	frFile.open("fractions.txt",ios::in);                       // open file write using file object
	if (frFile.is_open()) {                                              // check if file is open
		while (getline(frFile, frString)) {                        // read data
			int splitIndx  = frString.find(',');                      // find the comma
			string numStr = frString.substr(0, splitIndx);       // get the numerator
			string denStr = frString.substr(splitIndx+1);           // get the denominator
			int num = stoi(numStr);                                  // convert string to int
			int den = stoi(denStr);                                  // convert string to int
			Fraction f(num, den);                            // create fraction object
			//cout << f << endl;                                         // checking to see all works so far
			frVect.emplace_back(f);                                      // place the fraction in vector
		}
		frFile.close();                                                  // close the file object.
	}
	return frVect;
}

/**
 * Method to find the largest Fraction
 * @param frVect
 * @return
 */
Fraction find_largestFr(const vector<Fraction>& frVect){
	Fraction largest; // initialize largest place holder
	for (Fraction f : frVect) // iterate through the vector
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
void print(const vector<Fraction>& frVect){
	int index {0}; //initialize counter
	for (Fraction f : frVect) //iterate through vector
	{
		cout << "( " << f << " )" << "  "; //print out a fraction, no new line data
		index ++; // increment counter
		if (index == 5){
			cout << endl; // at 5, endl and reset counter
			index = 0;
		}
	}
}


int main()
	{
	vector<Fraction> frVect = insertFracToVec(); // create vector

	// FIND LARGEST
	Fraction largestFr = find_largestFr(frVect);
	cout << endl << "The largest positive fraction in the file is: " << largestFr << endl << endl;

	// PRINT 5 IN A ROW
	print(frVect);
	cout << endl;

	// OVERLOADED ADDITION (with double forms for confirmation)
	Fraction f1 = frVect[0]; // pick some fractions from the vector
	Fraction f2 = frVect[1];
	double decF1 = ((double)f1.getNumerator()/(double)f1.getDenominator());
	double decF2 = ((double)f2.getNumerator()/(double)f2.getDenominator());
	cout << "OVERLOADED ADDITION (with double forms for confirmation)" << endl;
	cout << f1 <<  " (" << decF1 << ")"<< " + " << f2 << " (" <<  decF2 << ")"" = " << f1 + f2 << " (" << decF1 + decF2 << ")" << endl << endl;

	// OVERLOADED SUBTRACTION
	Fraction f3 = frVect[2];
	Fraction f4 = frVect[3];
	double decF3 = ((double)f3.getNumerator()/(double)f3.getDenominator());
	double decF4 = ((double)f4.getNumerator()/(double)f4.getDenominator());
	cout << "OVERLOADED SUBTRACTION (with double forms for confirmation)" << endl;
	cout << f3 <<  " (" << decF3 << ")"<< " - " << f4 << " (" <<  decF4 << ")"" = " << f3 - f4 << " (" << decF3 - decF4 << ")" << endl << endl;

	// OVERLOADED MULTIPLICATION
	Fraction f5 = frVect[4];
	Fraction f6 = frVect[5];
	double decF5 = ((double)f5.getNumerator()/(double)f5.getDenominator());
	double decF6 = ((double)f6.getNumerator()/(double)f6.getDenominator());
	cout << "OVERLOADED MULTIPLICATION (with double forms for confirmation)" << endl;
	cout << f5 <<  " (" << decF5 << ")"<< " * " << f6 << " (" <<  decF6 << ")"" = " << f5 * f6 << " (" << decF5 * decF6 << ")" << endl << endl;

	// OVERLOADED DIVISION
	Fraction f7 = frVect[6];
	Fraction f8 = frVect[7];
	double decF7 = ((double)f7.getNumerator()/(double)f7.getDenominator());
	double decF8 = ((double)f8.getNumerator()/(double)f8.getDenominator());
	cout << "OVERLOADED DIVISION (with double forms for confirmation)" << endl;
	cout << f7 <<  " (" << decF7 << ")"<< " / " << f8 << " (" <<  decF8 << ")"" = " << f7 / f8 << " (" << decF7 / decF8 << ")" << endl << endl;

	return 0;
	}
