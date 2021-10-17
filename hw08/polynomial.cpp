#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;



ostream& operator<<(ostream& os, const Polynomial& rhs){
    const Polynomial::Node* i = rhs.head;
    int count = 0;
    string output = "";

    //zero polynomial
    if(i == nullptr){
        os << "0";
        return os;
    }

    while(count <= rhs.degree && i){
        if(count == 0){
            output = to_string(i->data);
        }
        else if(count == 1){
            if(i->data != 1){
                output = to_string(i->data) + "x + " + output;
            }
            else{
                output = "x + " + output;
            }
        }
        else if(i->data != 0){
            if(i->data != 1){
                output = to_string(i->data) + "x^" + to_string(count) + " + " + output;
            }
            else{
                output = "x^" + to_string(count) + " + " + output;
            }
        }   

        count += 1;      
        i = i->next;
    }
    os << output;
    return os;
}
//constructors
Polynomial::Polynomial() {}

Polynomial::Polynomial(const vector<int>& coefficients){
    degree = coefficients.size() - 1;

    head = new Node(coefficients[coefficients.size() - 1]);
    Node* iter = head;

    for(int i = degree - 1; i >= 0; --i){
        iter->next = new Node(coefficients[i]);
        iter = iter->next;
        
    }
    zeros_cleanup();
}


//destructor
Polynomial::~Polynomial(){
    degree = 0;
    Node* iter = head;
    head = nullptr;
    while(iter){
        Node* n = iter->next;
        delete iter;
        iter = n;
    }
}


//copy constructor
Polynomial::Polynomial(const Polynomial& rhs){
    degree = rhs.degree;
    head = new Node(rhs.head->data, nullptr);
    Node* n1 = head;
    Node* n2 = rhs.head->next;
    while(n2){
        n1->next = new Node(n2->data, nullptr);
        n1 = n1->next;
        n2 = n2->next;
    }
}


Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this != &rhs){
        degree = rhs.degree;

        //delete old nodes
        Node* n = head;
        while(n){
            Node* temp = n->next;
            delete n;
            n = temp;
        }
        //assigning
        head = new Node(rhs.head->data);
        Node* iter = head;
        Node* rhs_iter = rhs.head->next;

        while(rhs_iter){
            iter->next = new Node(rhs_iter->data);
            iter = iter->next;
            rhs_iter = rhs_iter->next;
        }
    }
    return *this;
}


Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    Node* n1 = head;
    Node* n2 = rhs.head;
    Node* pre_n1 = n1; //buffer when rhs is longer
    while(n1 && n2){
        n1->data = n1->data + n2->data;
        pre_n1 = n1;
        n1 = n1->next;
        n2 = n2->next;
        }
    //if rhs is longer, add to list
    while(n2){
        pre_n1->next = new Node(n2->data);
        degree += 1;
        pre_n1 = pre_n1->next;
        n2 = n2->next;                
    }
    zeros_cleanup();
    return *this;
}


bool Polynomial::operator==(const Polynomial& rhs) const{
    if(degree == rhs.degree){
        Node* n1 = head;
        Node* n2 = rhs.head;
        while(n1){
            if(n1->data != n2->data){
                return false;
            }
            n1 = n1->next;
            n2 = n2->next;
        }
        return true;
    }
    return false;
}


int Polynomial::evaluate(int x) const{
    int r = 0;
    size_t count = 0;            
    Node* iter = head;

    while(iter){
        if(count == 0){
            r += iter->data;
        }
        else{
            int pow_x = 1;
            for(size_t i = 0; i < count; ++i){
                pow_x = pow_x * x;
            }
            r += iter->data * pow_x;
        }
        count += 1;
        iter = iter->next;
    }

    return r;
}


void Polynomial::zeros_cleanup(){
    if(degree == 0){
        return;
    }
    Node* iter = head;
    while(iter){
        if(iter->next && iter->next->data == 0 && iter->data == 0){
            delete iter->next;
            iter->next = nullptr;
            degree -= 1;
            return;
        }
        iter = iter->next;
    } 
}


Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial temp1(rhs);
    return temp1 += lhs;
}

bool operator!=(Polynomial lhs, Polynomial rhs){
    if(lhs == rhs) return false;
    return true;
}