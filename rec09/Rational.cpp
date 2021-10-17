#include "Rational.h"
#include <string>
#include <iostream>

using namespace std;

namespace CS2124{

    ostream& operator<<(ostream& os, const Rational& rhs){
        os << rhs.a << "/" << rhs.b;
        return os;
    }

    istream& operator>>(istream& is, Rational& rhs){
        char c;
        is >> rhs.a >> c >> rhs.b;
        rhs.normalize();
        return is;
    }


    Rational::Rational(int a, int b) : a(a), b(b) {
        normalize();
    }


        //+=
    Rational& Rational::operator+=(const Rational& r){
        if(b != r.b){
            a = (a * r.b) + (r.a * b);
            b = b * r.b;
        }
        else{
            a += r.a;
        }
        normalize();
        return *this;
    }

    //++ pre
    Rational& Rational::operator++(){
        a += b;
        normalize();
        return *this;
    }

    //++ post
    Rational Rational::operator++(int x){
        Rational r = *this;
        a += b;
        return r;
    }

    Rational::operator bool() const{
        return a != 0;
    }

    Rational operator+(const Rational& lhs, const Rational& rhs){
        Rational l = lhs;
        l += rhs;
        return l;
    }

    bool operator==(const Rational& lhs, const Rational& rhs){
        return (lhs.a == rhs.a && lhs.b == rhs.b);
    }

    bool operator<(const Rational& lhs, const Rational& rhs){
        int l = lhs.a * rhs.b;
        int r = lhs.b * rhs.a;
        return (l < r);
    }


    //-- pre
    Rational& operator--(Rational& lhs){
        lhs += -1;
        return lhs;
    }

    //-- post
    Rational operator--(Rational& lhs, int x){
        Rational r = lhs;
        lhs += -1;
        return lhs;
    }

    bool operator!=(const Rational& lhs, const Rational& rhs){
        return !(lhs==rhs);
    }

    bool operator<=(const Rational& lhs, const Rational& rhs){
        return (lhs < rhs || lhs == rhs);
    }

    bool operator>(const Rational& lhs, const Rational& rhs){
        return !(lhs <= rhs);
    }

    bool operator>=(const Rational& lhs, const Rational& rhs){
        return (lhs > rhs || lhs == rhs);
    }


}