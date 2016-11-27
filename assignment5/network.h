#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <vector>
#include "user.h"

using namespace std;

class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(string username, int yr, int zipcode, string friends);
  void add_user(string username, int yr, int zipcode);
  int add_connection(string name1, string name2);
  int remove_connection(string name1, string name2);
  int get_id(string username);
  void print_friends(string username);
  void print_all();
 private:
   vector<User> users;

};


#endif
