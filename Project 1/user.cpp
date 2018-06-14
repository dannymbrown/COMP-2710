/**
@file   user.cpp

@author Danny Brown (dmb0057)
@version 04-02-2018 15:31

@section DESCRIPTION

Handles user info. Used in system.cpp.

*/

#include <string>

using namespace std;

struct User {
  string username;
  int score;
};

void setuser(User &iuser, std::string name) {
  iuser.username = name;
  iuser.score = 0;
}

std::string getname(User &iuser) { return iuser.username; }

User getUser(User &iuser) { return iuser; }
