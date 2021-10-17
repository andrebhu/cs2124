/*
  rec08_starter.cpp
  Starter Code for required functionality
  Yes, of course, you may add other methods.
  And no, this won't compile. You have to fix the cyclic association.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;

class Course {
    friend ostream& operator<<(ostream& os, const Course& rhs);
public:
    // Course methods needed by Registrar
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student*);
    void removeStudentsFromCourse(); 

private:
    string name;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& rhs);
public:
    // Student methods needed by Registrar
    Student(const string& name);
    const string& getName() const;
    bool addCourse(Course*);

    // Student method needed by Course
    void removedFromCourse(Course*);

private:
    string name;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& rhs);
public:
    Registrar();
    bool addCourse(const string&);
    bool addStudent(const string&);
    bool enrollStudentInCourse(const string& studentName,
                               const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();

private:
    size_t findStudent(const string&) const;
    size_t findCourse(const string&) const;

    vector<Course*> courses;
    vector<Student*> students;
};
  


//course methods
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

    for(Student* s : students){
        s->removedFromCourse(this);
    }
    students.clear();
}



//student methods
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
};
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




//registrar methods
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




int main() {

    Registrar registrar;

    cout << "No courses or students added yet\n";
    cout << registrar << endl;

    cout << "AddCourse CS101.001\n";
    registrar.addCourse("CS101.001");
    cout << registrar << endl;

    cout << "AddStudent FritzTheCat\n";
    registrar.addStudent("FritzTheCat");
    cout << registrar << endl;

    cout << "AddCourse CS102.001\n";
    registrar.addCourse("CS102.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    registrar.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << registrar << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    registrar.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << registrar << endl;

    cout << "CancelCourse CS102.001\n";
    registrar.cancelCourse("CS102.001");
    cout << registrar << endl;

    /*
    // [OPTIONAL - do later if time]
    cout << "ChangeStudentName FritzTheCat MightyMouse\n";
    registrar.changeStudentName("FritzTheCat", "MightyMouse");
    cout << registrar << endl;  

    cout << "DropStudentFromCourse MightyMouse CS101.001\n";
    registrar.dropStudentFromCourse("MightyMouse", "CS101.001");
    cout << registrar << endl;  

    cout << "RemoveStudent FritzTheCat\n";
    registrar.removeStudent("FritzTheCat");
    cout << registrar << endl;  
    */

    cout << "Purge for start of next semester\n";
    registrar.purge();
    cout << registrar << endl;
}
