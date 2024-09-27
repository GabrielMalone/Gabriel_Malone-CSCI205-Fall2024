// GABRIEL MALONE // CSCI205 // WEEK5 // LAB4

#include <iostream>
#include <string>
#include <random>
#include "List/ArrayList.hpp"
#include "backend/FileOpener.hpp"
#include "backend/Student.hpp"
#include "backend/Dorm.hpp"
#include "backend/FileSaver.hpp"
#include "frontend/Menu.hpp"

using namespace std;

Dorm<Student> d;                                                        // default global dorm for reasons
List<Dorm<Student> > allDormObj;                                        // List to hold all of the dorm objects
size_t minPopFinder();                                                  // helper function
Student getStudent(int);                                                // helper function
Dorm<Student>& getDorm(string);                                         // helper function


int main(){

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "INSERT (ITEM, POSITION) -- ARRAY VS LIST  (also testing PRINT and LENGTH)                                                   " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  

    cout << endl;

    A_List<int> arrayList (30);                                        // instantiate ARRAY list
    List<int> linkedList;                                              // instantiate LINKED list

    for (size_t i = 0 ; i < 10 ; i ++){                                // fill each list with 10 values
        arrayList.insert(i, i);
        linkedList.insert(i,i);
    }

    cout << "Array List of length "  << arrayList.length() << ": ";    // confirm this works
    arrayList.print();  
    cout << "Linked List of length " << linkedList.length() << ": ";                                            
    linkedList.print();                                               

    arrayList.insert(45,5);                                             // for finding where to actually insert the item 
                                                                        // time complexity is O(1) time complexity since the memory
                                                                        // for this array is continguous and has already been
                                                                        // allocated. simply place the item at the index with 
                                                                        // bracket notation 'array[pos] = item;
                                                                        // however, if items come after this item, they need to be shifted
                                                                        // which is time complexity O(n). Also
                                                                        // if position exceeds current mem allocated for list, 
                                                                        // array list needs to resize and copy contents into new space.
                                                                        // This copying is a time complexity O(n) Linear.

    linkedList.insert(45,5);                                            // inserting item in linked list is O(n) Linear since
                                                                        // position needs to be found by traversing the list.
                                                                        // best case scenario is position is at front of list for O(1)
                                                                        // otherwise all basically O(n) Linear. No shifting or copying needed 
                                                                        // for any insertion/removal, though, at the cost of a little extra memory
                                                                        // per data point stored. 
                                                                    
    cout << endl;
    cout << "Array List result of inserting '45' at index '5': ";       // confirm insertion works
    arrayList.print();  
    cout << "Linked List result of inserting '45' at index '5': ";                                            
    linkedList.print();

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << " GET ITEM AT (POSITION) -- ARRAY VS LIST                                                                                    " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  
                                                 
    int a_item = arrayList.get(5);                                      // get item at index 5 (should return 45)
                                                                        // time complexity for returning item at index for an
                                                                        // array list should be O(1) since this is an indexing
                                                                        // operation and the memory is contiguous.


    int l_item = linkedList.get(5);                                     // get item at index 5 (should return 45)
                                                                        // time complexity for indexing operation on a linked 
                                                                        // list is O(n) linear since the list has to be traversed
                                                                        // to find the item (memory is not contiguous), starting
                                                                        // at the head of the list no matter the index desired.
                                                                        // Best case scenario is O(1) front of list, worst
                                                                        // case is O(n) back of list. 

    cout << endl;
    cout << "result of 'get(5)' from array list: " << a_item << "\n";   // confirm results
    cout << "result of 'get(5)' from linked list: " << l_item << "\n";  

    
    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "FIND ITEM AT (POSITION) -- ARRAY VS LIST                                                                                    " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  

    size_t indexA = arrayList.find(45);                                 // find first instance of this item in the list and return index                                                                     
    size_t indexB = linkedList.find(45);                                // find first instance of this item in the list and return index
                                                                        // time complexity for both linked list and array is linear O(n)
                                                                        // since both have to loop through their lists until they find the item. 
                                                                        // best case is item is at front of list for each O(1), worse case
                                                                        // the item is at back of list O(n) or not found.

    cout << endl;
    cout << "array list item '45' found at index: " << indexA << "\n";  // confirm results
    cout << "linked list item '45  found at index: " << indexB << "\n";

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "REMOVE ITEM AT (POSITION) -- ARRAY VS LIST                                                                                  " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  
  
    int itemA = arrayList.remove(5);                                    // remove and return item from array list at the specified index
                                                                        // time complexity for array list to find the item to remove 
                                                                        // is O(1) since indexing operation and memory is contiguous. 
                                                                        // if items needs to be shifted, however, this will be a linear
                                                                        // O(n) operation to shift items down so that they remain contiguous. 

    int itemB = linkedList.remove(5);                                   // remove and return item from linked list at the specified index
                                                                        // time complexity to find the item to remove is O(n) since 
                                                                        // list needs to be traversed. however, no shifting will need to take place
                                                                        // since pointers being used, non-contiguous memory allocation. 

    cout << endl;
    cout << "array list item removed at index 5: " << itemA << "\n";    // confirm results
    cout << "array list after removal: ";
    arrayList.print();
    cout << "linked list item found at index 5: "  << itemB << "\n";
    cout << "linked list after remvoal: ";
    linkedList.print();

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "COUNT -- ARRAY VS LIST                                                                                                      " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  
                                                                         // both of these are O(1) constant since each class 
                                                                         // keeps track of the size of the list in a variable
    cout << endl;
    cout << "array list has: " << arrayList.length() << " items\n";      // confirm results
    cout << "linked list has: " << linkedList.length() << " items\n";    // confirm results

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "REVERSE -- ARRAY VS LIST                                                                                                    " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  
    
                                                                        // reversal on the array list I have set to be O(n), but no extra memory
                                                                        // needed since I just swap values directly in the same array. 

                                                                        // reversal for the linked list required at least O(n) as well, but also extra memory
                                                                        // to store the current state of the list (in a dynamic array)/
                                                                        // the dynamic array is then iterated through backwards and the nodes are updated
                                                                        // with those values. 
    cout << endl;
    cout << "array list prior to reverse: \n"; 
    arrayList.print();                                                  // show list prior to reversal
    cout << "array list post reverse: \n"; 
    arrayList.reverse();                                                // reverse
    arrayList.print();                                                  // confirm results

    cout << endl;
    cout << "linked list prior to reverse: \n";     
    linkedList.print();                                                 // show list prior to reversal
    cout << "linked list post reverse: \n";  
    linkedList.reverse();                                               // reverse
    linkedList.print();                                                 // confirm results

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << " REMOVE DUPLICATES & COUNT-- ARRAY VS LIST                                                                                  " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  
                                                                        // removing duplicates for both the array and the linked lists
                                                                        // required a time complexity of linear O(n) since both lists
                                                                        // need to be iterated through in their entirety to find potential duplicates.
                                                                        // extra memeory needed as well to store found duplciates. ahtough I did 
                                                                        // come up with a solution that did not require extra memory 
                                                                        // for the linked list but valgrind did not like it. 
                                                                

    //--------------------------------------------------------------------------------------------------------------------------
    // ARRAY LIST ADD DUPLICATES                                      
    //--------------------------------------------------------------------------------------------------------------------------
    arrayList.insert(1, 0);                                             
    arrayList.insert(1, 5);
    arrayList.insert(1, 6);
    arrayList.insert(1, 7);
    arrayList.insert(1, 0);                                             
    arrayList.insert(2, 5);
    arrayList.insert(1, 6);
    arrayList.insert(2, 0);
    arrayList.insert(2, 1);
    arrayList.insert(1, 2);
    arrayList.insert(2, 3);
    cout << "duplicates added: ";
    arrayList.print();
    //--------------------------------------------------------------------------------------------------------------------------
    // COUNT THE DUPLICATES PRESENT IN ARRAY LIST                                
    //--------------------------------------------------------------------------------------------------------------------------
    for (size_t i  = 0 ; i < arrayList.length(); i ++ ){
        size_t c = arrayList.count(i);
        if (c > 1){
            cout << "There are now "
            << c 
            << " number "<< i << "'s" 
            << endl;
        }
    }
    //--------------------------------------------------------------------------------------------------------------------------
    // REMOVE AND CONFIRM REMOVAL OF DUPLICATES IN ARRAY LIST                            
    //--------------------------------------------------------------------------------------------------------------------------
    cout << "duplicates removed: ";                                     // confirm duplicates
    arrayList.removeDuplicates();
    arrayList.print();                                                  // confirm no duplicates
    //--------------------------------------------------------------------------------------------------------------------------
    // LINKED LIST ADD DUPLICATES                                      
    //--------------------------------------------------------------------------------------------------------------------------
    linkedList.insert(5, 0);                                           
    linkedList.insert(1, 5);
    linkedList.insert(4, 6);
    linkedList.insert(1, 7);
    linkedList.insert(3, 0);                                          
    linkedList.insert(2, 5);
    linkedList.insert(1, 6);
    linkedList.insert(2, 0);
    linkedList.insert(2, 1);
    linkedList.insert(1, 2);
    linkedList.insert(2, 3);
    linkedList.insert(9, 3);
    cout << "duplicates added: ";
    linkedList.print();
    //--------------------------------------------------------------------------------------------------------------------------
    // COUNT THE DUPLICATES PRESENT IN LINKED LIST                            
    //--------------------------------------------------------------------------------------------------------------------------
    for (size_t i  = 0 ; i < linkedList.length(); i ++ ){
        size_t c = linkedList.count(i);
        if (c > 1){
            cout << "There are now "
            << c 
            << " number "<< i << "'s" 
            << endl;
        }
    }         
    //--------------------------------------------------------------------------------------------------------------------------
    // REMOVE AND CONFIRM REMOVAL OF DUPLICATES IN LINKED LIST                              
    //--------------------------------------------------------------------------------------------------------------------------                                      
    cout << "duplicates removed: ";
    linkedList.removeDuplicates();                                      
    linkedList.print();

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "APPEND -- ARRAY VS LIST                                                                                                     " << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  

    cout << endl; 

                                                                        // the time complexity for the linked list append
                                                                        // is constant O(1) by just pointing the original list
                                                                        // at the head of the list to be appended, with no extra memmory needed.
                                                                        // array iterates with time complexity O(n) in order to get the data 
                                                                        // from the lists being appended. extra memory needed for temp array as well.

    List<int>linkedList2;                                               // make a new list
    A_List<int> arrayList2;                                             // instantiate ARRAY list

    for (size_t i = 0 ; i < 10 ; i ++){                                 // fill each list with 10 values
        arrayList2.insert(i, i);
        linkedList2.insert(i,i);
    }
    cout << endl;
    cout << "new linked list: \n";     
    linkedList2.print();  
    cout << "original linked list prior to append: \n";     
    linkedList.print();
    linkedList.append(linkedList2);
    cout << "linked list after append: \n";    
    linkedList.print();
    cout << endl;
    cout << "new array list: \n";     
    arrayList2.print();  
    cout << "original array list prior to append: \n";     
    arrayList.print();
    arrayList.append(arrayList2);
    cout << "array list after append: \n";    
    arrayList.print();

    cout << endl;
    
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "DORM PORTION OF LAB  - dorms loaded, students assigned to dorms with fewest students, at random.                           "  << endl;  
    cout << "//--------------------------------------------------------------------------------------------------------------------------" << endl;  

    cout << endl; 

    //--------------------------------------------------------------------------------------------------------------------------
    // INITIALIZE LOCAL LISTS
    //--------------------------------------------------------------------------------------------------------------------------

    List<string> allStudentStr;                                         // List to hold all the students loaded from the students text file
    List<string> allDormStr;                                            // List to hold names of the dorms loaded from the dorms text file
    List<Student> allStudentObj;                                        // List to hold all the student objects
    
    
    //--------------------------------------------------------------------------------------------------------------------------
    // LOAD DORM DATA -- INTO TEXT LIST THEN DORM OBJECT LIST
    //--------------------------------------------------------------------------------------------------------------------------
    FileOpener::dormLoader("text_source/dormFile.txt", allDormStr);     // load all dorms from text file into dormstring list
    Node<string>* dorm_head = allDormStr.get_head();                    // iterate through linked list ^
    while (dorm_head != NULL){
        allDormObj.insert(Dorm<Student>(dorm_head->data), 0);           // create dorm object with dormname parameter (head->data) and insert into dorm linked list
        dorm_head = dorm_head->next;                                    // continue iterating
    }
    //--------------------------------------------------------------------------------------------------------------------------
    // LOAD STUDENT DATA -- INTO TEXT LIST THEN STUDENT OBJECT LIST
    //--------------------------------------------------------------------------------------------------------------------------    
    FileOpener::dormLoader("text_source/studentFile.txt", allStudentStr); // load all students from text file
    Node<string>* student_head = allStudentStr.get_head();              // iterate through linked list ^
    while (student_head != NULL){                                       // loop until tail of linked list (will always be a list of 2 items)
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
        Student s(studentID, studentName);
        allStudentObj.insert(s,0);                                      // create student object and insert into student linked list
        student_head = student_head->next;                              // continue iterating
    }
    //--------------------------------------------------------------------------------------------------------------------------
    // ASSIGN STUDENTS TO DORMS RANDOMLY // LOWEST POP DORMS GET PRIORITY
    //--------------------------------------------------------------------------------------------------------------------------
     size_t num_of_dorms = allDormObj.length();                         // number of dorms available for students
     random_device rd;                                                  // random number generator for random dorm assignment
     mt19937 gen(rd());                                        
     uniform_int_distribution<> dist(0, num_of_dorms - 1);              // range from 0 index to num of dorms - 1 for 0 index
     size_t min_pop = minPopFinder(); 
     Node<Student>* s = allStudentObj.get_head();                       // get current minimum pop (will start at 0)
     while (s != NULL){                                                 // loop until all students assigned                    
        int random_index = dist(gen);                                   // check dorm pops at random
        Dorm<Student>& d = allDormObj.get(random_index);                // check dorm pops at random
        if (d.getNumberOfStudents() == min_pop){                        // if dorm pop matches min pop, good to go
            // cout << d.getDormName() << " accepts:" << "\n";          // show that this is working
            //                                                          // get the next student in line
            // cout << s->data.getID() << " ";                          // confirm working
            // cout << s->data.getName() << "\n";                       // confirm working
            // cout << endl;       '
            s->data.setDorm(d.getDormName());                           // set dorm name for each student
            d.addStudent(s->data);
            s = s->next;                                                // add the student to the dorm
            min_pop = minPopFinder();                                   // set new min pop
        } 
     }     

    //--------------------------------------------------------------------------------------------------------------------------
    // SHOW ABILITY TO REASSIGN STUDENTS  -  1) FIND STUDENT VIA UNIQUE ID 
    //--------------------------------------------------------------------------------------------------------------------------
    cout << endl;
    printDormLists(allDormObj);                                                                     // show dorm info in terminal
    size_t searched_ID;                                                           // var to hold studentID that user searches for
    cout << "ENTER ID OF STUDENT TO TRANSFER: ";                      
    cin >> searched_ID;                                                       // get ID, invalid inputs will return defaul values
    
    Student studentFound = getStudent(searched_ID);                             // get and remove student from their current dorm
    cout << "-----------------------------------------------------\n" << endl;                            
    cout << "FOUND AND REMOVED STUDENT: '" << studentFound.getName() << "' FROM DORM: '" 
        << studentFound.getDorm() << "'\n" << endl;                         // get dormName of dorm to which this student belongs
    cout << "-----------------------------------------------------\n" << endl; 
    cout << "DORM: '" << getDorm(studentFound.getDorm()).getDormName() << "' NOW HAS: " 
        << getDorm(studentFound.getDorm()).getNumberOfStudents() << " STUDENTS\n" << endl;
    cout << "-----------------------------------------------------\n" << endl; 
    //--------------------------------------------------------------------------------------------------------------------------
    // SHOW ABILITY TO REASSIGN STUDENTS  -  2) ADD STUDENT TO ANOTHER DORM
    //--------------------------------------------------------------------------------------------------------------------------
    string newDorm;
    cout << "TRANSFER: " << studentFound.getName() << " TO DORM: ";
    cin >> newDorm;
    getDorm(newDorm).addStudent(studentFound);     // add stuedent to the selected dorm // student is lost forever if this fails
    cout << "-----------------------------------------------------\n" << endl;                            
    cout << "ADDED STUDENT: '" << studentFound.getName() << "' INTO DORM: '"  << newDorm << "'\n" << endl;
    cout << "-----------------------------------------------------\n" << endl; 

    cout << "DORM: '" << getDorm(studentFound.getDorm()).getDormName() << "' NOW HAS: "
         << getDorm(studentFound.getDorm()).getNumberOfStudents() << " STUDENTS\n" << endl;
    cout << "-----------------------------------------------------\n" << endl; 
    getDorm(studentFound.getDorm()).showStudents();                                                       // confirm this worked

                                                                         
    //--------------------------------------------------------------------------------------------------------------------------
    // PRINT AND SAVE DORM POP INFO 
    //--------------------------------------------------------------------------------------------------------------------------
    saveDormLists(allDormObj);                                                                   // save dorm info to text files

    return 0;
}

//--------------------------------------------------------------------------------------------------------------------------
// HELPER FUNCTIONS FOR THE DORM TASKS 
//--------------------------------------------------------------------------------------------------------------------------

/**
 *  helper function to determine the dorm with the current lowest pop
 */
size_t minPopFinder() {
    size_t min_pop = 9999;                                         // min pop variable initialize
    Node<Dorm<Student> >* dormObjs = allDormObj.get_head();        // get head to traverse dorm list
    while (dormObjs != NULL){                                     
        size_t dorm_pop = dormObjs->data.getNumberOfStudents();    // get population of current dorm
        if (dorm_pop <= min_pop){                                  // if current dorm's pop less than min
            min_pop = dorm_pop;                                    // set new min
        }
        dormObjs = dormObjs->next;                                 // move to next dorm
    }
    return min_pop;                                                // return new min value
}

/**
 * Select a student via ID. 
 * This will return the student from the dorm (removing the student from that dorm)
 * and will place the student into the dorm passed in as a parameter
 */
Student getStudent(int studentID){
    Student s;
    Node<Dorm<Student> >* dorms = allDormObj.get_head();           // iterate through list of dorms 
    while (dorms != NULL){                                         // put this function in dorm class                          
        Node<Student>* student_node = dorms->data.getStudents().get_head();
        while (student_node != NULL){                              // loop through students at that dorm
            if (student_node->data.getID() == studentID){          // find student with desired ID 
                s = student_node->data;                            // get that student's student object
                dorms->data.removeStudent(s);                      // remove them from this dorm
                return s;                                          // return the student
                }
                student_node = student_node -> next;
            }
            dorms = dorms->next;
        }
            return s;                                               // return null student if no student found
    }

/**
 * get dorm object via dormname
 */
Dorm<Student>& getDorm(string dormName){
    Node<Dorm<Student> >* dorms = allDormObj.get_head();            // iterate through list of dorms
    while (dorms != NULL){
        if (dormName == dorms->data.getDormName()){                 // if dormname parameter matches current dorm, return it
        return dorms->data;      
        }
        dorms = dorms->next;
    }
    return d;                                                   
}
    
    
