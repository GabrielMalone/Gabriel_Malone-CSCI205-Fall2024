#ifndef H_STUDENT
#define H_STUDENT

#include <string>

class Student{
	private:
		int id;
		std::string name;
		std::string dorm;

	public:

		Student(){
			id = 0;
			name = "";
			dorm = "";
		}

		Student(int id, std::string name){
			this->id 	= id;
			this->name 	= name;
		};
		int getID() const{
			return this->id;
		};
		std::string getName() const{
			return this->name;
		};
		std::string getDorm() const{
			return this->dorm;
		};
		void setDorm(std::string dorm){
			this->dorm = dorm;
		};
		
		/**
		 *  needed to overload this for main functionality
		*/
		bool operator == (Student &otherStudent) const {
			return this->id == otherStudent.getID();
		}
};
#endif
