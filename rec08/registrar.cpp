#include <iostream>
#include <vector>
#include <string>
#include "registrar.h"
#include "student.h"
#include "course.h"

using namespace std;

namespace BrooklynPoly{
    class Student;
    class Course;   

    //registrar methods

    Registrar::Registrar() {};

    size_t Registrar::findStudent(const string& name) const{
            for(size_t i = 0; i < students.size(); ++i){
                if (name == students[i]->getName()){
                    return i;
                }
            }
            return students.size();
        };
    size_t Registrar::findCourse(const string& name) const{
        for (size_t i = 0; i < courses.size(); ++i){
            if (name == courses[i]->getName()){
                return i;
            }
        }
        return courses.size();
    };
    bool Registrar::addCourse(const string& name){
        if (findCourse(name) < this->courses.size()){
            return false;
        }
        this->courses.emplace_back(new Course(name));
        
        return true;
    };
    bool Registrar::addStudent(const string& name){
        if (findStudent(name) < this->students.size()){
            return false;
        }
        this->students.emplace_back(new Student(name));
        return true;
    };
    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName){
            size_t s_i = findStudent(studentName);
            size_t c_i = findCourse(courseName);
            if (s_i == students.size() || c_i == courses.size()){
                return false;
            }

            this->students[s_i]->addCourse(courses[c_i]);
            this->courses[c_i]->addStudent(students[s_i]);
            return true;
        };

    bool Registrar::cancelCourse(const string& courseName){
        size_t c_i = findCourse(courseName);
        if(c_i == courses.size()){
            return false;

        }
        //remove cyclic association
        this->courses[c_i]->removeStudentsFromCourse();
        for (Student* s : this->students){
            s->removedFromCourse(courses[c_i]);
        }

        //remove from courses
        if (c_i == courses.size() - 1){
            courses.pop_back();
        }
        else{
            for(size_t j = c_i; j < courses.size(); ++j){
                courses[j] = courses[j + 1];
            }
            courses.pop_back();
        }

        return true;
    }

    void Registrar::purge(){
        for (Course* c : courses){
            delete c;
        }
        for (Student* s : students){
            delete s;
        }
        courses.clear();
        students.clear();
    }

    ostream& operator<<(ostream& os, const Registrar& rhs){
        os << "Registrar's Report" << endl;
        os << "Courses:" << endl;
        for(const Course* c : rhs.courses){
            os << *c << endl;
        }
        os << "Students:" << endl;
        for(const Student* s : rhs.students){
            os << *s << endl;
        }
        return os;
    };
}