#ifndef USER_H
#define USER_H
#include<vector>
#include<string>

using namespace std;

class User {
 public:
   User(int _id, string _name, int _year, int _zip, string friends);
   User(int _id, string _name, int _year, int _zip);
   ~User();
   void add_friend(int id);
   void delete_friend(int id);
   int get_id();
   string get_name();
   int get_year();
   int get_zip();
   string get_friends();

 private:
   int id;
   string name;
   int year;
   int zip;
   vector<int> friends;

};


#endif
