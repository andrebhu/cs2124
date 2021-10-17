/*
Andre Hu
5/7
rec14
*/

#include <iostream>
using namespace std;


//task 1
bool taskOne(int x){
  if(x <= 0){
    return true;
  }
  bool t = x % 2 == 0;
  return t == taskOne(x / 2);
}

//task 2
struct Node{
  Node(int data, Node* next = nullptr) : data(data), next(next) {}
  int data;
  Node* next;
};

Node* taskTwo(const Node* lhs, const Node* rhs){
  if(!lhs && !rhs){
    return nullptr;
  }
  if(!lhs){
    return new Node(rhs->data, taskTwo(nullptr, rhs->next));
  }
  if(!rhs){
    return new Node(lhs->data, taskTwo(lhs->next, nullptr));
  }
  return new Node(lhs->data + rhs->data, taskTwo(lhs->next, rhs->next));
}

//task 3
struct TNode {
  TNode(int data = 0, TNode *left = nullptr, TNode *right = nullptr)
    : data(data), left(left), right(right) {}
  int data;
  TNode *left, *right;
};

int max(TNode* root) {
  if(!root){
    throw invalid_argument("empty");
  }

  int ret = root->data;

  if(root->left){
    int l = max(root->left);
    if(l > ret){
      ret = l;
    }
  }

  if(root->right){
    int r = max(root->right);
    if(r > ret){
      ret = r;
    }
  }

  return ret;
}

//task 4
bool palindrome(const char arr[], int size){
  if(size <= 1){
    return true;
  }
  else{
    if(arr[0] != arr[size - 1]){
      return false;
    }
    return palindrome(arr + 1, size - 2);
  }

}

//task 5
int towers(int n, char start, char spare, char stop){
    if (n == 0) return 0;

    int x = 0;
    x += towers(n-1, start, spare, stop);
    //cout << "Move disk " << n << " from spindle " << start << " to spindle " << stop << endl;
    x += towers(n-1, spare, stop, start);
    return 1 + x;
}

//task 6
void mystery(int n) { 
   if (n > 1) { 
      cout << 'a'; 
      mystery(n/2); 
      cout << 'b'; 
      mystery(n/2); 
   } 
   cout << 'c'; 
}
//c
//c
//acbcc
//acbcc
//a acbcc b acbcc
//same until 7
//a aacbcc bacbcc c | b a acbcc bacbcc c c


int main() {
  cout << taskOne(25) << " " << taskOne(23) << endl;

  TNode a(1), b(2), c(4), d(8, &a, &b), e(16, &c), f(32, &d, &e);
  cout << max(&f) << endl;

  char s[] = "noon";
  cout << palindrome(s, 4) << endl;

  cout << towers(10, 'a', 'b', 'c') << endl;
  for(size_t i = 0; i < 11; ++i){
    cout << i << ": ";
    mystery(i);
    cout << endl;
  }
}

  
  
