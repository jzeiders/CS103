#include<iostream>
using namespace std;

void printHistorgram(int counts[]){
  for(int i = 4; i<25;i++){
    cout << i << ":";
    for(int j = 0; j <counts[i-4];j++ ){
      cout << "X";
    }
    cout << endl;
  }
}

int roll(){
  return rand()%6+1;
}
int main(int argc, char *argv[]){
  srand(time(NULL));
  int rolls, counts[21] = {0};
  cout << "Input # of Rolls: ";
  cin >> rolls;
  for(int i = 0; i<rolls; i++){
    counts[roll() + roll() + roll() + roll()-4] += 1;
  }
  printHistorgram(counts);
  return 0;
}
