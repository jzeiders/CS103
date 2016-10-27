#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, char *argv[]){
  double angle, range;
  cout << "Enter value between 15 && 75: ";
  cin >> angle;
  for(int i = 0; i <  31 ; i++){
    range = floor(tan(angle * M_PI / 180)*i);
    if(range >= 20 && range <= 30)
      range = 20;
    for(int j =0; j < range; j++){
      cout << "*";
    }
    cout << endl;
  }
}
