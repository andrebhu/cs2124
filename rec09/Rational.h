#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>
#include <string>

namespace CS2124{


    class Rational{
        friend std::ostream& operator<<(std::ostream& os, const Rational& num);
        friend std::istream& operator>>(std::istream& is, Rational& num);

        friend bool operator==(const Rational& lhs, const Rational& rhs);
        friend bool operator<(const Rational& lhs, const Rational& rhs);

        public:
            Rational(int a = 0, int b = 1);
            Rational& operator+=(const Rational& rhs);
            Rational& operator++();
            Rational operator++(int x);
            explicit operator bool() const;
        
        private:
            int a;
            int b;


            int greatestCommonDivisor(int x, int y) {
                while (y != 0) {
                    int temp = x % y;
                    x = y;
                    y = temp;
                }
                return x;
            }
            
            void normalize(){
                int div = greatestCommonDivisor(a, b);
                a /= div;
                b /= div;

            if (b < 0){
                a = -a;
                b = -b;
            }
        }
    };


    Rational operator+(const Rational& lhs, const Rational& rhs);
    bool operator!=(const Rational& lhs, const Rational& rhs);
    Rational& operator--(Rational& rhs);
    Rational operator--(Rational& rhs, int x);
    std::ostream& operator<<(std::ostream& os, const Rational& r);
    std::istream& operator>>(std::istream& is, Rational& r);
    bool operator==(const Rational& lhs, const Rational& rhs);
    bool operator<=(const Rational& lhs, const Rational& rhs);
    bool operator>=(const Rational& lhs, const Rational& rhs);
    bool operator>(const Rational& lhs, const Rational& rhs);
}

#endif