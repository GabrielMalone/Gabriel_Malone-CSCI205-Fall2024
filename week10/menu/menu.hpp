#ifndef MENU
#define MENU

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

//-----------------------------------------------------------------------------------
                                             // vector of the sorting algorithm names
vector<string> fileNames =
    {
        "QUICK SORT LAZY",
        "QUICK SORT MEDIAN",
        "QUICK SORT INSERTION",
        "QUICK SORT TUKEY'",
        "QUICK SORT DUAL PIVOT"
    };
//-----------------------------------------------------------------------------------
                                    // vector of the sorting vectory set up options
vector<string> arrayTypes =
    {
        "SORTED - ASCENDING",
        "SORTED - DESCENDING",
        "PARTIALLY SORTED",
        "RANDOM",
    };
//-----------------------------------------------------------------------------------
                                    // vector of the sorting vectory set up options
vector<string> experiment_type =
    {
        "GRAPHICAL SORTING DEMO",
        "GRAPH DATA",
    };


void printMenu(int& algo_selection, int& array_type_selection, int& experiment_selection ){

    int minWidth = 58;
    
    size_t i = 1;
    // create menu seleciton box
    //-------------------------------------------------------------------------------

    //-------------------------------------------------------------------------------
    cout << "+--------------------------------------------------------------+" << endl;
    cout << "                     ARRAY SET UP OPTIONS                       " << endl;
    cout << "+--------------------------------------------------------------+" << endl;
    i = 1;
	for (string fileName : arrayTypes)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
    cout << "+--------------------------------------------------------------+"<< endl;
	cout << "  SELECT ARRAY TYPE: "; cin >> array_type_selection;

    //-------------------------------------------------------------------------------
    cout << "+--------------------------------------------------------------+" << endl;
    cout << "                    ARRAY SET UP OPTIONS                        " << endl;
    cout << "+--------------------------------------------------------------+" << endl;
    i = 1;
	for (string fileName : experiment_type)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
    cout << "+--------------------------------------------------------------+" << endl;
	cout << "  SELECT  TYPE: "; cin >> experiment_selection;

    //---------------------------------------------------------------------------
    i = 1;
    cout << "+--------------------------------------------------------------+" << endl;
    cout << "                 ITERATIVE SORTING ALGORITHMS                   " << endl;
    cout << "+--------------------------------------------------------------+" << endl;
	for (string fileName : fileNames)
	{
		cout << "| " << i << ") " << setw(minWidth) << left << fileName << "|" << "\n";
		i ++;
	}
    cout << "+--------------------------------------------------------------+" << endl;
}

#endif