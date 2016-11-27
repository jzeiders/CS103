#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Network::Network(){

}
Network::~Network(){

}
int Network::read_friends(const char *filename){
	ifstream file (filename);
	if(file.fail()) {
		return -1;
	}
	int number;
	file >> number;
	string name,friends,line;
	getline(file,line);
	int year = 0 , zipcode = 0;
	for(int i = 0; i < number; i++) {
		getline(file,line);
		getline(file,name);
		getline(file,line);
    istringstream iss(line); //Converts to INT
		if(iss >> year) //if required to supress "unused expression warning"
      year *=1;
		getline(file,line);
    istringstream iss2(line);
    if(iss2 >> zipcode)
  		zipcode *=1;
		getline(file,friends);
		add_user(name,year,zipcode,friends);
	}
	return 0;
}
int Network::write_friends(const char *filename){
	ofstream file (filename);
	if(file.fail())
		return -1;
	int size = users.size();
	file << size << endl;
	for(int i = 0; i < size; i++) {
		file << i << endl;
		file << "\t" << users[i].get_name() << endl;
		file << "\t" << users[i].get_year() << endl;
		file << "\t" << users[i].get_zip() << endl;
		file << "\t" << users[i].get_friends() << endl;

	}
	return 0;
}
void Network::add_user(string username, int yr, int zipcode, string friends){
	users.push_back(User(users.size(),username,yr,zipcode, friends));
	return;
}
void Network::add_user(string username, int yr, int zipcode){
	users.push_back(User(users.size(),username,yr,zipcode));
	return;
}
int Network::add_connection(string name1, string name2){
	int user1 = get_id(name1);
	int user2 = get_id(name2);
	if(user1 == -1 || user2 == -1) // Failure States
		return -1;
	users[user1].add_friend(user2);
	users[user2].add_friend(user1);
	return 0;
}
int Network::remove_connection(string name1, string name2){
	int user1 = get_id(name1);
	int user2 = get_id(name2);
	if(user1 == -1 || user2 == -1) // Failure States
		return -1;
	users[user1].delete_friend(user2);
	users[user2].delete_friend(user1);
	return 0;
}
int Network::get_id(string username){
	for(int i = 0; i < users.size(); i++) {
		if(username.find(users[i].get_name())!= -1) {
			return users[i].get_id();
		}
	}
	return -1;
}

// Taken from stackoverflow, credit to Cyril Leroux, template for using iomanip
// Saved so much typing.
template<typename T> void printElement(T t, const int& width)
{
	cout << left << setw(width) << setfill(' ') << t;
}
// End stack copy
void Network::print_all(){
  //Prints Header
	int idW = 7, nameW = 20, yearW = 7, zipW = 12;
	printElement("ID",idW);
	printElement("NAME",nameW);
	printElement("YEAR",yearW);
	printElement("ZIP",zipW);
	cout << endl;
	for(int i = 0; i < 46; i++)
		cout << "=";
	cout << endl;
  //Prints Table
	for(int i = 0; i < users.size(); i++) {
		ostringstream id;
		id << users[i].get_id() << ".";
		printElement(id.str(),idW);
		printElement(users[i].get_name(),nameW);
		printElement(users[i].get_year(),yearW);
		printElement(users[i].get_zip(),zipW);
		cout << endl;
	}
}
void Network::print_friends(string username){
  int user = get_id(username);
  if(user == -1){
    cout << "Invalid User" << endl;
    return;
  }
	string friends = users[user].get_friends();
	istringstream s;
	s.str(friends);
	int idW = 7, nameW = 20, yearW = 7, zipW = 12;
	printElement("ID",idW);
	printElement("NAME",nameW);
	printElement("YEAR",yearW);
	printElement("ZIP",zipW);
	cout << endl;
	for(int i = 0; i < 46; i++)
		cout << "=";
  cout << endl;
	int i;
  //Prints table
	while(s >> i) {
		ostringstream id; // Stream used to append string to int
		id << users[i].get_id() << ".";
		printElement(id.str(),idW);
		printElement(users[i].get_name(),nameW);
		printElement(users[i].get_year(),yearW);
		printElement(users[i].get_zip(),zipW);
		cout << endl;
	}
}
