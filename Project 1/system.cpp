/**
@file   system.cpp

@author Danny Brown (dmb0057)
@version 04-02-2018 15:31

@section DESCRIPTION

Primary functions of the game. Used in menu.cpp.

*/

#include "event.cpp"
#include "user.cpp"
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

class System {

private:
  int intelligence = 0;
  int t = 0; // time since 'time' cause conflict with RNG
  int coins = 0;
  const int HALL_LENGTH = 20;
  int stepstotake = HALL_LENGTH;
  const int MAX_SIZE = 5;
  User u1;

public:

  int getscore() {
    int score = 0;

  }

  /**
  @brief Initilizes RNG, creates new user and enters the game.

  @param none.
  @return void.
  */
  void start(void) {
    srand(time(NULL)); // initialization of rand()

    int min = 15;
    int max = 25;
    int r1 = (min + (rand() % (int)(max - min + 1))); // intelligence
    int r2 = (min + (rand() % (int)(max - min + 1))); // time
    int r3 = (min + (rand() % (int)(max - min + 1))); // coins

    int steps_taken = 0;

    setuser(u1, getname(u1));
    std::cout << "\nEntering the Game...\n\n" << '\n';
    stepstotake = HALL_LENGTH;
    intelligence = r1;
    t = r2; // time
    coins = r3;

    viewcharacter();
  }

  /**
  @brief The 'view controls' player function.

  @param none.
  @return void.
  */
  void viewcontrols(void) {
    std::cout << "\n\t\t1) Move forward (takes time, could be risky...)" << '\n';
    std::cout << "\t\t2) Read floor plan (boost intelligence, takes time)"
    << '\n';
    std::cout << "\t\t3) Search for loose change (boost money, takes time)"
    << '\n';
    std::cout << "\t\t4) View character" << '\n';
    std::cout << "\t\t5) View controls" << '\n';
    std::cout << "\t\t6) Quit the game" << '\n';
  }

  /**
  @brief The 'view character' player function.

  @param none.
  @return void.
  */
  void viewcharacter(void) {
    std::cout << "\nYou have:" << '\n';

    std::cout << "\nintelligence: " << intelligence << endl;
    std::cout << "time: " << t << endl;
    std::cout << "coins: " << coins << endl;

    std::cout << "\nYou are " << stepstotake
    << " steps from the goal. Time left: " << t << '.' << '\n';
  }

  /**
  @brief Checks whether or not intelligence, time, or coins = 0;

  @param none.
  @return i indicating which value has fallen to 0
  */
  int checkparams(void) {
    int i = 0;
    if (intelligence <= 0) {
      i = 1;
    } else if (t <= 0) {
      i = 2;
    } else if (coins <= 0) {
      i = 3;
    }
    return i;
  }

  /**
  @brief the move function for the character

  @param none
  @return void
  */
  void move(void) {
    int rng = rand() % 100;
    if (rng <= 50) {
      std::cout << "You move forward one step and...\n\nNOTHING HAPPENS!"
      << '\n';
      t--;
      stepstotake--;
    }
    if ((rng >= 51) && (rng <= 56)) {
      std::cout << "Lucky you! You found 3 coins on the floor." << '\n';
      t--;
      stepstotake--;
    }
    if ((rng >= 57) && (rng <= 62)) {
      std::cout << "You encounter a friend. You loose 2 minutes of time"
      << '\n';
      t -= 2;
      stepstotake--;
    }
    if ((rng >= 63) && (rng <= 68)) {
      std::cout << "Looks like Dr. Cross needs you to grade some papers. You "
      "lose 3 minutes\nbut gain 5 coins."
      << '\n';
      t -= 3;
      stepstotake--;
    }
    if ((rng >= 69) && (rng <= 72)) {
      std::cout
      << "Oops, looks like you slipped a fell. Some money fell out as well."
      << '\n';
      t -= 2;
      coins -= 5;
      stepstotake--;
    }

    if ((rng >= 69) && (rng <= 76)) {
      int n;
      n = riddle1();
      if (n == 0) {
        intelligence -= 3;
      }
      t --;
      stepstotake--;
    }
    if ((rng >= 77) && (rng <= 80)) {
      std::cout << "Looks like like you've found a shortcut and saved some time"
      << '\n';
      t--;
      stepstotake -= 4;
    }
    if ((rng >= 80) && (rng <= 87)) {
      int n;
      n = riddle2();
      if (n == 0) {
        intelligence -= 3;
      }
      t -= 2;
      stepstotake--;
    }
    if ((rng >= 88) && (rng <= 95)) {
      int n;
      n = riddle3();
      if (n == 0) {
        intelligence -= 3;
        stepstotake--;
      } else {
        stepstotake -= 2;
      }
      t -= 1;
    }
    if ((rng >= 96) && (rng <= 99)) {
      int n;
      n = specialevent();
      if (n == 1) {
        intelligence += 3;
      } else if (n = 2) {
        t +=3 ;
      }
    }
    stepstotake--;
  }



  /**
  @brief Returns the number of steps until goal

  @param none.
  @return void.
  */
  int getstepstotake(void) { return stepstotake; }

  /**
  @brief The 'read map' player function.

  @param none.
  @return void.
  */
  void read(void) {
    std::cout << "\nYou take some time to view the floor plan." << '\n';
    intelligence += 3;
    t -= 2;
  }

  /**
  @brief The 'search pockets' player function.

  @param none.
  @return void.
  */
  void search(void) {
    std::cout << "\nYou take some time to search your pockets." << '\n';
    coins += 3;
    t -= 2;
  }

  int getScore(void) {
    int score = 0;
    score = (coins * t * intelligence);
    return score;
  }

  /**
  @brief Prints the top 5 scores

  @param none
  @return void
  */
  void displayTopScores(void) {
    std::cout << "The top 5 High Scores are: " << '\n';
  }
};
