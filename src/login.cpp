#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "adminMain.cpp"
#include "merchantMain.cpp"
#include "student.cpp"
#include "Teacher.cpp"
#include "Parent.cpp"
#include "admin_helpers.cpp"
#include "admin/admin_functions.h"
#include "termcolor/termcolor.hpp"

using namespace std;

void adminMain();
void merchantMain();
void studentMain();
void teacherMain();
void parentMain();

int main() {
    string inputEmail;
    string inputPassword;
    bool loggedIn = false;

    while (!loggedIn) {
        displayWelcomeMessage();
        displayLoginPrompt(inputEmail, inputPassword);

        if (validateLogin("adminAccount.txt", inputEmail, inputPassword, "admin")) {
            cout << termcolor::red << "\nLogging in as Admin...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem();
            adminMain();
        }
        else if (validateLogin("merchantAccounts.txt", inputEmail, inputPassword, "merchant")) {
            cout << termcolor::red << "\nLogging in as Merchant...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem();
            merchantMain(inputEmail);
        }
        else if (validateLogin("studentAccounts.txt", inputEmail, inputPassword, "student")) {
            cout << termcolor::red << "\nLogging in as Student...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem();
            studentMain(inputEmail);
        }
        else if (validateLogin("teacherAccounts.txt", inputEmail, inputPassword, "teacher")) {
            cout << termcolor::red << "\nLogging in as Teacher...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem();
            Teacher teacher;
            teacher.teacherMain(inputEmail);
        }
        else if (validateLogin("parentAccounts.txt", inputEmail, inputPassword, "parent")) {
            cout << termcolor::red << "\nLogging in as Parent...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem();
            Parent parent;
            parent.parentMain(inputEmail);
        }
        else {
            cout << termcolor::red << "Invalid email or password. Please try again.\n\n" << termcolor::reset;
        }
    }

    return 0;
}

void displayWelcomeMessage() {
    cout << termcolor::bold << termcolor::bright_magenta;
    cout << "\n+============================================+" << endl;
    cout << "|                                            |" << endl;
    cout << "|         WELCOME TO EDULOOT SYSTEM          |" << endl;
    cout << "|                                            |" << endl;
    cout << "+============================================+\n" << termcolor::reset;
}

void displayLoginPrompt(string& email, string& password) {
    cout << termcolor::bold << termcolor::bright_blue;
    cout << "+--------------------------------------------+" << endl;
    cout << "|                  LOGIN                     |" << endl;
    cout << "+--------------------------------------------+" << termcolor::reset << endl;
    cout << termcolor::bold << termcolor::bright_blue << "Email:   " << termcolor::reset;
    cin >> email;
    cout << termcolor::bold << termcolor::bright_blue << "Password:   " << termcolor::reset;
    cin >> password;
}

bool validateLogin(const string& filename, const string& inputEmail, const string& inputPassword, const string& userType) {
    ifstream inFile(filename);
    string line;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            string email, username, password;
            stringstream split(line);

            getline(split, email, ',');
            getline(split, username, ',');
            getline(split, password, ',');
            
            if (inputEmail == email && inputPassword == password) {
                inFile.close();
                return true;
            }
        }
    }

    inFile.close();
    return false;
}