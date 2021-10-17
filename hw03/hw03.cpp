/*
Andre Hu
2/26/2021
hw03

Text-based Fighting simulator between warriors with classes
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& w){
        cout << "Warrior: " << w.name << ", weapon: " << w.weapon;
        return os;
    }

    public:
        Warrior(const string& name, const string& weapon_name, int weapon_strength) : name(name), weapon(weapon_name, weapon_strength){}

        const string& getName() const{
            return name;
        }

        const int& getStrength() const{
            return weapon.getStrength();
        }

        void loseStrength(const int& amount){
            weapon.loseStrength(amount);
        }
    private:   
        class Weapon{     
            friend ostream& operator<<(ostream& os, const Weapon& w){
                cout << w.name << " " << w.strength;
                return os;
            }

                public:
                    Weapon(const string& name, int strength) : name(name), strength(strength) {};

                    const int& getStrength() const{
                        return strength;
                    }

                    void loseStrength(const int& amount){
                        strength -= amount;
                    }
   
                private:
                    string name;
                    int strength;
            };
        
        string name;
        Weapon weapon;
};

//function prototypes
void status(const vector<Warrior>& warriors);
size_t getWarriorIndex(const string&, const vector<Warrior>&);
void battle(Warrior&, Warrior&, vector<Warrior>&);

int main(){    
    //reading input file
    ifstream input("warriors.txt");
    if (!input){
        cerr << "Failed to open warriors.txt";
        exit(1);
    }

    vector<Warrior> warriors;
    string command;
    while(input >> command){
        if (command == "Warrior"){
            string name;
            string w_name;
            size_t strength;

            input >> name >> w_name >> strength;
            warriors.emplace_back(Warrior(name, w_name, strength));
        }
        else if (command == "Battle"){


            string warrior_name_one;
            string warrior_name_two;
            //obtain names
            input >> warrior_name_one;
            input >> warrior_name_two;
            //in order to directly reference the warriors without copying
            size_t warrior_one = getWarriorIndex(warrior_name_one, warriors);
            size_t warrior_two = getWarriorIndex(warrior_name_two, warriors); 

            battle(warriors[warrior_one], warriors[warrior_two], warriors);

        }
        else if (command == "Status"){
            status(warriors);
        }
    }   
    
    input.close();
    return 0;
}

//prints current names and strength of warriors
void status(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); ++i){
        cout << warriors[i] << endl;
    }
}

//Battles warriors based off strength
void battle(Warrior& warrior_one, Warrior& warrior_two, vector<Warrior>& warriors){

    cout << warrior_one.getName() << " battles " << warrior_two.getName() << endl;

    int health_one = warrior_one.getStrength();
    int health_two = warrior_two.getStrength();
    //Compare strengths
    //Check dead warriors
    if (health_one == 0 && health_two == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (health_one == 0){
        cout << "He's dead, " << warrior_two.getName() << endl;
    }
    else if (health_two == 0){
        cout << "He's dead, " << warrior_one.getName() << endl;
    }
    //Check alive warriors
    else if (health_one == health_two){
        warrior_one.loseStrength(health_one);
        warrior_two.loseStrength(health_two);
        cout << "Mutual Annihilation: ";
        cout << warrior_one.getName() << " and " << warrior_two.getName();
        cout << " die at each other's hands" << endl;
    }
    else if (health_one > health_two){
        warrior_one.loseStrength(health_two);
        warrior_two.loseStrength(health_two);
        cout << warrior_one.getName() << " defeats " << warrior_two.getName() << endl;
    }
    else if (health_one < health_two){
        warrior_two.loseStrength(health_one);
        warrior_one.loseStrength(health_one);
        cout << warrior_two.getName() << " defeats " << warrior_one.getName() << endl;
    }
}

//retrieves index of warrior from vector warriors
size_t getWarriorIndex(const string& name, const vector<Warrior>& warriors){
     for(size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i].getName() == name){
            return i;
        }
    }
    return warriors.size();
}
