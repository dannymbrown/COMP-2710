/**
hw1.cpp

@author Danny Brown (dmb0057)
@version 01-24-2018

No outside resources were used for this assignment with the exception of
the instructor's provided handout.

Description: This program provides a numerical value representing
how much diet soda it is possible to drink without dying as a result.

To compile, use g++ in Linux environment.
*/


#include <iostream>

using namespace std;

const float SWEETENER_IN_SODA = 0.001; //the amount of sweetener in a standard soda.

/**
Prints the welcome header.

@param none.
@return void.
*/
void printWelcome() {
  std::cout << "======================================================================\n";
  std::cout << "\t\t\t\tWelcome!" << '\n';
  std::cout << "======================================================================\n" << '\n';
}

/**
Returns amount of sweetener to kill a mouse to be used in calculate().

@param none.
@return amount of sweetener to kill a mouse.
*/
float getSweetenerToKill() {
  std::cout << "\nWhat is the amount of artificial sweetener needed to kill a mouse? ";
  float sweetenertokill;
  std::cin >> sweetenertokill;

  return sweetenertokill;
}

/**
Returns mouse weight to be used in calculate().

@param none.
@return current weight of mouse.
*/
float getWeightOfMouse() {
  float weightOfMouse;
  std::cout << "\nWhat is the the weight of the mouse? ";
  std::cin >> weightOfMouse;

  return weightOfMouse;
}

/**
Returns desired weight to be used in calculate().

@param none.
@return desired weight of the user after dieting.
*/
float getDesiredWeight() {
  float desiredWeight;
  std::cout << "\nWhat is your desired weight after dieting? ";
  std::cin >> desiredWeight;

  return desiredWeight;
}

/**
Caclculates and prints result of user input.

@param desiredWeight the desired weight of the user after dieting.
@param weightOfMouse the weighfloatf the mouse.
@param sweetenertoKill the amount of sweetener to kill a mouse.
@return void.
*/
void calculate(float desiredWeight, float weightOfMouse, float sweetenertokill) {
  float result = ((desiredWeight/weightOfMouse) * sweetenertokill)/SWEETENER_IN_SODA;
  std::cout << "\nYou can drink " <<  result << " diet sodas without dying." << '\n';
}

/**
Recalculates or terminates program based on user input.

@param none.
@return void.
*/
void recalculate() {
  char input;
  bool terminated = false;
  while (terminated == false) {
    std::cout << "\n\t\t\tWould you like to recalculate (y/n)? ";
    std::cin >> input;
    switch (input) {
      case 'y':
      calculate(getDesiredWeight(), getWeightOfMouse(), getSweetenerToKill());
      break;
      case 'n':
      terminated = true;
      break;
      default:
      std::cout << "\nError: Input must be y or n" << '\n';
      break;
    }
  }
  std::cout << "\nHave a nice day!" << '\n';
}

/**
Program operations.

@param none.
@return 0.
*/
int main() {
  printWelcome();
  calculate(getDesiredWeight(), getWeightOfMouse(), getSweetenerToKill());
  recalculate();

  return 0;
}
