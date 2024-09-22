// Gabriel Malone // CSCI205 // WEEK 5

#include <fstream>
#include <string>
#include "LinkedList/LinkedList.hpp"

using namespace std;

struct FileOpener{

	/**
	 * Load dorms / students from a text file into a linked list
	 */
	static List<string> dormLoader(string fileName){	
		List<string>output;													// linked list of strings to hold final split string outputs from file
		fstream frF;														// new filestream obj	
		string dormStr;														// string for each task in file
		frF.open(fileName, ios::in);										// open file write using file object					
		if (frF.is_open()){													// check if file is open
			while(getline(frF, dormStr)){
				output.insert(dormStr.substr(0, dormStr.length() - 1),0);  // remove the /r return escape
			}
		}
		return output;
	}
};



