#include "network.h"
#include "user.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	string f, l, f2, l2;
	char file[25];
	int year, zip;
	if(argc !=2) { // Expects a text file
		cout << "Insufficent Inputs";
		return 0;
	}
	Network network;
	if(network.read_friends(argv[1]) ==-1) {
		cout << "Invalid Filename";
		return -1;
	}
	while(true) {
		int option;
		cin >> option;
		if(option < 1 || option > 6)
			break;
		switch(option) { // Input handler
		case 1:
			cin >> f >> l >> year >> zip;
			network.add_user(f + " " + l,year,zip);
			break;
		case 2:
			cin >> f >> l >> f2 >> l2;
			if(network.add_connection(f + " " + l, f2 + " " + l2) == -1)
				cout << "Invalid Request" << endl;
			break;
		case 3:
			cin >> f >> l >> f2 >> l2;
			if(network.remove_connection(f + " " + l, f2 + " " + l2) == -1)
				cout << "Invalid Request" << endl; ;
			break;
		case 4:
			network.print_all();
			break;
		case 5:
			cin >> f >> l;
			network.print_friends(f+ " "+ l);
			break;
		case 6:
			cin >> file;
			network.write_friends(file);
			break;
		}
	}
	return 0;
}
