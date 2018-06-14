/**
 *   @file   hw3.cpp
 *
 *   @author Danny Brown (dmb0057)
 *   @version 02-19-2018 08:59
 *
 *   @section DESCRIPTION
 *
 *   This program simulates a duel between three men using two
 *   different strategies.
 *
 *   No outside resources were used for the creation of this program save
 *   for the instructor provided handout. Please do note that there may be
 *   variations in cout statements as I did copy provided code from the handout
 *   itself.
 *
 *   To compile, use g++ in Linux environment.
 */

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

const int NUMBER_OF_DUELS = 10000; // The total number of duels in simulation
const float BOB_HITRATE = 50;      // Bob's percentage of shots on target
const float AARON_HITRATE = 33.3;  // Aaron's percentage of shots on target
const float CHARLIE_HITRATE = 100; // Charlie's percentage of shots on target

// prototypes
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive);
// Input: A_alive indicates whether Aaron is alive
//        B_alive indicates whether Bob is alive
//        C_alive indicates whether Charlie is alive
// Return: true if at least two are alive
//         otherwise return false

void Aaron_shoots1(bool &B_alive, bool &C_alive);
// Input: A_alive indicates whether Aaron is alive
//        B_alive indicates whether Bob is alive
// Return: void

void Aaron_shoots2(bool &B_alive, bool &C_alive);
// Input: B_alive indicates whether Bob is alive
//        C_alive indicates whether Charlie is alive
// Return: void

void Bob_shoots(bool &A_alive, bool &C_alive);
// Input: A_alive indicates whether Aaron is alive
//        C_alive indicates whether Charlie is alive
// Return: void

void Charlie_shoots(bool &A_alive, bool &B_alive);
// Input: A_alive indicates whether Aaron is alive
//        B_alive indicates whether Bob is alive
// Return: void

/**
Helper function used to pause console.

@param none.
@return void.
*/
void pause() {
  cout << "Press any key to continue...";
  cin.ignore().get();
}

/**
@brief Determines, true or false, if their are at least two shooters still
       alive.

@param A_alive indicates whether Aaron is alive.
       B_alive indicates whether Bob is alive.
       C_alive indicates whether Charlie is alive.
@return bool.
*/
bool at_least_two_alive(bool A_alive, bool B_alive, bool C_alive) {
  bool at_least_two_alive = false;
  if (A_alive) {
    if (B_alive || C_alive) {
      at_least_two_alive = true;
    }
  } else if (B_alive) {
    if (A_alive || C_alive) {
      at_least_two_alive = true;
    }
  } else if (C_alive) {
    if (B_alive || A_alive) {
      at_least_two_alive = true;
    }
  }
  return at_least_two_alive;
}

/**
@brief First strategy for Aaron in the duel simulation.

@param B_alive indicates whether Bob is alive.
       C_alive indicates whether Charlie is alive.
@return void.
*/
void Aaron_shoots1(bool &B_alive, bool &C_alive) {
  int shoot_target_result = rand() % 100;
  if (shoot_target_result <= AARON_HITRATE) {
    if (C_alive) {
      C_alive = false;
    } else {
      B_alive = false;
    }
  }
}

/**
@brief Second strategy for Aaron in the duel simulation.
       In this strategy the first shot is intentionally missed.

@param B_alive indicates whether Bob is alive.
       C_alive indicates whether Charlie is alive.
@return void.
*/
void Aaron_shoots2(bool &B_alive, bool &C_alive) {
  int shoot_target_result = rand() % 100;
  if (B_alive && C_alive) {
    assert(C_alive);
  } else if (shoot_target_result <= AARON_HITRATE) {
    if (C_alive) {
      C_alive = false;
    } else {
      B_alive = false;
    }
  }
}

/**
@brief Function for Bob's shot.

@param A_alive indicates whether Aaron is alive.
       C_alive indicates whether Charlie is alive.
@return void.
*/
void Bob_shoots(bool &A_alive, bool &C_alive) {
  int shoot_target_result = rand() % 100;
  if (shoot_target_result <= BOB_HITRATE) {
    if (C_alive) {
      C_alive = false;
    } else {
      A_alive = false;
    }
  }
}

/**
@brief Function for Charlie's shot.

@param A_alive indicates whether Aaron is alive.
       B_alive indicates whether Bob is alive.
@return void.
*/
void Charlie_shoots(bool &A_alive, bool &B_alive) {
  if (B_alive) {
    B_alive = false;
  } else {
    A_alive = false;
  }
}

/**
@brief Class containing all unit tests.
       Mainly for organization.

*/
class UnitTest {
public:
  /**
  @brief Test driver for at_least_two_alive().

  @param none.
  @return void.
  */
  void test_at_least_two_alive() {
    std::cout << "Unit Testing 1: Function at_least_two_alive()" << '\n';
    std::cout << "Case 1: Aaron alive, Bob alive, Charlie alive" << '\n';
    assert(true == at_least_two_alive(true, true, true));
    cout << "Case passed ...\n";
    cout << "Case 2: Aaron dead, Bob alive, Charlie alive\n";
    assert(true == at_least_two_alive(false, true, true));
    cout << "Case passed ...\n";
    cout << "Case 3: Aaron alive, Bob dead, Charlie alive\n";
    assert(true == at_least_two_alive(true, false, true));
    cout << "Case passed ...\n";
    cout << "Case 4: Aaron alive, Bob alive, Charlie dead\n";
    assert(true == at_least_two_alive(true, true, false));
    cout << "Case passed ...\n";
    cout << "Case 5: Aaron dead, Bob dead, Charlie alive\n";
    assert(false == at_least_two_alive(false, false, true));
    cout << "Case passed ...\n";
    cout << "Case 6: Aaron dead, Bob alive, Charlie dead\n";
    assert(false == at_least_two_alive(false, true, false));
    cout << "Case passed ...\n";
    cout << "Case 7: Aaron alive, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(true, false, false));
    cout << "Case passed ...\n";
    cout << "Case 8: Aaron dead, Bob dead, Charlie dead\n";
    assert(false == at_least_two_alive(false, false, false));
    cout << "Case passed ...\n";
    pause();
  }

  /**
  @brief Test driver for Aaron_shoots1().

  @param none.
  @return void.
  */
  void test_Aaron_shoots1() {
    bool B_alive;
    bool C_alive;
    cout << "\nUnit Testing 2: Function Aaron_shoots1(Bob_alive, "
            "Charlie_alive)\n";
    cout << "Case 1:\tBob alive, Charlie alive\n\tAaron is shooting at "
            "Charlie\n";
    B_alive, C_alive = true;
    Aaron_shoots1(B_alive, C_alive);
    if (C_alive == false) {
      std::cout << "\tCharlie is dead." << '\n';
    } else {
      std::cout << "\tAaron misses." << '\n';
    }
    cout
        << "Case 2:\tBob dead, Charlie alive\n\tAaron is shooting at Charlie\n";
    B_alive = false;
    C_alive = true;
    Aaron_shoots1(B_alive, C_alive);
    if (C_alive == false) {
      std::cout << "\tCharlie is dead." << '\n';
    } else {
      std::cout << "\tAaron misses." << '\n';
    }
    cout << "Case 3:\tBob alive, Charlie dead\n\tAaron is shooting at Bob\n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots1(B_alive, C_alive);
    if (C_alive) {
      std::cerr << "Unit Test 2, Case 3: Failed, Charlie is alive." << '\n';
    } else if (B_alive) {
      std::cout << "\tAaron misses." << '\n';
    } else {
      std::cout << "\tBob is dead." << '\n';
    }
    pause();
  }

  /**
  @brief Test driver for test_Aaron_shoots2().

  @param none.
  @return void.
  */
  void test_Aaron_shoots2() {
    bool B_alive, C_alive;
    cout << "\nUnit Testing 5: Function Aaron_shoots2(Bob_alive, "
            "Charlie_alive)\n";
    cout << "Case 1:\tAaron alive, Bob alive\n\tAaron intentionally misses his "
            "first shot\n";
    B_alive = C_alive = true;
    Aaron_shoots2(B_alive, C_alive);
    if (B_alive && C_alive) {
      std::cout << "\tBoth Bob and Charlie are alive." << '\n';
    } else if (C_alive == false) {
      std::cout << "\tCharlie is dead." << '\n';
    }
    cout
        << "Case 2:\tBob dead, Charlie alive\n\tAaron is shooting at Charlie\n";
    B_alive = false;
    C_alive = true;
    Aaron_shoots2(B_alive, C_alive);
    if (B_alive && C_alive) {
      std::cerr
          << "\tUnit Test 5, Case 2: Failed, both Bob and Charlie are alive."
          << '\n';
    } else if (C_alive == false) {
      std::cout << "\tCharlie is dead." << '\n';
    } else {
      std::cout << "\tAaron missed." << '\n';
    }

    cout << "Case 3:\tBob alive, Charlie dead\n\tAaron is shooting at Bob\n";
    B_alive = true;
    C_alive = false;
    Aaron_shoots2(B_alive, C_alive);
    if (B_alive && C_alive) {
      std::cerr
          << "\tUnit Test 5, Case 3: Failed, both Bob and Charlie are alive."
          << '\n';
    } else if (C_alive) {
      std::cerr << "\tUnit Test 5, Case 3: Failed, Charlie is alive." << '\n';
    } else if (B_alive) {
      std::cout << "\tAaron missed." << '\n';
    } else {
      std::cout << "\tBob is dead." << '\n';
    }
    pause();
  }

  /**
  @brief Test driver for Bob_shoots().

  @param none.
  @return void.
  */
  void test_Bob_shoots() {
    bool A_alive;
    bool C_alive;
    cout << "\nUnit Testing 3: Function Bob_shoots(Aaron_alive, "
            "Charlie_alive)\n";
    cout << "Case 1:\tAaron alive, Charlie alive\n\tBob is shooting at "
            "Charlie\n";
    A_alive, C_alive = true;
    Bob_shoots(A_alive, C_alive);
    if (C_alive == false) {
      std::cout << "\tCharlie is dead." << '\n';
    } else {
      std::cout << "\tBob misses." << '\n';
    }
    cout
        << "Case 2:\tAaron dead, Charlie alive\n\tBob is shooting at Charlie\n";
    A_alive = false;
    C_alive = true;
    Bob_shoots(A_alive, C_alive);
    if (C_alive == false) {
      std::cout << "\tCharlie is dead." << '\n';
    } else if (A_alive) {
      std::cerr << "\tUnit Test 3, Case 2: Failed, Aaron is alive." << '\n';
    } else {
      std::cout << "\tBob misses." << '\n';
    }
    cout << "Case 3:\tAaron alive, Charlie dead\n\tBob is shooting at Aaron\n";
    A_alive = true;
    C_alive = false;
    Bob_shoots(A_alive, C_alive);
    if (A_alive) {
      std::cout << "\tBob misses." << '\n';
    } else if (C_alive) {
      std::cerr << "\tUnit Test 3, Case 3: Failed, Charlie is alive." << '\n';
    } else {
      std::cout << "\tAaron is dead." << '\n';
    }
    pause();
  }

  /**
  @brief Test driver for Charlie_shoots().

  @param none.
  @return void.
  */
  void test_Charlie_shoots() {
    bool A_alive;
    bool B_alive;
    cout << "\nUnit Testing 4: Function Charlie_shoots(Aaron_alive, "
            "Charlie_alive)\n";
    cout << "Case 1:\tAaron alive, Bob alive\n\tCharlie is shooting at Bob\n";
    A_alive, B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    if (B_alive) {
      std::cerr << "\tUnit Test 4, Case 1: Failed, Charlie missed." << '\n';
    } else {
      std::cout << "\tBob is dead." << '\n';
    }
    cout << "Case 2:\tAaron dead, Bob alive\n\tCharlie is shooting at Bob\n";
    A_alive, B_alive = true;
    Charlie_shoots(A_alive, B_alive);
    if (A_alive) {
      std::cerr << "\tUnit Test 4, Case 2: Failed, Aaron is alive." << '\n';
    } else if (B_alive) {
      std::cerr << "\tUnit Test 4, Case 2: Failed, Charlie missed." << '\n';
    } else {
      std::cout << "\tBob is dead." << '\n';
    }
    cout << "Case 3:\tAaron alive, Bob dead\n\tCharlie is shooting at Aaron\n";
    A_alive = true;
    B_alive = false;
    Charlie_shoots(A_alive, B_alive);
    if (A_alive) {
      std::cerr << "\tUnit Test 4, Case 2: Failed, Aaron is alive." << '\n';
    } else if (B_alive) {
      std::cerr << "\tUnit Test 4, Case 2: Failed, Bob is alive." << '\n';
    } else {
      std::cout << "\tAaron is dead." << '\n';
    }
    pause();
  }
};

/**
@brief Function that simulates duel with Aaron using his first strategy.

@param none.
@return Aarons_wins the number of wins by Aaron of type float.
*/
float sim_strategy1() {
  srand(time(0));
  std::cout << "\nReady to test strategy 1 (run 10000 times):" << '\n';
  pause();
  std::cout << "...\n...\n...\n" << '\n';

  float Aarons_wins = 0;  // Number of Aaron's wins
  float Bob_wins = 0;     // Number of Bob's wins
  float Charlie_wins = 0; // Number of Charlie's wins

  for (int i = 0; i < NUMBER_OF_DUELS; i++) {
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;

    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
      if (A_alive) {
        Aaron_shoots1(B_alive, C_alive);
      }
      if (B_alive) {
        Bob_shoots(A_alive, C_alive);
      }
      if (C_alive) {
        Charlie_shoots(A_alive, B_alive);
      }
    }
    if (A_alive) {
      Aarons_wins++;
    }
    if (B_alive) {
      Bob_wins++;
    }
    if (C_alive) {
      Charlie_wins++;
    }
  }
  std::cout << "Aaron won " << Aarons_wins << "\\" << NUMBER_OF_DUELS << " or "
            << ((Aarons_wins / NUMBER_OF_DUELS) * 100) << "%" << '\n';
  std::cout << "Bob won " << Bob_wins << "\\" << NUMBER_OF_DUELS << " or "
            << ((Bob_wins / NUMBER_OF_DUELS) * 100) << "%" << '\n';
  std::cout << "Charlie won " << Charlie_wins << "\\" << NUMBER_OF_DUELS
            << " or " << ((Charlie_wins / NUMBER_OF_DUELS) * 100) << "%"
            << "\n\n";

  return Aarons_wins;
}
/**
@brief Function that simulates duel with Aaron using his second strategy.

@param none.
@return Aarons_wins the number of wins by Aaron of type float.
*/
float sim_strategy2() {
  srand(time(0));
  std::cout << "Ready to test strategy 2 (run 10000 times):" << '\n';
  pause();
  std::cout << "...\n...\n...\n" << '\n';

  float Aarons_wins = 0;  // Number of Aaron's wins
  float Bob_wins = 0;     // Number of Bob's wins
  float Charlie_wins = 0; // Number of Charlie's wins

  for (int j = 0; j < NUMBER_OF_DUELS; j++) {
    bool A_alive = true;
    bool B_alive = true;
    bool C_alive = true;

    while (at_least_two_alive(A_alive, B_alive, C_alive)) {
      if (A_alive) {
        Aaron_shoots2(B_alive, C_alive);
      }
      if (B_alive) {
        Bob_shoots(A_alive, C_alive);
      }
      if (C_alive) {
        Charlie_shoots(A_alive, B_alive);
      }
    }
    if (A_alive) {
      Aarons_wins++;
    }
    if (B_alive) {
      Bob_wins++;
    }
    if (C_alive) {
      Charlie_wins++;
    }
  }
  std::cout << "Aaron won " << Aarons_wins << "\\" << NUMBER_OF_DUELS << " or "
            << ((Aarons_wins / NUMBER_OF_DUELS) * 100) << "%" << '\n';
  std::cout << "Bob won " << Bob_wins << "\\" << NUMBER_OF_DUELS << " or "
            << ((Bob_wins / NUMBER_OF_DUELS) * 100) << "%" << '\n';
  std::cout << "Charlie won " << Charlie_wins << "\\" << NUMBER_OF_DUELS
            << " or " << ((Charlie_wins / NUMBER_OF_DUELS) * 100) << "%"
            << '\n';

  return Aarons_wins;
}
/**
@brief Program operations.

@param none.
@return void.
*/
int main() {
  srand(time(0));
  std::cout << "*** Welcome to Danny's Duel Simulator ***" << '\n';
  /* Unit Testing - Comment out for release version */
  UnitTest unitTest;
  unitTest.test_at_least_two_alive();
  unitTest.test_Aaron_shoots1();
  unitTest.test_Bob_shoots();
  unitTest.test_Charlie_shoots();
  unitTest.test_Aaron_shoots2();
  /* --------------------------------------------- */
  sim_strategy1();
  sim_strategy2();
  if (sim_strategy1 > sim_strategy2) {
    std::cout << "\nStrategy 1 is better than strategy 2." << '\n';
  } else {
    std::cout << "\nStrategy 2 is better than strategy 1." << '\n';
  }

  return 0;
}
