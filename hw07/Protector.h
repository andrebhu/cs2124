#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef PROTECTOR_H
#define PROTECTOR_H

namespace WarriorCraft{
    class Noble;

    class Protector{
        public:
            Protector(const std::string& name, double strength);
            bool isHired() const;
            void setNoble(Noble* n);
            Noble* getNoble();
            virtual void setStrength(double strength);
            double getStrength() const;
            virtual void yell() const = 0;

        protected:
            std::string name;
            double strength;
            Noble* noble;
    };

    class Wizard : public Protector {
        public:
            Wizard(const std::string& name, double strength);
            void yell() const;
    };

    class Warrior : public Protector {
        public:
            Warrior(const std::string& name, double strength);
            virtual void yell() const;
    };

    class Archer : public Warrior{
        public:
            Archer(const std::string& name, double strength);
            void yell() const;
    };

    class Swordsman : public Warrior{
        public:
            Swordsman(const std::string& name, double strength);
            void yell() const;
    };
}

#endif