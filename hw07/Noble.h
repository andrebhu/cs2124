#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifndef NOBLE_H
#define NOBLE_H

namespace WarriorCraft{
    class Protector;

    class Noble{
        public:
            Noble(const std::string& s, double strength);
            std::string getName() const;
            virtual void loseStrength(double strength) = 0;
            virtual void battle(Noble& rhs);
            virtual void yell() const = 0;
        protected:
            std::string name;
            double strength;
            bool status;

    };

    class PersonWithStrengthToFight: public Noble{
        public:
            PersonWithStrengthToFight(const std::string& name, double strength);
            virtual void loseStrength(double strength);
            void yell() const;
    };

    class Lord : public Noble{
        public:
            Lord(const std::string& name);
            virtual void loseStrength(double strength);
            void hires(Protector& rhs);
            void fire(Protector& rhs);
            void yell() const;
            
        private:
            std::vector<Protector*> army;
    };
}


#endif