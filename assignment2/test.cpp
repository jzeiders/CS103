#include <iostream>
#include <cstdlib>    // Other helpful functions => rand(), RANDMAX
using namespace std;
int main() {
  srandom(time(NULL));
  cout <<  random()/(double)RAND_MAX;
  return 0;
}
