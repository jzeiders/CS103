#include <string>
#include <vector>
#include <iostream>
#include "bigint.h"

using namespace std;
using std::string;
using std::vector;

BigInt::BigInt(string term){
	for(int i = 0; i  < term.length(); i++) {
		value.push_back((int)term[i] -48);
	}
}

string BigInt::to_string(){
	string val = "";
	for(int i = 0; i < value.size(); i++) {
		val+= std::to_string(value[i]);
	}
	return val;
}

void BigInt::add(BigInt in){
	vector<int> b = in.value;
	int size = b.size(); // Figure out the smaller one
	if(size > value.size())
		size = value.size();
	for(int i = 0; i < size; i++) {
    int val_i = value.size()-i-1;
    int b_i = b.size()-i-1;
		value[val_i] += b[b_i];
		if(value[val_i] > 9) {
			if(val_i-1 == -1) { //Handling that edge case
				value.insert(value.begin(),1);
				value[val_i+1]-=10;
			}
			else {
				value[val_i-1]+=1;
				value[val_i]-=10;
			}
		}
	}
}
