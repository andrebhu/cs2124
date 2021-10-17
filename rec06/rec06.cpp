/*
  Andre Hu
  3/5/2021
  School of Engineering CS Lab Administration
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;



//TimeSlot and StudentRecord are nested
class Section{
     friend ostream& operator<<(ostream& os, const Section& section){
          cout << "Section: " << section.name << ", Time slot: " << section.time << ", Students: ";
          if (section.students.size() == 0){
               cout << "None" << endl;
          }
          else{
               cout << endl;
               for(size_t i = 0; i < section.students.size(); ++i){
                    cout << *section.students[i] << endl;
               }
          }          
          return os;
     }

     public:
          Section(const string& name, const string& day, int hour) : name(name), time(TimeSlot(day, hour)){}
          
          //copy constructor
          Section(const Section& s) : name(s.name), time(s.time){
               for(size_t i = 0; i < s.students.size(); ++i){
                    students.push_back(new StudentRecord(*s.students[i]));
               }
          }

          ~Section(){
               cout << "Section " << name << " is being deleted " << endl;
               for (StudentRecord* s : students){
                    cout << "Deleting " << s->getName() << endl;
                    delete s;
               }               
          }

          void addStudent(const string& name){
               students.push_back(new StudentRecord(name));
          }

          void addGrade(const string& name, int grade, int week){
               for (size_t i = 0; i < students.size(); ++i){
                    if (students[i]->getName() == name){
                         students[i]->addGrade(grade, week);
                    }
               }
          }

     private:
          class TimeSlot{
               friend ostream& operator<<(ostream& os, const TimeSlot& timeslot){
                    cout << "[Day: " << timeslot.day << ", Start time: ";
                    if (timeslot.hour > 12){
                         int t = timeslot.hour - 12;
                         cout << t << "pm]";
                    }
                    else{
                         cout << timeslot.hour << "am]";
                    }
                    return os;
               }

               public:
                    TimeSlot(const string& day, int hour) : day(day), hour(hour) {}
               private:
                    string day;
                    int hour;
          };


          class StudentRecord{
               friend ostream& operator<<(ostream& os, const StudentRecord& sr){
                    cout << "Name: " << sr.name << ", Grades: ";
                    for(size_t i = 0; i < sr.grades.size(); ++i){
                         cout << sr.grades[i] << " ";
                    }
                    return os;
               }
               public:
                    StudentRecord(const string& name) : name(name) {}

                    //copy
                    StudentRecord(const StudentRecord& s) : name(s.name), grades(s.grades) {}

                    void addGrade(const int& grade, const int& week){
                         grades[week - 1] = grade;
                    }

                    const string& getName() const{ return name; }
               private:
                    string name;
                    vector<int> grades = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
          };

          string name;
          TimeSlot time;
          vector<StudentRecord*> students;
};



class LabWorker{
     friend ostream& operator<<(ostream& os, const LabWorker& lw){
          if (lw.s == nullptr){
               cout << lw.name << " does not have a section" << endl;
          }
          else{
               cout << lw.name << " has " << *lw.s;
          }
          return os;
     }
     public:
          LabWorker(const string& n) : name(n), s(nullptr){}

          void addSection(Section& section){
               s = &section;
          }

          void addGrade(const string& name, int grade, int week){
               s->addGrade(name, grade, week);
          }

     private:
          string name;
          Section* s;
};


// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
         << "then make sure the following call works:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main
