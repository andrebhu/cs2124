// rec13.cpp
// 4/30
// Andre Hu

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;


//task 9
void printList(const list<int>& lst){
    list<int>::const_iterator iter;
    for(iter = lst.begin(); iter != lst.end(); ++iter){
        cout << *iter << " ";
    }
    cout << endl;
}

//task
void for_each_printList(const list<int>& lst){
    for(int x : lst){
        cout << x << " ";
    }
    cout << endl;
}


//task 11
void autoPrintList(const list<int>& lst){
    for(auto iter = lst.begin(); iter != lst.end(); ++++iter){
        cout << *iter << " ";
    }
    cout << endl;
}


//task 12
list<int>::const_iterator findElementInList(int x, const list<int>& lst){
    for(auto iter = lst.begin(); iter != lst.end(); ++iter){
        if(*iter == x){
            return iter;
        }
    }
    return lst.end();
}


//task 13
auto autoFindElementInList(int x, const list<int>& lst){
    for(auto iter = lst.begin(); iter != lst.end(); ++iter){
        if(*iter == x){
            return iter;
        }
    }
    return lst.end();
}


//task 15
bool isEven(int x){
    return !(x % 2);
}


//task 16
class isEven_functor{
    public:
        bool operator() (int x) const{
            return !(x % 2);
        }
};


//task 19
list<int>::iterator ourFind(int x, list<int>::iterator begin, list<int>::iterator end){
    cout << "ourFind" << endl;
    for(begin; begin != end; ++begin){
        if(*begin == x){
            return begin;
        }
    }
    return end;
}


//task 20
template <typename U, typename T>
T templated_ourFind(U x, T begin, T end){
    cout << "templated ourFind" << endl;
    for(T iter = begin; iter != end; ++iter){
        if(*iter == x){
            return iter;
        }
    }
    return end;
}

int main() {


    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> v = {5, 2, 6, 1, 3, 4, 9, 7, 8, 0};
    for(int i : v){
        cout << i << " ";
    }
    cout << "\n=======\n";


    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> l(v.begin(), v.end());
    for(int i : l){
        cout << i << " ";
    }
    cout << "\n=======\n";


    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(v.begin(), v.end());
    cout << "Vector: ";
    for(int i : v){
        cout << i << " ";
    }
    cout << "\nList: ";
    for(int i : l){
        cout << i << " ";
    }
    cout << "\n=======\n";


    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(size_t i = 0; i < v.size(); i += 2){
        cout << v[i] << " ";
    }
    cout << "\n=======\n";


    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    /*for(size_t i = 0; i < l.size(); ++i){
        cout << l[i] << " ";
    }*/
    cout << "lists wack";
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    vector<int>::iterator viter;
    for(viter = v.begin(); viter < v.end(); viter += 2){
        cout << *viter << " ";
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    list<int>::iterator liter;
    for(liter = l.begin(); liter != l.end(); ++++liter){
        cout << *liter << " ";
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    l.sort();
    for(int i : l){
        cout << i << " ";
    }
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printList(l);
    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    for(int i : l){
        cout << i << " ";
    }
    cout << endl;
    for_each_printList(l);
    cout << endl;
    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    autoPrintList(l);
    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int> task12 = {5, 3, 7, 2, 4};
    cout << *findElementInList(3, task12) << endl;
    cout << *findElementInList(20, task12) << endl;
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    list<int> task13 = {7, 4, 1, 2, 8};
    cout << *autoFindElementInList(1, task13) << endl;
    cout << *autoFindElementInList(20, task13) << endl;
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    list<int> task14 = {7, 5, 1, 4, 9, 0};
    cout << *find(task14.begin(), task14.end(), 1) << endl;
    cout << *find(task14.begin(), task14.end(), 2) << endl;
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    list<int> task15 = {7, 2, 5};
    cout << *find_if(task15.begin(), task15.end(), isEven) << endl;
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    list<int> task16 = {7, 2, 5, 1, 3, 8};
    cout << *find_if(task16.begin(), task16.end(), isEven_functor()) << endl;
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    list<int> task17 = {1, 3, 5, 7, 8};
    cout << *find_if(task17.begin(), task17.end(), [](int x) -> bool { return !(x % 2); }) << endl;
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* task18 = new int[10];
    copy(l.begin(), l.end(), task18);
    for(list<int>::iterator i = l.begin(); i != l.end(); ++i){
        cout << *i << " ";
    }
    cout << endl;
    cout << *find(task18, task18 + 10, 4) << endl;
    delete[] task18;
    cout << endl;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int> task19 = {6, 3, 1, 2, 8, 9};
    list<int>::iterator b = task19.begin();
    list<int>::iterator e = task19.end();
    cout << *ourFind(1, b, e) << endl;
    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    list<int> task20 = {6, 3, 1, 2, 8, 9};
    list<int>::iterator b20 = task20.begin();
    list<int>::iterator e20 = task20.end();
    cout << *templated_ourFind(1, b20, e20) << endl;
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream task21_ifs("pooh-nopunc.txt");
    if(!task21_ifs){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }

    vector<string> words;
    string token;
    while(task21_ifs >> token){
        if(find(words.begin(), words.end(), token) == words.end()){
            words.push_back(token);
        }
    }
    cout << words.size();
    task21_ifs.close();
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifstream task22_ifs("pooh-nopunc.txt");
    if(!task22_ifs){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }

    set<string> set_of_words;
    while(task22_ifs >> token){
        set_of_words.insert(token);
    }
    cout << set_of_words.size() << endl;
    task22_ifs.close();
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifstream task23_ifs("pooh-nopunc.txt");
    if(!task23_ifs){
        cerr << "Couldn't open file" << endl;
        exit(1);
    }

    map<string, vector<int>> wordMap;
    int location = 0;
    while(task23_ifs >> token){
        wordMap[token].push_back(location);
        location += 1;
    }
    cout << wordMap.size() << endl;

    for(const auto& word : wordMap){
        cout << word.first << " ";
        for(const auto& location : word.second){
            cout << location << " ";
        }
        cout << endl;
    }
    task23_ifs.close();
    cout << "=======\n";
}
