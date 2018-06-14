/**
@file   project1.cpp

@author Danny Brown (dmb0057)
@version 04-02-2018 15:31

@section DESCRIPTION

Limited outside resources were used and are documented where relevant as line
comments.

To compile, you will need to use g++ in a Linux terminal with C++11.
i.e. "g++ -o project1 project1.cpp -std=c++0x" or "g++ -o project1 project1.cpp
-std=c++11". note: I used the former to compile my source code and it worked as
desired.

*/

#include "menu.cpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
  Menu menu;
  std::string border =
      "===========================================================";
  std::string name;
  std::cout << "\n\t\tWhat's your name? ";
  getline(cin, name);
  std::cout << "\n\n"
            << border << "\n|                     Welcome, " << name
            << "                         |\n"
            << border << '\n';
  menu.startmenu();

  return 0;
}
