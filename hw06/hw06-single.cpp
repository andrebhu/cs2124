/*
hw06 single file solution
Andre Hu
war never ends
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Noble;

class Warrior{
     friend ostream& operator<<(ostream& os, const Warrior& w);
     public:
          Warrior(const string& n, size_t s);
          const string& getName() const;
          bool getStatus() const;
          bool isHired() const;
          double getStrength() const;
          void changeStatus(Noble& n);
          void loseStrength(double ratio);
          bool runaway();

     private:
          string name;
          double strength;
          Noble* n_man = nullptr;
};

class Noble{
     friend ostream& operator<<(ostream& os, const Noble& n);
     public:
          Noble(const string& n);
          const string& getName() const;
          double getStrength() const;
          bool getStatus() const;
          void die();
          bool hire(Warrior& w);
          bool fire(Warrior& w);
          bool battle(Noble& n);
          void loseStrength(double ratio);
     private:
          string name;
          vector<Warrior*> warriors;
          bool status = true;
};



int main() {
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	cout << "================ Initial Status ===============" << endl;
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie;
	cout << "===============================================\n\n";

	cheetah.runaway();
	cout << art << endl;

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);

	cout << "\n================ Final Status ===============" << endl;
	cout << jim << endl;
	cout << lance << endl;
	cout << art << endl;
	cout << linus << endl;
	cout << billie << endl;

	// Tarzan should be unemployed
	cout << "Tarzan's Hire Status: " << boolalpha << cheetah.isHired() << endl;
	cout << "===============================================\n\n";
}


//output operators
ostream& operator<<(ostream& os, const Warrior& w){
          cout << w.name << ": " << w.strength;
          return os;
}

ostream& operator<<(ostream& os, const Noble& n){
    cout << n.name << " has an army of " << n.warriors.size() << endl;
        for(size_t i = 0; i < n.warriors.size(); ++i){
            cout << "\t" << *n.warriors[i] << endl;
        }
    return os;
}


class Noble;

//warrior methods
Warrior::Warrior(const string& n, size_t s) : name(n), strength(s), n_man(nullptr) {}
const string& Warrior::getName() const { return name; }

//already have getStatus but don't want to break code
//just going to add isHired that does the same thing
bool Warrior::getStatus() const { 
    if(this->n_man) {
        return true;
    }
    return false;
}
bool Warrior::isHired() const {
    if(this->n_man){
        return true;
    }
    return false;
}

double Warrior::getStrength() const { return strength; }
void Warrior::changeStatus(Noble& n){
    if(n_man == nullptr){
        n_man = &n;
    }
    else{
        n_man = nullptr;
    }
}
void Warrior::loseStrength(double ratio){
    this->strength = strength * (1 - ratio);
}

bool Warrior::runaway(){
    if (n_man)
    {
        cout << name << " flees in terror, abandoning his lord, " 
        << n_man->getName() << endl;
        n_man->fire(*this);
        n_man = nullptr;
        return true;
    }    
    return false;
}

//noble methods
Noble::Noble(const string& n) : name(n) {}
const string& Noble::getName() const { return name; }
bool Noble::getStatus() const{ return status; }
double Noble::getStrength() const{
    double s = 0;
    for(size_t i = 0; i < warriors.size(); ++i){
        s += warriors[i]->getStrength();
    }
    return s;
}
void Noble::die(){ status = false; }
bool Noble::hire(Warrior& w){
    if(w.getStatus()){
        cout << "Error: noble " << name << " is attempting to hire warrior " 
        << w.getName() << " who is already employed." << endl;
        return false;
    }
    else{
        w.changeStatus(*this);
        this->warriors.push_back(&w);
        return true;
    }
}
bool Noble::fire(Warrior& w){
    for(size_t i = 0; i < warriors.size(); ++i){
        if(warriors[i] == &w){
            cout << "You don't work for me anymore " << 
            w.getName() << "! -- " << this->name << "." << endl;  

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
     cout << "Fire: Invalid noble or warrior!" << endl;
     return false;  
}

void Noble::loseStrength(double ratio){
    for(Warrior*& w : warriors){
        w->loseStrength(ratio);
    }
}


//alternating between "this" pointer and referenced opponent, had errors with
//lvalue and const so just kept it as is
bool Noble::battle(Noble& n){
     if(this == &n){
          cout << "Nobles can't battle each other!" << endl;
          return false;
     }

     //battle!
     double s1 = this->getStrength();
     double s2 = n.getStrength();
     cout << this->name << " battles " << n.getName() << endl;

     if (this->getStatus() == false && n.getStatus() == false){
          cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
          return true;
     }
     else if(this->getStatus() == false){
          cout << "He's dead, " << n.getName() << endl;
          return true;
     }
     else if(n.getStatus() == false){
          cout << "He's dead, " << this->getName() << endl;
          return true;
     }

     else if(s1 == s2){
          cout << "Mutual Annihalation: " << this->getName() << " and " << n.getName() << " die at each other's hands" << endl;
          this->die();
          n.die();
          this->loseStrength(1);
          n.loseStrength(1);
          return true;
     }
     else if(s1 > s2){
          cout << this->getName() << " defeats " << n.getName() << endl;
          n.die();
          n.loseStrength(1);

          double ratio = s2 / s1;
          this->loseStrength(ratio);
          return true;
     }
     else if(s1 < s2){
          cout << n.getName() << " defeats " << this->getName() << endl;
          this->die();
          this->loseStrength(1);

          double ratio = s1 / s2;
          n.loseStrength(ratio);
          return true;
     }
     return false;
}
