#include<iostream>
#include<unordered_map>
#include<stdexcept>
// #include<algorithm>
#include<numeric>
#include<iterator>
#include"vector.h"
using namespace std;

class A {
};

int main() {
    Vector<A> x;
    for (int i = 0; i < 100; ++i) {
        x.push_back(A());
    }
    cout << x.size() << endl;
  return 0;
}
