#include <iostream>
#include <vector>
#include <string>
#include "course.h"
#include "student.h"
#include "registrar.h"

using namespace std;

namespace BrooklynPoly{

    class Student;

    //course methods
    Course::Course(const string& courseName) : name(courseName) {};
    const string& Course::getName() const { return name; };
    bool Course::addStudent(Student* s){
        for(size_t i = 0; i < this->students.size(); ++i){
                if (s == this->students[i]){
                    return false;
                }
            }
            this->students.emplace_back(s); 
            return true;
    }
    void Course::removeStudentsFromCourse(){
        students.clear();
    }
    ostream& operator<<(ostream& os, const Course& rhs){
        os << rhs.name << ": ";
        if(rhs.students.size() == 0){
            os << "No Students";
        }
        else{
            for(const Student* s : rhs.students){
                os << s->getName() << " ";
            }
        }
        return os;
    };

}