// rec01-start.cpp
// 2124 21S


#include <iostream>    // Tasks 3, 4, 5 and 6
#include <fstream>     // Task 4, 5 and 6
#include <string>      // Task 5
using namespace std;

int main() {
    // Task 3
    cout << "Task 3\n========\n";
    // Put code for Task 3 here
    cout << "Yay C++!!!" << endl;


    // Task 4
    cout << "Task 4\n========\n";
    // Put code for Task 4 here
    ifstream integers("integers.txt");
    if (!integers){
        cerr << "Could not open the file integers.txt\n";
        exit(1);
    }
    int sum = 0;
    int x;

    while (integers >> x){
        sum += x;
    }
    cout << sum << endl;


    // Task 5
    cout << "Task 5\n========\n";
    // Put code for Task 5 here
    ifstream text("text.txt");
    if (!text){
        cerr << "Could not open the file text.txt\n";
        exit(1);
    }
    string word;

    while (text >> word){
        cout << word << endl;
    }


    // Task 6
    cout << "Task 6\n========\n";
    // Put code for Task 6 here
    ifstream mixed("mixed.txt");
    
    if (!mixed){
        cerr << "Could not open the file mixed.txt\n";
        exit(1);
    }
    sum = 0;
    int y;
    while (mixed >> y){
        sum += y;
    }
    cout << sum << endl;
}
