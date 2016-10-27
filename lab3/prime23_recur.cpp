#include <iostream>
using namespace std;

int* recursion(int* data){
	if(data[2] % 2 == 0) {
		data[2]/=2;
		data[0]+=1;
		return recursion(data);
	}
	else if(data[2] % 3 == 0) {
		data[2] /= 3;
		data[1] += 1;
		return recursion(data);
	}
	else if(data[2] != 1) {
		data[2] = -1;
	}
	return data;
};

int main(int argc, char *argv[]){
	int data[3] = {0,0,0};
	cout << "Enter a Positive Integer: ";
	cin >> data[2];
	recursion(data);
	if(data[2] == -1) {
		cout << "NO";
	}
	else {
    cout << "YES" << endl;
		cout << "Twos=" << data[0] << " Threes="  << data[1];
	}
	return 0;
}
