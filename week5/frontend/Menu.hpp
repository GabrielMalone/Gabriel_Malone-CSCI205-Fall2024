// GABRIEL MALONE // CSCI205 // WEEK5 // LAB4

#ifndef Menu_H
#define Menu_H

#include <iostream>
#include <string>
#include "../List/ArrayList.hpp"
#include "../backend/FileOpener.hpp"
#include "../backend/Student.hpp"
#include "../backend/Dorm.hpp"
#include "../backend/FileSaver.hpp"
#include <iomanip>

using namespace std;

class Menu{

    public:

    void static welcomeMenu(List<Dorm<Student> >& dormsInSystem){
        cout << "+------------------------------------------------------------------+" << endl;
        cout << "|                 MEGACORP DORM MANAGEMENT SOFTWARE                |" << endl;
        cout << "+------------------------------------------------------------------+" << endl;
        cout 
             << "| CURRENT DORMS IN SYSTEM  " << dormsInSystem.length()
             << setw(40) 
             << setfill(' ')
             << right 
             << "|"
             << endl;
        cout << "+------------------------------------------------------------------+" << endl;
    }

    void static listDorms(List<Dorm<Student> >& dormsInSystem){
        Node<Dorm<Student> >* dorms = dormsInSystem.get_head();
        int count = 0; 
        while(dorms != NULL){
            count ++;
            cout 
                 << "| " 
                 << count 
                 << " - " 
                 << setw(60) << left 
                 << dorms->data.getDormName() 
                 << " |" 
                 << endl;
            dorms = dorms->next;
        }
        cout << "+------------------------------------------------------------------+" << endl;
    }

    static string dormSelect(List<Dorm<Student> >& dormsInSystem){
        size_t selection{};
        size_t count{};
        cout << "Select dorm: ";
        cin >> selection;
        cout << endl;
        Node<Dorm<Student> >* dorms = dormsInSystem.get_head();       // iterate through list of dorms
        while (dorms != NULL){
            count ++ ;
            if (selection == count){            // if dormname parameter matches current dorm, return it
                string dormname = dorms->data.getDormName();
                string capName{};
                for (char c : dormname){
                    capName += toupper(c);
                }
                cout << "+------------------------------------------------------------------+\n"
                     << capName  << " (" << dorms->data.getNumberOfStudents() << " students)" << "\n"
                     << "+------------------------------------------------------------------+" 
                     << endl;
                return dorms->data.getDormName();      
                }
        dorms = dorms->next;
        }
        return "";   
    }

    static void subMenu(){
        cout << "(A)DD STUDENT | (R)EMOVE STUDENT | (M)OVE STUDENT" << endl;
    }

};

#endif