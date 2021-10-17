/*
  testNobleWarrior.cpp
  Andre Hu
  Medieval program for aggressive nobles
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;



class Warrior{
     friend ostream& operator<<(ostream&os, const Warrior& warrior);
     public:
          Warrior(string name, int strength): name(name), strength(strength), hired(false) {}

          const string getName() const{ return name; }

          double getStrength() const{ return strength; }

          const bool isHired() const{ return hired; }

          void changeStatus(){
               if (hired){
                    hired = false;
               }
               else{
                    hired = true;
               }
          }

          void loseStrength(double h){
               strength -= h;
          }

     private:
          string name;
          double strength;
          bool hired;
};

ostream& operator<<(ostream& os, const Warrior& w){
     cout << w.name << ": " << w.strength;
     return os;
}


class Noble{
     friend ostream& operator<<(ostream&os, const Noble& noble);
     public:
          Noble(string name) : name(name), alive(true) {}

          bool hire(Warrior& w){
               if (alive){
                    if(w.isHired()){ //if already hired
                         return false;
                    }
                    else{
                         w.changeStatus();
                         warriors.emplace_back(&w);
                    }
                    return true;
               }     
               return false;                    
          }

          //if warrior is not found does nothing
          const bool fire(Warrior& w){               
               if(alive){
                    for (size_t i = 0; i < warriors.size(); ++i){
                         if (warriors[i] == &w){
                              cout << "You don't work for me anymore " << w.getName() << "! -- " << name << "." << endl;  
                              w.changeStatus();

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
               }
               return false;
          }


          void battle(Noble& n){
               cout << name << " battles " << n.name << endl;
               
               //calculating strength of armies
               double strength = 0;
               double strength_other = 0;
               double ratio = 0;

               for (size_t i = 0; i < warriors.size(); ++i){
                    strength += warriors[i]->getStrength();
               }
               for (size_t i = 0; i < n.warriors.size(); ++i){
                    strength_other += n.warriors[i]->getStrength();
               }

               //battle!
               if (alive == false && n.alive == false){
                    cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
               }
               else if(alive == false){
                    cout << "He's dead, " << n.name << endl;
               }
               else if(n.alive == false){
                    cout << "He's dead, " << name << endl;
               }

               //modify noble status as well as strength of warriors
               else if (strength == strength_other){
                    cout << "Mutual Annihalation: " << name << " and " << n.name << " die at each other's hands" << endl;
                    alive = false;
                    n.alive = false;

                    for(size_t i = 0; i < warriors.size(); ++i){
                         warriors[i]->loseStrength(warriors[i]->getStrength());
                    }
                    for(size_t i = 0; i < n.warriors.size(); ++i){
                         n.warriors[i]->loseStrength(n.warriors[i]->getStrength());
                    }
               }
               //calculates ratio for amount of health lost
               else if (strength > strength_other){
                    cout << name << " defeats " << n.name << endl;
                    n.alive = false;
                    ratio = strength_other / strength;

                    for(size_t i = 0; i < warriors.size(); ++i){
                         warriors[i]->loseStrength(warriors[i]->getStrength() * ratio);
                    }
                    for(size_t i = 0; i < n.warriors.size(); ++i){
                         n.warriors[i]->loseStrength(n.warriors[i]->getStrength());
                    }
               }
               else if (strength < strength_other){
                    cout << n.name << " defeats " << name << endl;
                    alive = false;
                    ratio = strength / strength_other;

                    for(size_t i = 0; i < warriors.size(); ++i){
                         warriors[i]->loseStrength(warriors[i]->getStrength());
                    }
                    for(size_t i = 0; i < n.warriors.size(); ++i){
                         n.warriors[i]->loseStrength(n.warriors[i]->getStrength() * ratio);
                    }
               }
          }

     private:          
          string name;
          vector<Warrior*> warriors;
          bool alive;
};

ostream& operator<<(ostream& os, const Noble& n){
     cout << n.name << " has an army of " << n.warriors.size() << endl;
     for (size_t i = 0; i < n.warriors.size(); ++i){
          cout << "\t" << *n.warriors[i] << endl;
     }
     return os;
}


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

    cout << "==========\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

    art.fire(cheetah);
    cout << art << endl;


    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

     return 0;
}
