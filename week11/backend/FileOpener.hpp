// Gabriel Malone // CSCI205 // WEEK 5
#ifndef H_FILE_OPENER
#define H_FILE_OPENER

#include <fstream>
#include <string>
#include "List.hpp"
#include <algorithm>

using namespace std;



/**
 * Load dorms / students from a text file into a linked list
 */
string textLoader(const string& fileName) {								
	fstream frF;														// new filestream obj	
	string line;														// string for each task in file
	string file_text = "";
	frF.open(fileName, ios::in);										// open file write using file object					
	if (frF.is_open()){													// check if file is open
		while(getline(frF, line)){										// get the string from each line
			std::transform(line.begin(), line.end(), line.begin(), ::toupper);
			for (char c : line){
				if ((c >= 'A' && c <= 'Z') || c == ' ' || c == '\n'){
					string cur_char = "";
					cur_char += c;
					file_text += cur_char;
				}
			}
		}
	}
	frF.close();														// close
	return file_text;
}


#endif




