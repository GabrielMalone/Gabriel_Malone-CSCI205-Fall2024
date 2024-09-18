// GABRIEL MALONE / CSCI 205 / LAB 3

#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Queue.hpp"
#include "Task.h"

using namespace std;


void ringBuffer(){
	// instantiate Queue of Tasks
	Queue<Task> task_data;
	// filestream to open text data
	fstream frF;
	// string for each task in file
	string tStr;
	// open file write using file object
	// check if file is open
	frF.open("tasks.txt", ios::in);
	if (frF.is_open()){
		while(getline(frF, tStr)){
			vector<string>tokens;
			// instantiate task vars
			// run until no more tabs found
			while (tStr.find('\t') != std::string::npos)
			{	
				// start splittin string at space
				string token = tStr.substr(0,tStr.find('\t'));
				// place each split into vector
				tokens.push_back(token);
				// reduce size of string to post split
				tStr = tStr.substr(tStr.find('\t') + 1);
			}
			// push the remaining string piece
			tokens.push_back(tStr);
			// create task object
			// place task object in Queue
			int PID = stoi(tokens[0]);
			string progName = tokens[1];
			string time = tokens[2];
			int mem = stoi(tokens[3]);
			// instantiate Task
			Task t(PID, progName, time, mem);
			// enqueue task
			task_data.enqueue(t);
		}
	}
	// confirm fill of queue
	while (! task_data.is_empty()){
		// dequeue the next task
		Task t = task_data.dequeue();
		// display that task in terminal for a second
		cout << "dequeing element: " << t << endl;
		
		// update the time of that task
		string current_task_time = t.getTime(); // get current time
		size_t updated_second = stoi(current_task_time.substr(current_task_time.length() - 2)); // get the seconds and convert to int
		string updated_time = current_task_time.substr(0, current_task_time.length() - 2) + to_string(updated_second + 1); // add a second and reattach
		t.setTime(updated_time); // set the time
		cout << "updated time: " << t.getTime() << endl;
		cout << "enqueing updated task :"  << t << endl;
		task_data.enqueue(t); // put the updated task back in line
		this_thread::sleep_for(chrono::milliseconds(2000)); // set output delay 
		cout << endl;
	}
}