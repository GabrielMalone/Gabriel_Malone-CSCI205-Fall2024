// GABRIEL MALONE // CSCI205 // WEEK5 // LAB4

#include <iostream>
#include <string>
#include <vector>
#include "LinkedList/LinkedList.hpp"
#include "FileOpener.hpp"
#include "Student.hpp"
#include "Dorm.hpp"

using namespace std;

int main(){

    Dorm<Student> g("goob");

    g.loadStudents("studentFile.txt");
    g.addStudent(Student(68, "goobert"));
    g.showStudents();

    // TODO -> 1) from text file read the dorms and create Dorm objects from each dorm (take those functions out of the dorm class and put here)
    // TODO -> 2) from text file read the students and load them into student objects (take those functions out of the dorm class and put here)
    // TODO -> 3) randomly assign students to a dorm (dorms with fewer students get priority)
    // TODO -> 4) output the roster from each dorm to its own text file

    return 0;
}
