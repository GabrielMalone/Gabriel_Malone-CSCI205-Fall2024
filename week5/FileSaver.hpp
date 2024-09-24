#ifndef H_FILE_SAVER
#define H_FILE_SAVER


#include <fstream>
#include <string>
#include "Dorm.hpp"


using namespace std;

/**
 *  show the results of the dorm assignments for all dorms in terminal and via .txt files
 */
void saveDormLists(List<Dorm<Student> > & allDormObj)  {
    Node<Dorm<Student> >* dormObjs = allDormObj.get_head();                         // iterate through linked list ^
    while (dormObjs != NULL){                                                       // iterate
        ofstream outFile(dormObjs->data.getDormName() + ".txt");                    // create text file based on name of dorm
        if (outFile.is_open()){                                                     // while file is still open...
                outFile << dormObjs->data.getDormName() << ": " << dormObjs->data.getNumberOfStudents() << "\n";
                outFile << "----------------\n";                            
                Node<Student>* s_node = dormObjs->data.getStudents().get_head();    // iterate through students in each dorm
                while (s_node != NULL){ 
                    int studentID = s_node->data.getID();                           // get student info
                    string studentName = s_node->data.getName();                    // get student info
                    outFile << studentID;                                           // output the student info
                    outFile << " - ";
                    outFile << studentName;
                    outFile << "\n";
                    s_node = s_node->next;
                }
                dormObjs = dormObjs->next;                                          // continue to iterate to next dorm
                outFile << endl;
        }                                                                           
    }
}

/**
 *  show the results of the dorm assignments for all dorms in terminal and via .txt files
 */
void printDormLists(List<Dorm<Student> >& allDormObj)  {
    Node<Dorm<Student> >* dormObjs = allDormObj.get_head();                         // iterate through linked list
    while (dormObjs != NULL){
        cout << dormObjs->data.getDormName() << ": " << dormObjs->data.getNumberOfStudents() << "\n";
        cout << "----------------\n";
        dormObjs->data.showStudents();                                              // call the class print function
        dormObjs = dormObjs->next;                      
        cout << "\n";
    }
}


#endif
