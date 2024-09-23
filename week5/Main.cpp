// GABRIEL MALONE // CSCI205 // WEEK5 // LAB4

#include <iostream>
#include <string>
#include <random>
#include "LinkedList/LinkedList.hpp"
#include "FileOpener.hpp"
#include "Student.hpp"
#include "Dorm.hpp"
#include "FileSaver.hpp"

using namespace std;


List<Dorm<Student> > allDormObj;                                        // List to hold all of the dorm objects

size_t minPopFinder();                                                  // helper function


int main(){

    List<string> allStudentStr;                                         // List to hold all the students loaded from the students text file
    List<string> allDormStr;                                            // List to hold names of the dorms loaded from the dorms text file
    List<Student> allStudentObj;                                        // List to hold all the student objects
    //--------------------------------------------------------------------------------------------------------------------------
    // LOAD DORM DATA -- INTO TEXT LIST THEN DORM OBJECT LIST
    //--------------------------------------------------------------------------------------------------------------------------
    allDormStr = FileOpener::dormLoader("dormFile.txt");                // load all dorms from text file into dormstring list
    Node<string>* dorm_head = allDormStr.get_head();                    // iterate through linked list ^
    while (dorm_head->next != NULL){
        allDormObj.insert(Dorm<Student>(dorm_head->data), 0);           // create dorm object with dormname parameter (head->data) and insert into dorm linked list
        dorm_head = dorm_head->next;                                    // continue iterating
    }
    //--------------------------------------------------------------------------------------------------------------------------
    // LOAD STUDENT DATA -- INTO TEXT LIST THEN STUDENT OBJECT LIST
    //--------------------------------------------------------------------------------------------------------------------------    
    allStudentStr = FileOpener::dormLoader("studentFile.txt");          // load all students from text file
    Node<string>* student_head = allStudentStr.get_head();              // iterate through linked list ^
    while (student_head->next != NULL){                                 // loop until tail of linked list (will always be a list of 2 items)
        List<string>tokens;	                                            // linked list to hold the split string data
        string studentStr = student_head->data;						    // hold the current split line's tokens
        while (studentStr.find(" ") != std::string::npos)               // loop until end of string
        {	
            string token = studentStr.substr(0,studentStr.find(" "));   // start splittin string at delimeter
            tokens.insert(token, 0);									// place each split into list
            studentStr = studentStr.substr(studentStr.find(" ") + 1);	// reduce size of string to post split
            tokens.insert(studentStr, 0);								// push the remaining string piece
        }
        int studentID = stoi(tokens.get(1));                            // get the data from the list
        string studentName = tokens.get(0);                             // get the data from the list
        allStudentObj.insert(Student(studentID, studentName),0);        // create student object and insert into student linked list
        student_head = student_head->next;                              // continue iterating
    }
    //--------------------------------------------------------------------------------------------------------------------------
    // ASSIGN STUDENTS TO DORMS RANDOMLY // LOWEST POP DORMS GET PRIORITY
    //--------------------------------------------------------------------------------------------------------------------------
     size_t num_of_dorms = allDormObj.length();                         // number of dorms available for students
     random_device rd;                                                  // random number generator for random dorm assignment
     mt19937 gen(rd());                                        
     uniform_int_distribution<> dist(0, num_of_dorms - 1);              // range from 0 index to num of dorms - 1 for 0 index
     size_t min_pop = minPopFinder();                                   // get current minimum pop (will start at 0)
     while (allStudentObj.length() > 0){                                // loop until all students assigned                    
        int random_index = dist(gen);                                   // check dorm pops at random
        Dorm<Student>& d = allDormObj.get(random_index);                // check dorm pops at random
        if (d.getNumberOfStudents() == min_pop){                        // if dorm pop matches min pop, good to go
            cout << d.getDormName() << " accepts:" << "\n";             // show that this is working
            Student s = allStudentObj.remove(0);                        // get the next student in line
            cout << s.getID() << " ";                                   // confirm working
            cout << s.getName() << "\n";                                // confirm working
            cout << endl;       
            d.addStudent(s);                                            // add the student to the dorm
            min_pop = minPopFinder();                                   // set new min pop
        } 
     }                                      
    //--------------------------------------------------------------------------------------------------------------------------
    // PRINT AND SAVE DORM POP INFO 
    //--------------------------------------------------------------------------------------------------------------------------
    printDormLists(allDormObj);                                         // show dorm info in terminal
    saveDormLists(allDormObj);                                          // save dorm info to text files

    return 0;
}

/**
 *  helper function to determine the dorm with the current lowest pop
 */
size_t minPopFinder() {
    size_t min_pop;                                                     // min pop variable initialize
    Node<Dorm<Student> >* dormObjs = allDormObj.get_head();             // get head to traverse dorm list
    while (dormObjs->next != NULL){                                     
        size_t dorm_pop = dormObjs->data.getNumberOfStudents();         // get population of current dorm
        if (dorm_pop <= min_pop){                                       // if current dorm's pop less than min
            min_pop = dorm_pop;                                         // set new min
        }
        dormObjs = dormObjs->next;                                      // move to next dorm
    }
    return min_pop;                                                     // return new min value
}
