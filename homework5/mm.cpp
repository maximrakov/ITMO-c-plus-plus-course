#include<iostream>
#include <iostream>
#include <algorithm>
#include "CircularBuffer.hpp"

using namespace std;

using namespace std;
int main(){
  int* p = new int[3];
  p[0] = 1;
  p[1] = 2;
  p[2] = 3;
  // cout << *(++p) << endl;
  // cout << endl << endl;
  CircularBuffer<int> c(4);
  c.addFirst(45);
  // cout << c.ed << endl;
  c.addLast(23);
  // cout << c.ed << endl;
  c.addLast(233);
  // cout << c.ed << endl;
  c.addFirst(1337);
  c.pp();
  // cout << c.ed << endl;
  
  // auto = c.begin();
  // ++i;
  // cout << *(it);
  return 0;
}