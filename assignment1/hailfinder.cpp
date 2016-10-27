/* John Zeiders
Calculate Hailstones
*/
#include <iostream>

using namespace std;

int hail(int start);

int hail(int start){
  int count = 0;
  while(start > 1) {
    if(start % 2 == 0){ // Even Case
      start /= 2;
      // cout << start << " ";
      count +=1;
    }
    else { //Odd Case
      start*=3;
      start+=1;
      // cout << start << " ";
      count +=1;
    }
  }
  return count;
};

int main(int argc, char *argv[]) {
    int num = 1;
    while(true){
      if(hail(num) == 151)
        break;
      num++;
    }
    cout << num;
    return 0;
}
