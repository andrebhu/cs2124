#include <iostream>
#include <vector>
#include <string>

#ifndef NOBLE_H
#define NOBLE_H

namespace WarriorCraft{
    class Warrior;
    
    class Noble{
        friend std::ostream& operator<<(std::ostream& os, const Noble& n);
        public:
            Noble(const std::string& n);
            const std::string& getName() const;
            double getStrength() const;
            bool getStatus() const;
            void die();
            bool hire(Warrior& w);
            bool fire(Warrior& w);
            bool battle(Noble& n);
            void loseStrength(double ratio);
        private:
            std::string name;
            std::vector<Warrior*> warriors;
            bool status = true;
    };
}

#endif