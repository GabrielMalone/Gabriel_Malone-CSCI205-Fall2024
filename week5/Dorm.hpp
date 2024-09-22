// Gabriel Malone // CSC205 // LAB 4 // WEEK 5

#include "LinkedList/LinkedList.hpp"
#include "Student.hpp"

using namespace std;

template <class Student>
class Dorm{
    
    private:

        List<Student> students;
        string dorm_name = "default";

    public:

        /**
         * Default const
         */
        Dorm (){

        }
        /**
         * Overloaded const
         */
        Dorm(string dorm_name){
            this->dorm_name = dorm_name;
        }

        /**
         *  return the linked list of students associated with this dorm
         */
        List<Student> getStudents() const {
            return students;
        }

        /**
         * Add a student to this dorm
         */
        void addStudent(Student student){
            students.insert(student, 0);
        }

        /**
         * remove a student from this dorm via name
         */
        void removeStudent(string name){
           // need to traverse linked list
        }

        /**
         * remove a student from this dorm via ID
         */
        void removeStudent(int id){
            // need to traverse linked list
        }

        /**
         * remove a student from this dorm via Student object
         */
        void removeStudent(Student s){
            size_t pos = students.find(s);
            students.remove(pos);
        }

        /**
         * Load students from a text file into this dorm's linked list
         */
        void loadStudents(string fileName){
            vector<vector<string> > studentsVec = FileOpener::tokenizeFile(fileName, " ");
            for (vector<string> student : studentsVec){                  // iterate through tokens in the vectors
                int id =  stoi(student[0]);                              // get id
                string name = student[1];                                // get name
                Student s(id, name);                                     // create student objects                                                   
                students.insert(s,0);                                    // append student object to dorm
            }
        }

        /**
         * print a list of this dorm's current students
         */
        void showStudents(){
            Node<Student>* s_node = students.get_head();
            while (s_node != NULL){
                cout << s_node->data.getName() << endl;
                s_node = s_node->next;
            }
        }

};