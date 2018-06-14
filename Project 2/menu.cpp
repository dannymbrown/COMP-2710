/**
@file   menu.cpp

@author Danny Brown (dmb0057)
@version 04-28-2018 18:26

@section DESCRIPTION

This file contains all of the menus used in the program. In addition, it handles
user input mistakes when interacting with said menus.

*/

#include "client.cpp"
#include "system.cpp"
#include <cstdlib>
#include <iostream>
#include <string>

class Menu {
private:
  System sys;
  Client client;

public:
  void start_program(void) {
    std::string border =
        "===========================================================";
    std::cout << border << '\n';
    std::cout << "|      Welcome to the Auburn Branch of Tiger Bank!        |"
              << '\n';
    std::cout << border << '\n';
    std::cout << "1) Login" << '\n';
    std::cout << "2) Quit" << '\n';
    std::cout << "\n\tPlease choose an option: ";
    int input;
    do {
      std::cin >> input;
      switch (input) {
      case 1: // Login
        sys.login();
        sys.set_current_state(true);
        break;
      case 2: // Quit Terminal
        std::cout << "\n\t\t\tTerminal Closing" << '\n';
        exit(EXIT_SUCCESS);
        break;
      default: // Input Invalid
        std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
        break;
      }
    } while (!sys.get_current_state());
    if (sys.get_privileges() == "1") {
      system_admin_menu();
    } else if (sys.get_privileges() == "2") {
      branch_staff_menu();
    } else {
      std::cout << "Unknown Error" << '\n';
    }
  }

  void branch_staff_menu(void) {
    std::string border =
        "===========================================================";
    std::cout << border << '\n';
    std::cout << "|      Teller Terminal System - Branch Staff     |" << '\n';
    std::cout << border << '\n';
    std::cout << "1) Client and Account Management" << '\n';
    std::cout << "2) Add a branch staff member" << '\n';
    std::cout << "3) Delete a branch staff member" << '\n';
    std::cout << "4) Display branch staff" << '\n';
    std::cout << "5) Change password" << '\n';
    std::cout << "6) Exit" << '\n';
    std::cout << "\n\tPlease choose an option: ";
    int input;
    bool valid = false;
    do {
      std::cin >> input;
      switch (input) {
      case 1: // Client and Account Management
        client_manage_menu();
        break;
      case 2: // Add a branch staff member
        sys.add_member();
        branch_staff_menu();
        break;
      case 3: // Change password
        sys.change_password();
        branch_staff_menu();
        break;
      case 4: // Exit
        std::cout << "\n\t\t\tTerminal Closing" << '\n';
        exit(EXIT_SUCCESS);
        break;
      default: // Input Invalid
        std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
        branch_staff_menu();
        break;
      }
    } while (!valid);
  }

  void system_admin_menu(void) {
    std::string border =
        "===========================================================";
    std::cout << border << '\n';
    std::cout << "|      Teller Terminal System - System Administration     |"
              << '\n';
    std::cout << border << '\n';
    std::cout << "1) Client and Account Management" << '\n';
    std::cout << "2) Add a branch staff member" << '\n';
    std::cout << "3) Delete a branch staff member" << '\n';
    std::cout << "4) Display branch staff" << '\n';
    std::cout << "5) Change password" << '\n';
    std::cout << "6) Exit" << '\n';
    std::cout << "\n\tPlease choose an option: ";
    int input;
    bool valid = false;
    do {
      std::cin >> input;
      switch (input) {
      case 1: // Client and Account Management
        client_manage_menu();
        break;
      case 2: // Add a branch staff member
        sys.add_member();
        system_admin_menu();
        break;
      case 3: // Delete a branch staff member
        sys.delete_member();
        system_admin_menu();
        break;
      case 4: // Display branch staff
        sys.display_staff();
        system_admin_menu();
        break;
      case 5: // Change password
        sys.change_password();
        system_admin_menu();
        break;
      case 6: // Exit
        std::cout << "\n\t\t\tTerminal Closing" << '\n';
        exit(EXIT_SUCCESS);
        break;
      default: // Input Invalid
        std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
        system_admin_menu();
        break;
      }
    } while (!valid);
  }

  void client_manage_menu(void) {
    std::string border =
        "===========================================================";
    std::cout << border << '\n';
    std::cout
        << "|      Teller Terminal System - Client and Account Management     |"
        << '\n';
    std::cout << border << '\n';
    std::cout << "1) Add a client" << '\n';
    std::cout << "2) Add an account" << '\n';
    std::cout << "3) Edit client information" << '\n';
    std::cout << "4) Manage an account" << '\n';
    std::cout << "5) Save client and account information" << '\n';
    std::cout << "6) Exit" << '\n';
    std::cout << "\n\tPlease choose an option: ";
    int input;
    bool valid = false;
    do {
      std::cin >> input;
      switch (input) {
      case 1: // Add a client
        client.add_client();
        client_manage_menu();
        break;
      case 2: // Add an account
        client.add_account();
        sys.pause();
        client_manage_menu();
        break;
      case 3: // Edit client information
        if (client.manage_information() == -1) {
          std::cout << "Error - The client is not in the system! " << '\n';
        }
        client_manage_menu();
        break;
      case 4: // Manage an account
        client.manage_account();
        client_manage_menu();
        break;
      case 5: // Save client and account information
        client.save();
        client_manage_menu();
        break;
      case 6: // Exit
        if (sys.get_privileges() == "1") {
          system_admin_menu();
        } else if (sys.get_privileges() == "2") {
          branch_staff_menu();
        } else {
          std::cout << "Unknown Error" << '\n';
        }
        break;
      default: // Input Invalid
        std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
        client_manage_menu();
        break;
      }
    } while (!valid);
  }
};
