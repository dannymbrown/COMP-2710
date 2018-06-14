/**
@file   menu.cpp

@author Danny Brown (dmb0057)
@version 04-02-2018 15:31

@section DESCRIPTION

Handles menus and user input errors. Used in main.cpp.

*/


#include "system.cpp"
#include <iostream>
#include <fstream>

using namespace std;

/**
@brief Menu class - handles user input.

*/
class Menu {
private:
  int input;
  System sys;

public:

  /**
  @brief gets user input.

  @param none.
  @return void.
  */
  int getMenuInput(void) {
    std::cin >> input;
    return input;
  }

  /**
  @brief In game menu.

  @param none.
  @return void.
  */
  void gamemenu(void) {
    sys.start();
    sys.viewcontrols();

    bool end = false;
    do {
      if (sys.getstepstotake() <= 0) {
        std::cout << "\nWinner Winner, Chicken Dinner!" << '\n';
        std::cout << "\nYour Score: \n" <<  sys.getscore() << '\n';
        startmenu();
      }
      if (sys.checkparams() == 1) {
        std::cout << "\nINTELLIGENCE HAS FALLEN TO ZERO. YOU DIE." << '\n';
      } else if (sys.checkparams() == 2) {
        std::cout << "\nTIME HAS FALLEN TO ZERO. YOU DIE." << '\n';
      } else if (sys.checkparams() == 3) {
        std::cout << "\nCOINS HAS FALLEN TO ZERO. YOU DIE." << '\n';
      }
      if (!end) {
        std::cout << "\nPlease choose an option: ";
        switch (getMenuInput()) {
          case 1:
          sys.move(); //move forward
          break;
          case 2:
          sys.read(); //read map
          break;
          case 3:
          sys.search(); //search pockets
          break;
          case 4:
          sys.viewcharacter(); //view stats
          break;
          case 5:
          sys.viewcontrols(); //view controls
          break;
          case 6:
          std::cout << "\n\t\tThank you for playing! Goodbye :D" << '\n';
          exit(EXIT_SUCCESS);
          default:
          std::cout << "\n\t\tHmm, I don't think that's an option. Try again."
          << '\n';
        }
      }
    } while (!end);
  }

  /**
  @brief Program start menu

  @param none
  @return void
  */
  void startmenu() {
    std::cout << "1) Start a New Game of Shelby Center and Dragons!" << '\n';
    std::cout << "2) View top 10 High Scores" << '\n';
    std::cout << "3) Quit" << '\n';
    bool end = false;
    do {
      std::cout << "\nPlease choose an option: ";
      switch (getMenuInput()) {
        case 1:
        gamemenu();
        break;
        case 2:
        break;
        case 3:
        std::cout << "\n\t\tThank you for playing! Goodbye :D" << '\n';
        exit(EXIT_SUCCESS);
        default:
        std::cout << "\n\t\tHmm, I don't think that's an option. Try again."
        << '\n';
      }
    } while (!end);
  }
};
