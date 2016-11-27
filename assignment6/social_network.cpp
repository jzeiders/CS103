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


	vector<vector<int> > results;
  vector<int> path;
	while(true) {
		int option;
		cin >> option;
		if(option < 1 || option > 9)
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
		case 7:
			cin >> f >> l >> f2 >> l2;
			path = network.shortest_path(network.get_id(f + " " + l),
								 network.get_id(f2 + " " + l2));
			break;
		case 8:
			results = network.groups();
			for(int i = 0; i < results.size(); i++) {
				cout << "Set " << i << ": ";
				for(int j = 0; j < results[i].size(); j++) {
					cout << results[i][j] << " ";
				}
				cout << endl;
			}
			break;
		case 9:
			cin >> f >> l;
			int id = network.get_id(f + " " + l);
			int score;
			vector<int> suggests = network.suggest_friends(id, score);
      cout << "The suggested friends are:" << endl;
      if(suggests.size() == 0){
        cout << " None";
      }
      for(int i = 0 ; i < suggests.size();i++){
        cout << network.get_name(suggests[i]) << " : " << score << endl;
      }
    	break;
		}
	}
	return 0;
}
