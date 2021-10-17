#include <iostream>
#include <vector>
#include <string>

#ifndef WARRIOR_H
#define WARRIOR_H

namespace WarriorCraft{
    class Noble;

    class Warrior{
        friend std::ostream& operator<<(std::ostream& os, const Warrior& w);
        public:
            Warrior(const std::string& n, size_t s);
            const std::string& getName() const;
            bool getStatus() const;
            bool isHired() const;
            double getStrength() const;
            void changeStatus(Noble& n);
            void loseStrength(double ratio);
            bool runaway();

        private:
            std::string name;
            double strength;
            Noble* n_man = nullptr;
    };
}

#endif