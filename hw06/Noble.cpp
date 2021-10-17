#include <iostream>
#include <vector>
#include <string>
#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft{
    class Warrior;

    Noble::Noble(const string& n) : name(n) {}

    ostream& operator<<(ostream& os, const Noble& n){
        cout << n.name << " has an army of " << n.warriors.size() << endl;
            for(size_t i = 0; i < n.warriors.size(); ++i){
                cout << "\t" << *n.warriors[i] << endl;
            }
        return os;
    }


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
}