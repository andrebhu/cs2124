/*
  hw05.cpp
  Andre Hu
  Medieval program for aggressive nobles
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Warrior{
     friend ostream& operator<<(ostream& os, const Warrior& w){
          cout << w.name << ": " << w.strength;
          return os;
     }

     public:
          Warrior(const string& n, size_t s) : name(n), strength(s) {}

          const string& getName() const { return name; }

          void changeStatus() { 
               if(hired){ hired = false; }
               else{ hired = true; }
          }
          bool getStatus() { return hired;}

          double getStrength() { return strength; }

          void loseStrength(double ratio){
               strength = strength * (1 - ratio);
          }

     private:
          string name;
          double strength;
          bool hired = false;
};

class Noble{
     friend ostream& operator<<(ostream& os, const Noble& n){
          cout << n.name << " has an army of " << n.warriors.size() << endl;
          for(size_t i = 0; i < n.warriors.size(); ++i){
               cout << "\t" << *n.warriors[i] << endl;
          }
          return os;
     }
     public:
          Noble(const string& n) : name(n) {}

          const string& getName() const{ return name; }

          double getStrength() const{
               double s = 0;
               for(size_t i = 0; i < warriors.size(); ++i){
                    s += warriors[i]->getStrength();
               }
               return s;
          }

          bool getStatus() const { return status; }

          //rip
          void die() { status = false; }

          void hire_warrior(Warrior*& w){
               if(w->getStatus()){ 
                    cout << "Error: noble " << name << " is attempting to hire warrior " << w->getName() << " who is already employed." << endl;
               }
               else{
                    w->changeStatus();
                    warriors.push_back(w);
               }               
          }

          bool fire_warrior(Warrior*& w){
               for(size_t i = 0; i < warriors.size(); ++i){
                    if (warriors[i] == w){
                         cout << "You don't work for me anymore " << w->getName() << "! -- " << name << "." << endl;  
                         w->changeStatus();

                         //remove warrior from vector
                         if (i == warriors.size() - 1){
                              warriors.pop_back();
                         }                        
                         else{
                              for (size_t j = i; j < warriors.size(); ++j){
                                   warriors[j] = warriors[j + 1];
                              }
                              warriors.pop_back();
                         } 
                         return true;
                    }
               }
               return false;
          }

          void loseStrength(double ratio){
               for(Warrior*& w : warriors){
                    w->loseStrength(ratio);
               }
          }

     private:
          string name;
          vector<Warrior*> warriors;
          bool status = true;
};


//function prototypes
void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors);
void open_file(ifstream& input);
bool newNoble(const string& name, vector<Noble*>& nobles);
bool newWarrior(const string& name, double strength, vector<Warrior*>& warriors);
bool hire(const string& n_name, const string& w_name, vector<Noble*>& n, vector<Warrior*>& w);
bool fire(const string& n_name, const string& w_name, vector<Noble*>& n, vector<Warrior*>& w);
bool battle(const string& name1, const string& name2, vector<Noble*>& n, vector<Warrior*>& w);
void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors);

int main(){
     vector<Noble*> nobles;
     vector<Warrior*> warriors;
     string command;
     string name1;
     string name2;
     double strength;

     ifstream input;
     open_file(input);

     while(input >> command){
          if(command == "Noble"){
               input >> name1;
               newNoble(name1, nobles);
          }
          else if(command == "Warrior"){
               input >> name1 >> strength;
               newWarrior(name1, strength, warriors);
          }
          else if(command == "Hire"){
               input >> name1 >> name2;               
               hire(name1, name2, nobles, warriors);
          }
          else if(command == "Fire"){
               input >> name1 >> name2;
               fire(name1, name2, nobles, warriors);
          }
          else if(command == "Battle"){
               input >> name1 >> name2;
               battle(name1, name2, nobles, warriors);
          }
          else if(command == "Status"){
               status(nobles, warriors);
          }
          else if(command == "Clear"){
               clear(nobles, warriors);
          }
          else{
               cout << "Invalid command!" << endl;
               exit(1);
          }
     }

     input.close();
     return 0;
}

void status(const vector<Noble*>& nobles, const vector<Warrior*>& warriors){

     //status for nobles
     cout << "Status" << endl << "======" << endl << "Nobles:" << endl;

     if (nobles.size() == 0){
          cout << "NONE" << endl;
     }
     else{
          for(size_t i = 0; i < nobles.size(); ++i){
               cout << *nobles[i];
          }
     }
     
     //status for warriors
     vector<Warrior*> unemployed;
     for(size_t i = 0; i < warriors.size(); ++i){
          if (warriors[i]->getStatus() == false){
               unemployed.push_back(warriors[i]);
          }
     }

     cout << "Unemployed Warriors:" << endl;
     if(unemployed.size() == 0){
          cout << "NONE" << endl;
     }
     else{
          for(size_t i = 0; i < unemployed.size(); ++i){
               cout << *unemployed[i] << endl;
          }
     }     
}

void open_file(ifstream& input){
     input.open("nobleWarriors-20S.txt");
     if (!input){
        cerr << "Failed to open file!";
        exit(1);
    }
}

bool newNoble(const string& name, vector<Noble*>& nobles){
     for(Noble* n: nobles){
          if (n->getName() == name){
               cout << "Noble " << name << " already exists!" << endl;
               return false;
          }
     }
     nobles.push_back(new Noble(name));
     return true;
}

bool newWarrior(const string& name, double strength, vector<Warrior*>& warriors){
     for(Warrior* w: warriors){
          if(w->getName() == name){
               cout << "Warrior " << name << " already exists!" << endl;
               return false;
          }
     }
     warriors.push_back(new Warrior(name, strength));

     return true;
}

bool hire(const string& n_name, const string& w_name, vector<Noble*>& n, vector<Warrior*>& w){
     for(size_t i = 0; i < n.size(); ++i){
          if (n[i]->getName() == n_name){
               for(size_t j = 0; j < w.size(); ++j){
                    if(w[j]->getName() == w_name){
                         n[i]->hire_warrior(w[j]);
                         return true;
                    }
               }
          }
     }
     cout << "Error: noble " << n_name << " is attempting to hire an unknown warrior " << w_name << endl;
     return false;
}

bool fire(const string& n_name, const string& w_name, vector<Noble*>& n, vector<Warrior*>& w){
     for(size_t i = 0; i < n.size(); ++i){
          if (n[i]->getName() == n_name){
               for(size_t j = 0; j < w.size(); ++j){
                    if(w[j]->getName() == w_name){
                        n[i]->fire_warrior(w[j]);
                        return true;
                    }
               }
          }
     }  
     cout << "Fire: Invalid noble or warrior!" << endl;
     return false;  
}

bool battle(const string& name1, const string& name2, vector<Noble*>& n, vector<Warrior*>& w){
     if(name1 == name2){
          cout << "Nobles can't battle each other!" << endl;
          return false;
     }

     Noble* n1 = nullptr;
     Noble* n2 = nullptr;
     
     for(Noble*& noble : n){
          if (noble->getName() == name1){
               n1 = noble;
          }
          if (noble->getName() == name2){
               n2 = noble;
          }
     }

     if (n1 == nullptr || n2 == nullptr){
          cout << "Noble does not exist!" << endl;
          return false;
     }

     //battle!
     double s1 = n1->getStrength();
     double s2 = n2->getStrength();
     cout << name1 << " battles " << name2 << endl;

     if (n1->getStatus() == false && n2->getStatus() == false){
          cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
          return true;
     }
     else if(n1->getStatus() == false){
          cout << "He's dead, " << n2->getName() << endl;
          return true;
     }
     else if(n2->getStatus() == false){
          cout << "He's dead, " << n1->getName() << endl;
          return true;
     }

     else if(s1 == s2){
          cout << "Mutual Annihalation: " << n1->getName() << " and " << n2->getName() << " die at each other's hands" << endl;
          n1->die();
          n2->die();
          n1->loseStrength(1);
          n2->loseStrength(1);
          return true;
     }
     else if(s1 > s2){
          cout << n1->getName() << " defeats " << n2->getName() << endl;
          n2->die();
          n2->loseStrength(1);

          double ratio = s2 / s1;
          n1->loseStrength(ratio);
          return true;
     }
     else if(s1 < s2){
          cout << n2->getName() << " defeats " << n1->getName() << endl;
          n1->die();
          n1->loseStrength(1);

          double ratio = s1 / s2;
          n2->loseStrength(ratio);
          return true;
     }
     return false;
}

void clear(vector<Noble*>& nobles, vector<Warrior*>& warriors){
     for(Noble*& n : nobles){
          delete n;
     }
     for(Warrior*& w : warriors){
          delete w;
     }
     nobles.clear();
     warriors.clear();
}