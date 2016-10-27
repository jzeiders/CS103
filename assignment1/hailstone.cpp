/* John Zeiders
Calculate Hailstones
*/
#include <iostream>

using namespace std;

void hail(int start);

void hail(int start){
  int count = 0;
  while(start > 1) {
    if(start % 2 == 0){ // Even Case
      start /= 2;
      cout << start << " ";
      count +=1;
    }
    else { //Odd Case
      start*=3;
      start+=1;
      cout << start << " ";
      count +=1;
    }
  }
  cout << endl << "Length: " << count;
  return;
};

int main(int argc, char *argv[]) {
    int num;
    cout << "Please Enter a Number ";
    cin >> num;
    hail(num);
    return 0;
}
