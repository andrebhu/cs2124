/*
Andre Hu
2/8/2021
hw02

Text-based Fighting simulator between warriors
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Warrior {
        string name;
        size_t strength;
};

//function prototypes
void status(const vector<Warrior>&);
void battle(Warrior&, Warrior&, vector<Warrior>&);
void createWarrior(string, size_t, vector<Warrior>&);
size_t getWarriorIndex(string, vector<Warrior>&);

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
            size_t strength;

            input >> name;
            input >> strength;
            createWarrior(name, strength, warriors);
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
    return 0;
}

//prints current names and strength of warriors
void status(const vector<Warrior>& warriors){
    cout << "There are: " << warriors.size() << " warriors" << endl;
    for(size_t i = 0; i < warriors.size(); ++i){
        cout << "Warrior: " << warriors[i].name;
        cout << ", strength: " << warriors[i].strength << endl;
    }
}

//Battles warriors based off strength
void battle(Warrior& warrior_one, Warrior& warrior_two, vector<Warrior>& warriors){

    cout << warrior_one.name << " battles " << warrior_two.name << endl;

    //Compare strengths
    //Check dead warriors
    if (warrior_one.strength == 0 && warrior_two.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
    else if (warrior_one.strength == 0){
        cout << "He's dead, " << warrior_two.name << endl;
    }
    else if (warrior_two.strength == 0){
        cout << "He's dead, " << warrior_one.name << endl;
    }
    //Check alive warriors
    else if (warrior_one.strength == warrior_two.strength){
        warrior_one.strength = 0;
        warrior_two.strength = 0;
        cout << "Mutual Annihilation: ";
        cout << warrior_one.name << " and " << warrior_two.name;
        cout << " die at each other's hands" << endl;
    }
    else if (warrior_one.strength > warrior_two.strength){
        warrior_one.strength -= warrior_two.strength;
        warrior_two.strength = 0;
        cout << warrior_one.name << " defeats " << warrior_two.name << endl;
    }
    else if (warrior_one.strength < warrior_two.strength){
        warrior_two.strength -= warrior_one.strength;
        warrior_one.strength = 0;
        cout << warrior_two.name << " defeats " << warrior_one.name << endl;
    }
}

//creates new Warrior with given variables and vector
void createWarrior(string name, size_t strength, vector<Warrior>& warriors){
    Warrior new_warrior{name, strength};
    warriors.push_back(new_warrior);
}

//retrieves index of warrior from vector warriors
size_t getWarriorIndex(string name, vector<Warrior>& warriors){
     for(size_t i = 0; i < warriors.size(); ++i){
        if (warriors[i].name == name){
            return i;
        }
    }
    return warriors.size();
}