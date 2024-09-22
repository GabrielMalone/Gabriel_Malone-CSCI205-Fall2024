#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct FileOpener{
	static vector<vector<string> > tokenizeFile(string fileName, string delimeter){
		vector<vector<string>>output;										// vector of vectors to hold final split string outputs from file
		fstream frF;														// new filestream obj	
		string tStr;														// string for each task in file
		frF.open(fileName, ios::in);										// open file write using file object					
		if (frF.is_open()){													// check if file is open
			while(getline(frF, tStr)){
				vector<string>tokens;										// hold the current split line's tokens
				while (tStr.find(delimeter) != std::string::npos)
				{	
					string token = tStr.substr(0,tStr.find(delimeter));		// start splittin string at delimeter
					tokens.push_back(token);								// place each split into vector
					tStr = tStr.substr(tStr.find(delimeter) + 1);			// reduce size of string to post split
				}
				tokens.push_back(tStr);										// push the remaining string piece
				output.push_back(tokens);									// push split string to output vector
			}
		}
		return output;
	}
};



