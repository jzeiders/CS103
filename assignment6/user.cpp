#include "user.h"
#include <iostream>
#include <sstream>
#include <algorithm>

using namespace std;

//Has Friends
User::User(int _id, string _name, int _year, int _zip, string _friends){
	//Removes Tabs on Name
	_name.erase(std::remove(_name.begin(), _name.end(), '\t'), _name.end());
	id = _id;
	name = _name;
	year = _year;
	zip = _zip;
	istringstream iss(_friends); // Iterates through friend list
	int f_id;
	while(iss >> f_id) {
		add_friend(f_id);
	}
  depth = -1;
  predecessor = -1;
}
//Has No Friends
User::User(int _id, string _name, int _year, int _zip){
	id = _id;
	name = _name;
	year = _year;
	zip = _zip;
}
User::~User(){

}
void User::add_friend(int _id){
	friends.push_back(_id);
}
void User::delete_friend(int _id){
	for(int i = 0; i < friends.size(); i++)
		if(friends[i] == _id) {
			friends.erase(friends.begin()+i);
			return;
		}
	cout << "Friendship did not exist";
}
int User::get_id(){
	return id;
}
string User::get_name(){
	return name;
}
int User::get_year(){
	return year;
}
int User::get_zip(){
	return zip;
}
vector<int> User::friend_vector(){
  return friends;
}
string User::get_friends(){
	ostringstream sFriends;
	for(int i = 0; i < friends.size(); i++) {
		sFriends << friends[i] << " ";
	}
	return sFriends.str();
}
