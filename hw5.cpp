/**
@file   hw5.cpp

@author Danny Brown (dmb0057)
@version 03-16-2018 22:35

@section DESCRIPTION

The program first allows players to create their trivia questions and answers.
Multiple questions are organized and managed using a linked data structure.
Then, the program asks a question to the player, input the player’s answer,
and checks if the player’s answer matches the actual answer.
If so, the player is awarded points for that question.If the player enters the
wrong answer, the program displays the correct answer. When all questions have
been asked, the program displays the total points that the player has won.

Limited outside resources were used and are documented where relevant as line
comments.

To compile, you will need to use g++ in a Linux terminal with C++11.
i.e. "g++ -o hw4 hw4.cpp -std=c++0x" or "g++ -o hw4 hw4.cpp -std=c++11".
note: I used the former to compile my source code and it worked as desired.

*/

#define UNIT_TESTING // comment out this line for release version
#ifdef UNIT_TESTING

//------------------------------------------------------------------------------
//--------------------------------Debug Version---------------------------------
//------------------------------------------------------------------------------

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// -----------------------Function Prototypes-------------------------
struct TriviaNode;
// Trivia structure
void initialize(TriviaNode *&head, TriviaNode *&last);
// Input: (1) Head of Trivia linked list
//        (2) Tail of Trivia  linked list
// Output: void.
void addNode(TriviaNode *&head, TriviaNode *&last);
// Input: (1) Head of Trivia linked list
//        (2) Tail of Trivia  linked list
// Output: void.
void playgame(TriviaNode *current);
// Input: (1) Current node of Trivia linked list (i.e. head)
// Output: void.

struct TriviaNode {
  std::string setquestion;
  std::string setanswer;
  int setpoints;
  int setindex;
  TriviaNode *next;
};

/**
@brief Hard codes instances of the the TriviaNode structure.

@param head the head of the Trivia linked list.
@param last the tail of the Trivia linked list.
@return void.
*/
void initialize(TriviaNode *&head, TriviaNode *&last) {
  TriviaNode *n1 = new TriviaNode;
  TriviaNode *n2 = new TriviaNode;
  TriviaNode *n3 = new TriviaNode;

  head = n1;
  n1->next = n2;
  n1->setquestion =
      "How long was the shortest war on record? (Hint: how many minutes)?";
  n1->setanswer = "38";
  n1->setpoints = 100;

  n2->next = n3;
  n2->setquestion = "Question: What was Bank of America's original name? "
                    "(Hint: Bank of Italy or Bank of Germany)";
  n2->setanswer = "Bank of Italy";
  n2->setpoints = 50;

  n3->next = NULL;
  last = n3;
  n3->setquestion = "Question: What is the best-selling video game of all "
                    "time? (Hint: Minecraft or Tetris)?";
  n3->setanswer = "Tetris";
  n3->setpoints = 20;
}

/**
@brief Adds a user generated TriviaNode structure to the end of the TriviaNode
linked list. Used in main().

@param head the head of the Trivia linked list.
@param last the tail of the Trivia linked list.
@return void.
*/
void addNode(TriviaNode *&head, TriviaNode *&last) {
  TriviaNode *n = new TriviaNode;
  std::string question;
  std::string answer;
  int points;
  while (question.empty()) {
    std::cout << "Enter a question: ";
    std::getline(std::cin, question);
    if (question.empty()) {
      std::cerr << "Warning - The number of trivia to be asked must equal to "
                   "or larger than 1."
                << '\n';
    }
  }
  n->setquestion = question;
  std::cout << "Enter an answer: ";
  std::getline(std::cin, answer);
  n->setanswer = answer;
  std::cout << "Enter award points: ";
  std::cin >> points;
  // stackoverflow.com/questions/18728754/checking-input-value-is-an-integer
  while (std::cin.fail()) {
    std::cout << "Input must be an integer" << '\n';
    std::cout << "Enter award points: ";
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> points;
  }
  n->next = NULL;
  last->next = n;
  last = n;
}

/**
@brief Bulk of program operations. Asks a question to the player, inputs the
player’s answer, and checsk if the player’s answer matches the actual answer. If
so, the player is awarded the points for that question. If the player enters the
wrong answer, the program displays the correct answer. Used in main().

@param *current node to begin traversal of linked list.
@return void.
*/
void playgame(TriviaNode *current) {
  int total = 0;
  while (current != NULL) {
    std::cout << '\n' << current->setquestion << '\n';
    std::cout << "Answer: ";
    string response;
    getline(cin, response);
    std::cin.ignore(); // http://www.cplusplus.com
    if (response == current->setanswer) {
      std::cout << "Your answer is correct. You receive " << current->setpoints
                << " points." << '\n';
      total += current->setpoints;
    } else {
      std::cout << "Your answer is wrong. The correct answer is "
                << current->setanswer << '\n';
    }
    std::cout << "Your total points: " << total << '\n';
    current = current->next;
  }
  std::cout << "*** Thank you for playing the trivia quiz game. Goodbye! ***"
            << '\n';
}

/**
@brief Test driver for functions playgame() and addNode().

*/
class TestDriver {

public:
  /**
  @brief Unit Test Case 1.1: Ask no questions. The program should give a warning
  message.

  @param head the head of the Trivia linked list.
  @param last the tail of the Trivia linked list.
  @return int (1) if passed, (0) otherwise.
  */
  int test_addNode1(TriviaNode *&head, TriviaNode *&last) {
    int result = 0;
    std::string question;
    while (question.empty()) {
      std::cout << "Enter a question: ";
      std::getline(std::cin, question);
      question.clear(); // Incase user enters a non empty string, the string is
                        // emptied for testing purposes
      if (question.empty()) {
        std::cerr << "Warning - The number of trivia to be asked must equal to "
                     "or larger than 1."
                  << '\n';
        result = 1;
        break;
      }
    }
    return result;
  }

  /**
  @brief Unit Test Case 2.1: Ask 1 question in the linked list. The tester
  enters an incorrect answer.
  
  @param *current node to begin traversal of linked list.
  @return void.
  */
  int test_playgame1(TriviaNode *current) {
    int result = 0;
    std::cout << '\n' << current->setquestion << '\n';
    std::cout << "Answer: ";
    string response;
    getline(cin, response);
    std::cin.ignore(); // http://www.cplusplus.com
    if (response != current->setanswer) {
      result = 1;
    } else {
      std::cout << "Warning - Tester Must Enter Incorrect Answer" << '\n';
      test_playgame1(current);
    }
    return result;
  }

  /**
  @brief Unit Test Case 2.2: Ask 1 question in the linked list. The tester
  enters a correct answer.
  
  @param *current node to begin traversal of linked list.
  @return void.
  */
  int test_playgame2(TriviaNode *current) {
    int result = 0;
    std::cout << '\n' << current->setquestion << '\n';
    std::cout << "Answer: ";
    string response;
    getline(cin, response);
    std::cin.ignore(); // http://www.cplusplus.com
    if (response == current->setanswer) {
      result = 1;
    } else {
      std::cout << "Warning - Tester Must Enter Correct Answer" << '\n';
      test_playgame2(current);
    }
    return result;
  }

  /**
  @brief Unit Test Case 3: Ask the last trivia in the linked list.
  
  @param *current node to begin traversal of linked list.
  @return void.
  */
  int test_playgame3(TriviaNode *current) {
    std::cout << '\n' << current->setquestion << '\n';
    std::cout << "Answer: ";
    string response;
    getline(cin, response);
    std::cin.ignore(); // http://www.cplusplus.com
    if (response == current->setanswer) {
      std::cout << "Your answer is correct. You receive " << current->setpoints
                << " points." << '\n';
    } else {
      std::cout << "Your answer is wrong. The correct answer is "
                << current->setanswer << '\n';
    }
    std::cout << "Question asked and answered with success." << '\n';
  }
};

/**
@brief Program Ops.

@param none.
@return int.
*/
int main(int argc, char const *argv[]) {
  TestDriver test;
  TriviaNode *head;
  TriviaNode *last;
  initialize(head, last);
  std::cout << "*** This is a debug version ***" << '\n';
  std::cout << "Unit Test Case 1: Ask no questions. The program should give a "
               "warning message. *Note* String is automatically emptied."
            << '\n';
  assert(test.test_addNode1(head, last) == 1);
  std::cout << "Case 1 passed..." << '\n';
  std::cout << "\nUnit Test Case 2.1: Ask first question in list. The "
               "tester\nenters an incorrect answer";
  assert(test.test_playgame1(head) == 1);
  std::cout << "Case 2.1 passed..." << '\n';
  std::cout << "\nUnit Test Case 2.2: Ask 1 question in the linked list. The "
               "tester\nenters a correct answer."
            << '\n';
  assert(test.test_playgame2(last) == 1);
  std::cout << "Case 2.2 passed..." << '\n';
  std::cout << "Unit Test Case 3: Ask the last trivia in the linked list."
            << '\n';
  test.test_playgame3(last);
  std::cout << "\n*** End of the Debug Version ***" << '\n';
  return 0;
}

//------------------------------------------------------------------------------
//--------------------------------Release Version-------------------------------
//------------------------------------------------------------------------------

#else

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

// -----------------------Function Prototypes-------------------------
struct TriviaNode;
// Trivia structure
void initialize(TriviaNode *&head, TriviaNode *&last);
// Input: (1) Head of Trivia linked list
//        (2) Tail of Trivia  linked list
// Output: void.
void addNode(TriviaNode *&head, TriviaNode *&last);
// Input: (1) Head of Trivia linked list
//        (2) Tail of Trivia  linked list
// Output: void.
void playgame(TriviaNode *current);
// Input: (1) Current node of Trivia linked list (i.e. head)
// Output: void.

/**
TriviaNode Structure
*/
struct TriviaNode {
  std::string setquestion;
  std::string setanswer;
  int setpoints;
  int setindex;
  TriviaNode *next;
};

/**
@brief Hard codes instances of the the TriviaNode structure.

@param head the head of the Trivia linked list.
@param last the tail of the Trivia linked list.
@return void.
*/
void initialize(TriviaNode *&head, TriviaNode *&last) {
  TriviaNode *n1 = new TriviaNode;
  TriviaNode *n2 = new TriviaNode;
  TriviaNode *n3 = new TriviaNode;

  head = n1;
  n1->next = n2;
  n1->setquestion =
      "How long was the shortest war on record? (Hint: how many minutes)?";
  n1->setanswer = "38";
  n1->setpoints = 100;

  n2->next = n3;
  n2->setquestion = "Question: What was Bank of America's original name? "
                    "(Hint: Bank of Italy or Bank of Germany)";
  n2->setanswer = "Bank of Italy";
  n2->setpoints = 50;

  n3->next = NULL;
  last = n3;
  n3->setquestion = "Question: What is the best-selling video game of all "
                    "time? (Hint: Minecraft or Tetris)?";
  n3->setanswer = "Tetris";
  n3->setpoints = 20;
}

/**
@brief Adds a user generated TriviaNode structure to the end of the TriviaNode
linked list. Used in main().

@param head the head of the Trivia linked list.
@param last the tail of the Trivia linked list.
@return void.
*/
void addNode(TriviaNode *&head, TriviaNode *&last) {
  TriviaNode *n = new TriviaNode;
  std::string question;
  std::string answer;
  int points;
  while (question.empty()) {
    std::cout << "Enter a question: ";
    std::getline(std::cin, question);
    if (question.empty()) {
      std::cerr << "Warning - The number of trivia to be asked must equal to "
                   "or larger than 1."
                << '\n';
    }
  }
  n->setquestion = question;
  std::cout << "Enter an answer: ";
  std::getline(std::cin, answer);
  n->setanswer = answer;
  std::cout << "Enter award points: ";
  std::cin >> points;
  // stackoverflow.com/questions/18728754/checking-input-value-is-an-integer
  while (std::cin.fail()) {
    std::cout << "Input must be an integer" << '\n';
    std::cout << "Enter award points: ";
    std::cin.clear();
    std::cin.ignore(256, '\n');
    std::cin >> points;
  }
  n->setpoints = points;
  n->next = NULL;
  last->next = n;
  last = n;
}

/**
@brief Bulk of program operations. Asks a question to the player, inputs the
player’s answer, and checsk if the player’s answer matches the actual answer. If
so, the player is awarded the points for that question. If the player enters the
wrong answer, the program displays the correct answer. Used in main().

@param *current node to begin traversal of linked list.
@return void.
*/
void playgame(TriviaNode *current) {
  int total = 0;
  while (current != NULL) {
    std::cout << '\n' << current->setquestion << '\n';
    std::cout << "Answer: ";
    string response;
    getline(cin, response);
    std::cin.ignore(); // http://www.cplusplus.com
    if (response == current->setanswer) {
      std::cout << "Your answer is correct. You receive " << current->setpoints
                << " points." << '\n';
      total += current->setpoints;
    } else {
      std::cout << "Your answer is wrong. The correct answer is "
                << current->setanswer << '\n';
    }
    std::cout << "Your total points: " << total << '\n';
    current = current->next;
  }
}

/**
@brief Program Ops.

@param none.
@return int.
*/
int main(int argc, char const *argv[]) {
  std::cout << "*** Welcome to Danny's trivia quiz game ***" << '\n';
  TriviaNode *head;
  TriviaNode *last;
  initialize(head, last);
  addNode(head, last);
  std::string input;
  bool invalid = true;
  do {
    std::cout << "Continue? (Yes/No): ";
    std::cin >> input;
    std::cin.ignore();
    if (input.compare("yes") == 0 || input.compare("Yes") == 0) {
      addNode(head, last);
    } else if (input.compare("no") == 0 || input.compare("No") == 0) {
      invalid = false;
    } else {
      std::cout << "Input must be 'Yes' or 'No'" << '\n';
    }
  } while (invalid);
  playgame(head);
  std::cout
      << "\n\n*** Thank you for playing the trivia quiz game. Goodbye! ***"
      << '\n';
  return 0;
}

#endif
