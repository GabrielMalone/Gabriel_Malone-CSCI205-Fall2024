#include "Task.h"
#include <iostream>


Task::Task(int PID, std::string Command, std::string Time, int Mem) {
	this->PID		= PID;
	this->Command	= Command;
	this->Time		= Time;
	this->Mem		= Mem;
}

int Task::getPID() {
	return PID;
}

std::string Task::getCommand() {
	return Command;
}

std::string Task::getTime() {
	return Time;
}

int Task::getMem() {
	return Mem;
}

void Task::setTime(std::string Time) {
	this->Time = Time;
}

void Task::setMem(int Mem) {
	this->Mem = Mem;
}

std::ostream& operator<<(std::ostream& os, const Task& t) {
	os << "PID: " << t.PID << ", Command: " << t.Command << ", Time: " << t.Time << ", Mem: " << t.Mem;
	return os;
}

