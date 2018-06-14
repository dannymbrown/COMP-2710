/**
@file   system.cpp

@author Danny Brown (dmb0057)
@version 04-28-2018 18:26

@section DESCRIPTION

This file contains functions for the system in general as well as the functions
of Administrators and staff members.

*/

#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

class System {
private:
  std::string current_user;
  std::string privileges;
  bool is_active = false;

public:
  void pause() {
    std::cout << "Press any key to continue...";
    std::cin.ignore().get();
  }

  void login(void) {
    std::string username, password, un, pw, role;
    std::string border =
        "===========================================================";
    std::cout << border << '\n';
    std::cout << "|        Login to Access the Teller Terminal System       |"
              << '\n';
    std::cout << border << '\n';
    do {
      std::cout << "\nEnter username: ";
      std::cin >> username;
      set_current_user(username);
      std::cout << "Enter Password: ";
      std::cin >> password;
      std::ifstream read("./data/staff/" + username + ".txt");
      getline(read, un);   // read username
      getline(read, pw);   // read password
      getline(read, role); // role = 1 if admin, 2 otherwise
      if (!is_valid(username, password, un, pw)) {
        std::cout << "\n\t\t\tError: Invalid username or password" << '\n';
      }
    } while (!is_valid(username, password, un, pw));
    set_current_state(true);
    set_privileges(role);
  }

  std::string get_privileges(void) { return privileges; }

  void set_privileges(std::string role) { privileges = role; }

  bool is_valid(std::string input_username, std::string input_password,
                std::string actual_username, std::string actual_password) {
    bool valid = false;
    if (input_username == actual_username &&
        input_password == actual_password) {
      valid = true;
    }

    return valid;
  }

  bool get_current_state(void) { return is_active; }

  void set_current_state(bool currentstate) { is_active = currentstate; }

  void set_current_user(std::string user) { current_user = user; }

  std::string get_current_user(void) { return current_user; }

  void delete_member(void) {
    std::string username;
    std::cout << "Delete a user - User Name: ";
    std::cin >> username;
    bool valid = false;
    int input;
    std::cout << "1) Confirm\n2) Cancel";
    do {
      std::cout << "\nPlease choose an option: " << '\n';
      std::cin >> input;
      switch (input) {
      case 1:
        goto delete_user;
        break;
      case 2:
        valid = true;
        break;
      default:
        std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
        break;
      }
    } while (!valid);
  delete_user:
    std::string const file("./data/staff/" + username + ".txt");
    bool failed = !std::ifstream(file.c_str());
    if (failed) {
      std::cout << "Warning - User " << username
                << " is not in the system. No user is deleted!" << '\n';
    } else {
      std::remove(file.c_str());
      std::cout << "User " << username << " is deleted!" << '\n';
    }
  }

  void display_staff(void) {
    std::ifstream read("./data/staff/roster.txt");
    std::string un, rl;
    int index = 1;
    while (getline(read, un)) {
      getline(read, rl);
      std::cout << index << '.' << " User Name: " << un << "       Role: " << rl
                << '\n';
      index++;
    }
    if (read.eof()) { // check for EOF
      std::cout << "[EoF reached]\n";
    }
  }

  void change_password(void) {
    std::string un, pw, role, newpw;
    std::ifstream read("./data/staff/" + get_current_user() + ".txt");
    getline(read, un);   // read username
    getline(read, pw);   // read password
    getline(read, role); // read role
    do {
      std::cout << "New Password: ";
      std::cin >> newpw;
      if (pw == newpw) {
        std::cout
            << "Error - Your new password must be different from the old one!"
            << '\n';
      }
    } while (pw == newpw);

    std::ofstream file;
    file.open("./data/staff/" + get_current_user() + ".txt");
    file << un << '\n' << newpw << '\n' << role;
    file.close();
    std::cout << "Password was changed!" << '\n';
    pause();
  }

  void add_member(void) {
    std::string username, password, role;
    std::cout << "Username: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;
    std::cout << "Role (1 - Administrator; 2 - Branch Staff): ";
    std::cin >> role;
    bool valid = false;
    int input;
    std::cout << "1) Confirm\n2) Cancel\nPlease choose an option: ";
    do {
      std::cin >> input;
      switch (input) {
      case 1:
        goto make_user;
        break;
      case 2:
        valid = true;
        break;
      default:
        std::cout << "\n\t\t\tERROR: Invalid Input" << '\n';
        break;
      }
    } while (!valid);
  //-----------------------------------------------------------------------//
  //                          create new user                              //
  //-----------------------------------------------------------------------//
  make_user:
    std::ofstream file;
    file.open("./data/staff/" + username + ".txt");
    file << username << '\n' << password << '\n' << role;
    file.close();
    std::cout << "A new branch staff member is added!" << '\n';
    std::string title;
    if (role == "1") {
      title = "System Administrator";
    } else {
      title = "Branch Staff";
    }
    std::cout << "User Name: " << username << "  Role: " << title << '\n';
    //-----------------------------------------------------------------------//
    //                   add new user to staff roster                       //
    //-----------------------------------------------------------------------//
    std::ofstream roster("./data/staff/roster.txt", std::ios_base::app);
    roster << '\n' << username << '\n' << title;
    roster.close();
    pause();
  }
};
