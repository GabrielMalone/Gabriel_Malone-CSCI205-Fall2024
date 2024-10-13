// Gabriel Malone // CSCI205 // WEEK 5
#ifndef H_FILE_OPENER
#define H_FILE_OPENER

#include <fstream>
#include <string>
#include "List.hpp"




using namespace std;

struct FileOpener{

	/**
	 * Load dorms / students from a text file into a linked list
	 */
	static void contactLoader(string fileName, List<Contact>& stringList) {	// pass List reference
		fstream frF;														// new filestream obj	
		string contact;														// string for each task in file
		string name;
		string email;
		string phone;
		frF.open(fileName, ios::in);										// open file write using file object					
		if (frF.is_open()){													// check if file is open
			while(getline(frF, contact)){									// get the string from each line
				int delimiter = contact.find(',');
				name = contact.substr(0, delimiter);						// get name
				contact = contact.substr(delimiter + 1, contact.length());
				delimiter = contact.find(',');
				email = contact.substr(0, delimiter);						// get email
				phone = contact.substr(delimiter + 1, contact.length());	// get phone
				Contact c {name, email, phone}	;							// create contact object
				stringList.insert(c);  										// place object in list
			}
		}
		frF.close();														// close
	}
};

#endif




