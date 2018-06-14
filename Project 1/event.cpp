/**
@file   event.cpp

@author Danny Brown (dmb0057)
@version 04-02-2018 15:31

@section DESCRIPTION

Handles random events. Used in system.cpp.

*/

#include <iostream>
#include <string>

using namespace std;

int riddle1() {
  std::cout << "In order to progress, you must answer the following:" << '\n';
  std::cout << "What comes down but never goes up?" << '\n';
  std::cout << "\n\t\t1) Light" << '\n';
  std::cout << "\n\t\t2) Rain" << '\n';
  std::cout << "\n\t\t3) Waves" << '\n';
  std::cout << "\n\t\t4) Temperature" << '\n';
  std::cout << "\nEnter your answer: ";
  int i;
  int j = 1;
  std::cin >> i;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  if (i == 1 || i == 3 || i == 4) {
    std::cout
        << "Sorry, the correct answer is light. You lose 3 intelligence points."
        << '\n';
    j = 0;
  }

  return j;
}

int riddle2() {
  std::cout << "In order to progress, you must answer the following:" << '\n';
  std::cout << "What travels around the world but stays in one spot?" << '\n';
  std::cout << "\n\t\t1) The Ocean" << '\n';
  std::cout << "\n\t\t2) A Plane" << '\n';
  std::cout << "\n\t\t3) A Cloud" << '\n';
  std::cout << "\n\t\t4) A Stamp" << '\n';
  std::cout << "\nEnter your answer: ";
  int i;
  int j = 1;
  std::cin >> i;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  if (i == 1 || i == 3 || i == 2) {
    std::cout << "Sorry, the correct answer is a stamp. You lose 3 "
                 "intelligence points."
              << '\n';
    j = 0;
  }

  return j;
}

int riddle3() {
  std::cout << "\nIn order to progress, you must answer the following:" << '\n';
  std::cout << "What can you catch but not throw?" << '\n';
  std::cout << "\n\t\t1) A ball" << '\n';
  std::cout << "\n\t\t2) Shade" << '\n';
  std::cout << "\n\t\t3) A cold" << '\n';
  std::cout << "\n\t\t4) A hat" << '\n';
  std::cout << "\nEnter your answer: ";
  int i;
  int j = 1;
  std::cin >> i;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  if (i == 1 || i == 4 || i == 2) {
    std::cout << "Sorry, the correct answer is a hat. You lose 3 "
                 "intelligence points."
              << '\n';
    j = 0;
  } else {
    std::cout << "\nThat's correct! Dr. Ku let you cut through his office. Steps to take decreased by 2." << '\n';
  }

  return j;
}

int specialevent(void) {
  std::cout << "\nLucky you! Choose your free award! " << '\n';
  std::cout << "\n\t\t 1) +3 Intelligence" << '\n';
  std::cout << "\n\t\t 2) +3 Minutes" << '\n';
  std::cout << "\n\t\t 3) +3 Coins" << '\n';
  std::cout << "\nEnter your choice: ";
  int j;
  std::cin >> j;

  return j;
}
