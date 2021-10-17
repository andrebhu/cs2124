//#include "polynomial.h"
#include <iostream>
#include <vector>
using namespace std;

class Polynomial{
    struct Node{
        Node(int data = 0, Node* next = nullptr) : data(data), next(next) {}
        int data;
        Node* next;
    };

    friend ostream& operator<<(ostream& os, const Polynomial& rhs){
        const Node* i = rhs.head;
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

    public:
        Polynomial() {};

        //constructor with vector, coefs are stored backwards
        Polynomial(const vector<int>& coefficients){
            degree = coefficients.size() - 1;

            head = new Node(coefficients[coefficients.size() - 1]);
            Node* iter = head;
        
            for(int i = degree - 1; i >= 0; --i){
                iter->next = new Node(coefficients[i]);
                iter = iter->next;
                
            }
            zeros_cleanup();
        }

        //copy constructor
        Polynomial(const Polynomial& rhs){
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

        //assignment operator
        Polynomial& operator=(const Polynomial& rhs){
            if(this != &rhs){
                degree = rhs.degree;

                //delete old nodes
                Node* n = head;
                while(n){
                    Node* temp = n->next;
                    delete n;
                    n = temp;
                }
                
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

        //destructor
        ~Polynomial(){
            degree = 0;
            Node* iter = head;
            head = nullptr;
            while(iter){
                Node* n = iter->next;
                delete iter;
                iter = n;
            }
        }

        //if there are two trailing zeros
        void zeros_cleanup(){
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

        //+=
        Polynomial& operator+=(const Polynomial& rhs){
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

        bool operator==(const Polynomial& rhs){
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

        //calculates polynomial
        int evaluate(int x){
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
    private:
        size_t degree = 0;
        Node* head = nullptr;
};



Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial temp1(rhs);
    return temp1 += lhs;
}

bool operator!=(Polynomial lhs, Polynomial rhs){
    if(lhs == rhs) return false;
    return true;
}


void doNothing(Polynomial temp) {}

int main() {
	
    //test constructor
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -1x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7
	
    cout << "p1: " << p1 << endl;
    cout << "p2: " << p2 << endl;
    cout << "p3: " << p3 << endl;
    cout << "p4: " << p4 << endl;
    cout << "has_a_zero: " << has_a_zero << endl;    
    
    cout << "p2 + p3: " << (p2+p3) << endl; 
    cout << "p2 + p4: " << (p2+p4) << endl; 
    cout << "p4 + p2: " << (p4+p2) << endl;


    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    cout << "p4: " << p4 << endl; //delete
    Polynomial p5(p4);
    cout << "p5: " << p5 << endl; //delete
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  

    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    
    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
	
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;
    
    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

	//=================================================================
	//NEW TEST CODE - test if cleaning the leading 0s
	//===================================================================

	Polynomial p8({ 1, 1 });
	Polynomial p9({ -1, 1 });
	Polynomial p10({ 0, 0, 2 });
	//p8 + p9 tests if += does the cleanup()
	//p10 tests if constructor does the cleanup()
	cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;
}


