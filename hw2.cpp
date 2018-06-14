/**
hw2.cpp

@author Danny Brown (dmb0057)
@version 02-06-2018 19:43

Resources: https://www.investopedia.com

Description: This program provides a complete table of periodic loan payments,
showing the amount of principal and the amount of interest that comprise each
payment until the loan is paid off at the end of its term.

To compile, use g++ in Linux environment.
*/

#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

float monthlyPayments = 0; // value of monthly payments
float loanAmount = 0;      // total of desired loan
float interestRate = 0;    // interest rate

/**
Sets the loan amount.

@param none.
@return void.
*/
void setLoanAmount() {
  float loan = 0;
  std::cout << "Loan Amount: ";
  std::cin >> loan;
  if (loan <= 0) {
    std::cerr << "\n\t\t\tError:Loan amount must be greater than 0!" << '\n';
  } else {
    loanAmount = loan;
  }
}

/**
Sets the interest rate.

@param none.
@return void.
*/
void setRate() {
  float rate = 0;
  std::cout << "Interest Rate (% per year): ";
  std::cin >> rate;
  if (rate < 0) {
    std::cerr << "\n\t\t\tError:Rate must be 0 or positive!" << '\n';
  } else {
    interestRate = (rate / 100);
  }
}

/**
Sets the amount of monthly payments.

@param none.
@return void.
*/
void setMonthlyPayments() {
  float payments = 0;
  std::cout << "Monthly Payments: ";
  std::cin >> payments;
  if (payments <= 0) {
    std::cerr << "\n\t\t\tError:Integer must be greater than 0!" << '\n';
    setMonthlyPayments();
  } else if (payments != ceil(payments) || payments != floor(payments)) {
    std::cerr << "\n\t\t\tError:Length of loan must be a positive integer!"
              << '\n';
    setMonthlyPayments();
  } else {
    monthlyPayments = payments;
  }
}

/**
Prints the amortization table.

@param none.
@return void.
*/
void printTable() {
  cout.setf(ios::fixed);
  cout.setf(ios::showpoint);
  cout.precision(2);

  int numberOfMonths = 0;
  float iod = 0;          // Interest On Debt
  float principal = 0;    // Total principal paid
  float payment = 0;      // Total of payment
  float interestPaid = 0; // Total interest paid
  float balance = 0;      // Interest + initial loan

  balance = loanAmount;

  bool t = true;
  while (t == true) {

    iod = (balance * interestRate);
    if (monthlyPayments < iod) {
      std::cerr << "\nError: Current Monthly Payment Will Result In Infinite "
                   "Payment Plan! - Please Enter New Values. \n"
                << '\n';
      exit(1);
    }

    if (numberOfMonths == 0) {
      std::cout << "\n******************************************************"
                << '\n';
      std::cout << "\t\tAmortization Table" << '\n';
      std::cout << "******************************************************";
      std::cout << "\nMonth\tBalance Payment Rate        Interest Principal"
                << '\n';
    }

    if (balance == loanAmount) {
      std::cout << "\n"
                << numberOfMonths << "\t" << loanAmount
                << " N\\A N\\A N\\A         N\\A      N\\A"
                << "\n";
      numberOfMonths++;
    }

    balance = iod + balance;

    if (balance <= monthlyPayments) {
      payment = balance;
      principal = (balance - iod);
      std::cout << "\n"
                << numberOfMonths << "\t"
                << "$0.00"
                << " $" << payment << " " << (interestRate * 100)
                << "          $" << iod << "    $" << principal << '\n';
      numberOfMonths++;
      t = false;
    }

    else {

      payment = monthlyPayments;
      principal = (monthlyPayments - iod);
      std::cout << "\n"
                << numberOfMonths << "\t$" << (balance - monthlyPayments)
                << " $" << monthlyPayments << " " << (interestRate * 100)
                << "          $" << iod << "    $" << principal << '\n';
      numberOfMonths++;

      balance = balance - payment;
    }

    interestPaid += iod;
  }

  std::cout << "******************************************************\n\n";
  std::cout << "I takes " << (numberOfMonths - 1)
            << " months to pay off the loan.\n";
  std::cout << "Total interest paid is: " << interestPaid << "\n\n";
}

/**
Program operations.

@param none.
@return void.
*/
int main() {
  setLoanAmount();
  setRate();
  setMonthlyPayments();
  printTable();

  return 0;
}
