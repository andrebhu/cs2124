//Andre Hu
//4/23

#include <cstdlib>
#include <iostream>
using namespace std;

class List {
    struct Node{
        int data;
        Node* next = nullptr;
        Node* prior = nullptr;
    };

    friend ostream& operator<<(ostream& os, const List& rhs){
        const Node* i = rhs.header->next;
        while (i != rhs.trailer){
            os << i->data << " ";
            i = i->next;
        }
        return os;
    }

public:
    List() : list_size(0), header(new Node()), trailer(new Node()) {
        header->next = trailer;
        trailer->prior = header;
    }

    //task 1
    void push_back(int i){
        Node* n = new Node{i, trailer, trailer->prior};
        trailer->prior->next = n;
        trailer->prior = n;
        list_size += 1;
    }

    int pop_back(){
        if(list_size == 0){
            return -1;
        }
        Node* temp = trailer->prior;
        int r = temp->data;

        trailer->prior->prior->next = trailer;
        trailer->prior = trailer->prior->prior;

        delete temp;
        list_size -= 1;
        return r;
    }

    size_t size() const { return list_size; }

    int front() const{
        return header->next->data;
    }
    int& front(){
        return header->next->data;
    }

    int back() const{
        return trailer->prior->data;
    }
    int& back(){
        return trailer->prior->data;
    }

    //task 2
    void push_front(int i){
        Node* n = new Node{i, header->next, header};
        header->next->prior = n;
        header->next = n;
        list_size += 1;
    }

    int pop_front(){
        if(list_size == 0){
            return -1;
        }
        Node* temp = header->next;
        int r = temp->data;

        header->next->next->prior = header;
        header->next = header->next->next;

        delete temp;
        list_size -= 1;
        return r;
    }

    //task 3
    void clear(){
        while(list_size > 0){
            pop_back();
        }
    }

    //task 4
    int operator[](size_t index) const{
        Node* temp = header->next;
        for(size_t i = 0; i < index; ++i){
            temp = temp->next;
        }
        return temp->data;
    }

    int& operator[](size_t index){
        Node* temp = header->next;
        for(size_t i = 0; i < index; ++i){
            temp = temp->next;
        }
        return temp->data;
    }

    //task 5
    class iterator{
        friend List;
        friend bool operator==(const iterator& lhs, const iterator& rhs){
            return lhs.n == rhs.n;
        }
        friend bool operator!=(const iterator& lhs, const iterator& rhs){
            return !(lhs.n == rhs.n);
        }
        public:
            iterator(Node* n) : n(n) {}
            iterator& operator++(){
                if(n){
                    n = n->next;
                }
                return *this;
            }
            iterator& operator--(){
                if(n){
                    n = n->prior;
                }
                return *this;
            }
            int& operator*(){
                return n->data;
            }
            
            int operator*() const{
                return n->data;
            }

        private:
            Node* n;
    };

    iterator begin() const{
        iterator p(header->next);
        return p;
    }

    iterator end() const{
        iterator p(trailer);
        return p;
    }

    //task 6
    iterator insert(iterator iter, int i){
        Node* temp = new Node{i, iter.n, iter.n->prior};
        iter.n->prior->next = temp;
        iter.n->prior = temp;
        iter.n = temp;
        list_size += 1;
        return iter;
    }

    //task 7
    iterator erase(iterator iter){
        Node* temp = iter.n;
        iter.n->prior->next = iter.n->next;
        iter.n->next->prior = iter.n->prior;
        iter.n = iter.n->next;
        list_size -= 1;
        delete temp;
        return iter;
    }

    
private:
    int list_size;
    Node* header;
    Node* trailer;
};

// Task 1
void printListInfo(const List& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// The following should not compile. Check that it does not.
//void changeFrontAndBackConst(const List& theList){
//     theList.front() = 17;
//    theList.back() = 42;
//}

void changeFrontAndBack(List& theList){
    theList.front() = 17;
    theList.back() = 42;
}


// Task 4
void printListSlow(const List& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// Task 8
void doNothing(List aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << endl;
    cout << "Leaving doNothing\n";
}    




int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";
    
    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";
    
    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    cout << "===================\n";
    
    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";
    
    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    cout << "===================\n";

    
    // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    /*
    // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
    */
}
