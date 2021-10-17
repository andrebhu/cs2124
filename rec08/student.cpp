#include <iostream>
#include <vector>
#include <string>
#include "student.h"
#include "course.h"
#include "registrar.h"
using namespace std;

namespace BrooklynPoly{
    class Course;

    //student methods

    Student::Student(const string& name) : name(name){};
    const string& Student::getName() const { return name; };
    bool Student::addCourse(Course* c){
        for(size_t i = 0; i < this->courses.size(); ++i){
            if (c == this->courses[i]){
                return false;
            }
        }
        this->courses.emplace_back(c);
        return true;
    }
    void Student::removedFromCourse(Course* c){
        for (size_t i = 0; i < this->courses.size(); ++i){
            if (c == this->courses[i]){
                if (i == this->courses.size() - 1){
                    this->courses.pop_back();
                }
                else{
                    for (size_t j = i; j < this->courses.size(); ++j){
                        this->courses[j] = this->courses[j + 1];
                    }
                    this->courses.pop_back();
                }
            }
        }
    }

    ostream& operator<<(ostream& os, const Student& rhs){
        os << rhs.name << ": ";
        if (rhs.courses.size() == 0){
            os << "No Courses";
        }
        else{
            for(const Course* c : rhs.courses){
                os << c->getName() << " ";
            }
        }
        return os;
    }
}