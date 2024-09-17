#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
	private:
		int PID;				// Process ID
		std::string Command;	// Command
		std::string Time;		// Time in seconds
		int Mem;				// Memory in KB

	public:
		Task(int PID, std::string Command, std::string Time, int Mem);	// Constructor

		// Getters and Setters
		int getPID();
		std::string getCommand();
		std::string getTime();
		int getMem();
		void setTime(std::string Time);
		void setMem(int Mem);

		// Overload the << operator.
		friend std::ostream& operator<<(std::ostream& os, const Task& p);
};
#endif