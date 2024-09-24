// Gabriel Malone // CSCI205 // WEEK 5
#ifndef H_FILE_OPENER
#define H_FILE_OPENER

#include <fstream>
#include <string>
#include "../List/LinkedList.hpp"
using namespace std;

struct FileOpener{

	/**
	 * Load dorms / students from a text file into a linked list
	 */
	static void dormLoader(string fileName, List<string>& stringList) {		// pass List reference
		fstream frF;														// new filestream obj	
		string dormStr;														// string for each task in file
		string name;
		frF.open(fileName, ios::in);										// open file write using file object					
		if (frF.is_open()){													// check if file is open
			while(getline(frF, dormStr)){									// get the string from each line
				name = dormStr.substr(0, dormStr.length() - 1);				
				stringList.insert(name,0);  								// remove the /r return escape
			}
		}
		frF.close();														// close
	}
};

#endif




