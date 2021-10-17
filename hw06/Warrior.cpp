#include <iostream>
#include <vector>
#include <string>
#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft{
    class Noble;

    Warrior::Warrior(const string& n, size_t s) : name(n), strength(s), n_man(nullptr) {}


    ostream& operator<<(ostream& os, const Warrior& w){
            cout << w.name << ": " << w.strength;
            return os;
    }

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
}