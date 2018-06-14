/**
@file   main.cpp

@author Danny Brown (dmb0057)
@version 05-02-2018 22:26

@section DESCRIPTION

This result of this program is a teller terminal system that allows bank
administrators and staff to perform several task (i.e. create accounts).

The following links have been used to assist in the development of this
protoype:

http://www.cplusplus.com/reference/ios
http://www.cplusplus.com/reference/fstream

The class textbook "Absolute C++" was also used.

There are some known issues with this prototype and are documented where
necessary. Make sure that the data\accounts and data\staff exists and is located
in the current directory. I made an error while writing this project.

To compile, you will need to use g++ in a Linux terminal with C++11.
i.e. "g++ -o main main.cpp -std=c++0x" or "g++ -o main main.cpp
-std=c++11". note: I used the former to compile my source code and it worked as
desired.

*/

#include "menu.cpp"
#include <cstdlib>
#include <iostream>
#include <string>

/**
@brief Program Operations

@param none
@return exit code 0
*/
int main(int argc, char const *argv[]) {
  Menu menu;
  menu.start_program();

  return 0;
}
