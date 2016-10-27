#include <iostream>

using namespace std;
int tenPow(int power) { // A generic iterative power function
	int r = 1;
	for(int i = 0; i < power; i++) {
		r*=10;
	}
	return r;
}

int main(int argc, char *argv[]){
	int num, i = 1;
	cout << "Enter an integer:";
	cin >> num;
	while(tenPow(i) <= num*10) {
		cout << tenPow(i-1) << "'s digit is: " << (num%tenPow(i) - num%tenPow(i-1)) / tenPow(i-1) << endl;
		i++;
	}
	//The hardcoded method

	// cout << endl << "1's digit is: " << num%10 << endl;
	// cout << "10's digit is: " << (num%100 - num%10)/10 << endl;
	// cout << "100's digit is: " << (num - num%100) / 100;
	return 0;
}
