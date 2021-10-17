#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <list>     
#include <algorithm>
#include <set>     
#include <map>

using namespace std;


int product(int n){
  if(n == 0) return 1;
  int val = n % 10;
  return val * product(n / 10);
}

int main(){
  cout << product(-21233);
}