// Gabriel Malone // CSC205 // LAB 4 // WEEK 5

#ifndef H_DORM
#define H_DORM

#include "LinkedList/LinkedList.hpp"
#include "Student.hpp"

using namespace std;

template <class Student>
class Dorm{
    
    private:

        size_t number_of_students = 0;
        List<Student> students;
        string dorm_name = "default";

    public:

        /**
         * Default const
         */
        Dorm (){}

        /**
         * Overloaded const
         */
        Dorm(string dorm_name){
            this->dorm_name = dorm_name;
        }

        /**
         *  return the linked list of students associated with this dorm
         */
        List<Student> getStudents() {
            return this->students;
        }

        /**
         * Add a student to this dorm
         */
        void addStudent(Student s){
            this->students.insert(s, number_of_students);
            this->number_of_students ++;
        }

        /**
         * remove a student from this dorm via name
         */
        void removeStudent(string name){
           // need to traverse linked list
           this->number_of_students --;
        }

        /**
         * remove a student from this dorm via ID
         */
        void removeStudent(int id){
            // need to traverse linked list
           this-> number_of_students --;
        }

        /**
         * remove a student from this dorm via Student object
         */
        void removeStudent(Student s){
            size_t pos = students.find(s);
            students.remove(pos);
        }
        
        /**
         * returns the number of students living in this dorm
         */
        size_t getNumberOfStudents() const {
            return this->number_of_students;
        }

        /**
         * returns the name of this dorm
         */
        string getDormName() const {
            return this->dorm_name;
        }
        
        /**
         * print a list of this dorm's current students
         */
        void showStudents(){
            Node<Student>* s_node = students.get_head();
            while (s_node->next != NULL){
                cout << s_node->data.getID() << " - " << s_node->data.getName() << endl;
                s_node = s_node->next;
            }
        }

};

#endif
