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
	int year = 0, zipcode = 0;
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
string Network::get_name(int id){
	return users[id].get_name();
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
	if(user == -1) {
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
vector<int> Network::bfs(int start, int end){
	vector <int> q;
	vector <int> path;
	q.push_back(start);
	int cur;
	users[start].depth = 0;
	while(q.size() !=0) {
		cur = q.front();
		q.erase(q.begin());
		vector<int> friends =  users[cur].friend_vector();
		for(int i = 0; i < friends.size(); i++) {
			if(users[friends[i]].predecessor == -1 && friends[i] != start) {
				users[friends[i]].predecessor = cur;
				users[friends[i]].depth = users[cur].depth+1;
				q.push_back(friends[i]);
			}
		}
	}
	if(users[end].predecessor != -1) {
		path.push_back(end);
		cur = end;
		while(true) {
			cur = users[cur].predecessor;
			if(cur == start) {
				return path;
			}
			path.push_back(cur);
		}
	}
	path.push_back(-1);
	return path;
}

void Network::reset_bfs(){
	for(int i = 0; i < users.size(); i++) {
		users[i].depth = -1;
		users[i].predecessor = -1;
	}
}
vector<int> Network::shortest_path(int from, int to){
	vector<int> path = bfs(from, to);
	if(path[0] == -1) {
		cout << "None";
	}
	else{
		cout << "Distance: " << path.size() << endl;
		cout << users[from].get_name();
		for(int i = path.size()-1; i>=0; i--) { // Path is reversed
			cout << " -> " <<  users[path[i]].get_name();
		}
	}
	reset_bfs();
	return path;
}
vector< vector<int> > Network::groups(){
	vector<int> visited;
	vector<int> temp;
	vector< vector<int> > output;
	int count = 0;
	for(int i = 0; i < users.size(); i++) {
		bool isVisited = false;
		for(int j = 0; j < visited.size(); j++) {
			if(visited[j] == i)
				isVisited = true;
		}
		if(!isVisited) {
			temp.clear();
			bfs(i,i);
			for(int k = 0; k < users.size(); k++) {
				if(users[k].depth != -1) {
					temp.push_back(k);
				}

			}
			visited = temp;
			output.push_back(temp);
			reset_bfs();
		}
	}
	return output;
}
vector<int> Network::suggest_friends(int who, int& score){
	vector<int> canidates;
	vector<int> results;
	bfs(who,who);
	for(int i = 0; i < users.size(); i++) {
		if(users[i].depth == 2) {
			canidates.push_back(i);
		}
	}
	for(int i = 0; i < canidates.size(); i++) {
		int mutal = 0;
		for(int j = 0; j< users[who].friend_vector().size(); j++) {
			for(int k = 0; k < users[canidates[i]].friend_vector().size(); k++) {
				if(users[who].friend_vector()[j] == users[canidates[i]].friend_vector()[k]) {
					mutal++;
				}
			}
		}
		if(mutal == score) {
			results.push_back(canidates[i]);
		}
		if(mutal > score) {
			results.clear();
			results.push_back(canidates[i]);
			score = mutal;
		}

	}
  reset_bfs();
	return results;
}
