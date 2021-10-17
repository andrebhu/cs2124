#include "Noble.h"
#include "Protector.h"

namespace WarriorCraft{
    Noble::Noble(const std::string& name, double strength = 0) : name(name), strength(strength), status(true) {}

    std::string Noble::getName() const { return name; };

    void Noble::battle(Noble& n){
        std::cout << name << " battles " << n.name << std::endl;
        yell();
        n.yell();

        //check statuses
        if(status == false && n.status == false){
            std::cout << "Oh, NO! They're both dead! Yuck!\n" << std::endl;
            return;
        }
        else if(status == false){
            std::cout << "He's dead, " << n.name << std::endl;
            return;
        }
        else if(n.status == false){
            std::cout << "He's dead, " << name << std::endl;
            return;
        }

        //fight
        if(strength == n.strength){
            this->loseStrength(n.strength);
            n.loseStrength(strength);
            status = false;
            n.status = false;
            std::cout << "Mutual Annihilation: " << name << " and " << n.name << " die at each other's hands" << std::endl;
        }
        else if(strength > n.strength){
            this->loseStrength(n.strength);
            n.loseStrength(strength);
            n.status = false;
            std::cout << name << " defeats " << n.name << std::endl;
        }
        else if(strength < n.strength){
            this->loseStrength(n.strength);
            n.loseStrength(strength);
            status = false;
            std::cout << n.name << " defeats " << name << std::endl;
        }
    }

////////////////////////////////////////////

    PersonWithStrengthToFight::PersonWithStrengthToFight(const std::string& name, double strength) : Noble(name, strength) {}
    void PersonWithStrengthToFight::loseStrength(double s){ //raw strength
        strength -= s;
        if (strength < 0){
            strength = 0;
            status = false;
        }
    }
    void PersonWithStrengthToFight::yell() const{
        if(status){
            std::cout << "Ugh!" << std::endl;
        }
    }

////////////////////////////////////////////

    Lord::Lord(const std::string& name) : Noble(name) {}
    void Lord::loseStrength(double s){ //raw strength
        if(s == strength){
            strength = 0;
            status = false;

            for(Protector* p : army){
                p->setStrength(0);
            }
        }
        //Lord wins
        else if(s < strength){
            double damage = s / strength;
            strength = 0;

            for(Protector* p : army){
                double new_strength = p->getStrength() * damage;
                p->setStrength(new_strength);
                strength += new_strength;
            }
        }
        //Lord loses
        else if(s > strength){
            strength = 0;
            status = false;
            for(Protector* p : army){
                p->setStrength(0);
            }
        }
    }

    void Lord::hires(Protector& p){
        if(status){
            if(p.isHired() == false){
                p.setNoble(this);
                army.push_back(&p);
                strength += p.getStrength();                
            }
        }
    }

    void Lord::fire(Protector& p){
        if(status){
            if(p.isHired() && p.getNoble() == this){
                strength -= p.getStrength();
                for(size_t i = 0; i < army.size(); ++i){
                    if(army[i] == &p){
                        for(size_t j = i; j < army.size(); ++j){
                            army[j] = army[j + 1];
                        }
                    }
                }
            }
        }
    }

    void Lord::yell() const {
        if(status){
            for(Protector* p : army){
                p->yell();
            }        
        }
    }
}
