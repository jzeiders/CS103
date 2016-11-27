#include <iostream>

using namespace std;

int main(){
  int n = 1000;
  int b = 2;
  int a = 0;
  while(n>=b){
    n/=b;
    a++;
  }
  cout << a << endl;
  cout << (3+9+21+39)/5;
  return 0;
}
