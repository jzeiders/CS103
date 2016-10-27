#include <iostream>
using namespace std;


int main(int argc, char *argv[]){
	int data[3] = {0,0,0};
	cout << "Enter a Positive Integer: ";
	cin >> data[2];
  while(data[2] % 2 == 0 || data[2] % 3 == 0){
    if(data[2]%2 == 0){
      data[0]++;
      data[2]/=2;
    }

    if(data[2]%3 == 0){
      data[1]++;
      data[2]/=3;
    }
  }
	if(data[2] != 1) {
		cout << "NO";
	}
	else {
    cout << "YES" << endl;
		cout << "Twos=" << data[0] << " Threes="  << data[1];
	}
	return 0;
}
