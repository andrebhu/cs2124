#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <vector>
#include <string>
#include <iostream>

class Polynomial{
    struct Node{
        Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
        int data;
        Node* next;
    };

    friend std::ostream& operator<<(std::ostream& os, const Polynomial& rhs);

    public:
        Polynomial();
        Polynomial(const std::vector<int>& coefficients);
        ~Polynomial();
        Polynomial(const Polynomial& rhs);
        Polynomial& operator=(const Polynomial& rhs);
        Polynomial& operator+=(const Polynomial& rhs);
        bool operator==(const Polynomial& rhs) const;
        int evaluate(int x) const;
        void zeros_cleanup();
    private:
        size_t degree = 0;
        Node* head = nullptr;
};

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
bool operator!=(Polynomial lhs, Polynomial rhs);

#endif