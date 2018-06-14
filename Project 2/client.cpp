/**
@file   system.cpp

@author Danny Brown (dmb0057)
@version 04-28-2018 18:26

@section DESCRIPTION

This file contains all of the functions for client operations.

*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

class Client {
private:
  /* data */

public:
  void add_client(void) {
    std::string c_name, c_address, c_ssn, c_employer, c_income;
    std::cout << "Client name: ";
    getchar();
    std::getline(std::cin, c_name);
    std::cout << "Address: ";
    std::getline(std::cin, c_address);
    std::cout << "Social Security Number: ";
    std::getline(std::cin, c_ssn);
    std::cout << "Employer: ";
    std::getline(std::cin, c_employer);
    std::cout << "Income: ";
    std::getline(std::cin, c_income);
    std::ofstream file;
    file.open("./data/accounts/" + c_name + "_profile.txt");
    file << c_name << '\n'
         << c_address << '\n'
         << c_ssn << '\n'
         << c_employer << '\n'
         << c_income;
    file.close();
    std::cout << "A new client was added!" << '\n';
  }

  void add_account(void) {
    std::string client;
    std::cout << "Choose a client: ";
    getchar();
    getline(std::cin, client);
    std::string const file("./data/accounts/" + client + "_profile.txt");
    bool failed = !std::ifstream(file.c_str());
    if (failed) {
      std::cout << "Error - The client is not in the system! " << '\n';
      std::cout << "1) Choose new client\n2) Return to client "
                   "terminal";
      int input;
      do {
        std::cout << "\nPlease choose an option: ";
        std::cin >> input;
        switch (input) {
        case 1:
          add_account();
          break;
        case 2:
          return_to_menu();
          break;
        default:
          std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
          break;
        }
      } while (true);
    } else {
      std::string id, type, balance;
      std::ofstream file;
      std::cout << "Account Number: ";
      getline(std::cin, id); // account number
      std::cout << "Account Type: ";
      getline(std::cin, type); // account type (i.e. checking)
      std::cout << "Balance: ";
      getline(std::cin, balance); // account balance
      file.open("./data/accounts/" + client + "_accounts.txt");
      file << client << '\n' << id << ' ' << type << '\n' << balance;
      file.close();
      std::cout << "A new account was added for " << client << "!\n";
    }
  }
  int manage_information(void) {
    std::string client, c_name, c_address, c_ssn, c_employer, c_income;
    std::cout << "\nChoose a client: ";
    std::cin.ignore();
    getline(std::cin, client);
    std::ifstream read("./data/accounts/" + client + "_profile.txt");
    if (read.good()) {
      while (getline(read, c_name)) {
        getline(read, c_address);  // read client address
        getline(read, c_ssn);      // read client ssn
        getline(read, c_employer); // read client employer
        getline(read, c_income);   // read client income
        std::cout << c_name << '\n';
        std::cout << "Address: " << c_address << '\n';
        std::cout << "Social Security Number: " << c_ssn << '\n';
        std::cout << "Employer: " << c_employer << '\n';
        std::cout << "Income: " << c_income << '\n';
        std::cout << "Client " << client << "'s information will be updated..."
                  << '\n';
      }

      bool valid = false;
      int input;
      std::cout << "1) Confirm\n2) Cancel";
      do {
        std::cout << "\nPlease choose an option: ";
        std::cin >> input;
        switch (input) {
        case 1:
          goto edit_client;
          break;
        case 2:
          return 0;
          break;
        default:
          std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
          break;
        }
      } while (!valid);

    edit_client:
      std::string new_address, new_ssn, new_employer, new_income;
      std::string const file("./data/accounts/" + client + "_profile.txt");
      std::remove(file.c_str());

      std::cout << "Address: ";
      getchar();
      std::getline(std::cin, new_address);
      std::cout << "Social Security Number: ";
      std::getline(std::cin, new_ssn);
      std::cout << "Employer: ";
      std::getline(std::cin, new_employer);
      std::cout << "Income: ";
      std::getline(std::cin, new_income);
      std::ofstream new_file;
      new_file.open("./data/accounts/" + client + "_profile.txt");
      new_file << client << '\n'
               << new_address << '\n'
               << new_ssn << '\n'
               << new_employer << '\n'
               << new_income;
      new_file.close();
      std::cout << client << "'s information was updated!" << '\n';
    } else {
      read.clear();
      return -1;
    }

    return 1;
  }

  void manage_account(void) {
    std::string client, account_id;
    std::cout << "Choose a client: ";
    std::getline(std::cin, client);
    std::cout << "Which account will be managed? ";
    std::getline(std::cin, account_id);
    std::ifstream read("./data/accounts/" + client + "_accounts.txt");

    /* Worked tirelessly, but could not complete this function. I really did. */
  }

  void save(void) {
    std::cout
        << "Client and account information has been saved in data\\accounts "
        << '\n';
    /*I realized way too late that we had pre-defined file names. But for what
    it's worth, my solution works for the most part */
  }

  int return_to_menu(void) { return 1; }
};
