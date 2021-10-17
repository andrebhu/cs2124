#include "Protector.h"
#include "Noble.h"

namespace WarriorCraft{
    class Noble;

    Protector::Protector(const std::string& name, double strength) : name(name), strength(strength), noble(nullptr) {}
    bool Protector::isHired() const{
        if(noble == nullptr){
            return false;
        }
        return true;
    }
    
    void Protector::setNoble(Noble* n){ noble = n; }
    Noble* Protector::getNoble() { return noble; }
    void Protector::setStrength(double s){
        strength = s;
    }
    double Protector::getStrength() const { return strength; }

////////////////////////////////////////////

    Wizard::Wizard(const std::string& name, double strength) : Protector(name, strength) {}
    void Wizard::yell() const { std::cout << "POOF!" << std::endl; }

////////////////////////////////////////////

    Warrior::Warrior(const std::string& name, double strength) : Protector(name, strength) {}
    void Warrior::yell() const { std::cout << "shouldn't be called" << std::endl; }

////////////////////////////////////////////

    Archer::Archer(const std::string& name, double strength) : Warrior(name, strength) {}
    
    void Archer::yell() const { 
        std::cout << "TWANG! " << name << " says: Take that in the name of my lord, " 
        << noble->getName() << std::endl; 
    }

////////////////////////////////////////////

    Swordsman::Swordsman(const std::string& name, double strength) : Warrior(name, strength) {}
    void Swordsman::yell() const {
        std::cout << "CLANG! "
        << name << " says: Take that in the name of my lord, "
        << noble->getName() << std::endl;
    }
}