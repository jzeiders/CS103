/* John Zeiders
   Calculate Hailstats
 */
#include <iostream>

using namespace std;
int hail(int start);

int hail(int start){
	int count = 0;
	while(start > 1) {
		if(start % 2 == 0) {
			start /= 2;
			count +=1;
		}
		else {
			start*=3;
			start+=1;
			count +=1;
		}
	}
	return count;
};

int main(int argc, char *argv[]) {
	int min,max;
	cout << "Enter the range you want to search: ";
	cin >> min >> max;
	if(min > max) {
		cout << "Invalid Range";
	}
	else {
		int minLen = hail(min), minNum = min, maxLen = hail(min), maxNum = min;
		for(int i = min; i < max; i++) { //Does all the work
			int curHail = hail(i);
			if(curHail < minLen) {
				minLen = curHail;
				minNum = i;
			}
			if(curHail > maxLen) {
				maxLen = curHail;
				maxNum = i;
			}
		}
		cout << "Minimum length:" << minLen << endl;
		cout << "Achieved By:" << minNum << endl;
		cout << "Maximum length:" << maxLen << endl;
		cout << "Achieved By:" << maxNum << endl;
	}
	return 0;

}
