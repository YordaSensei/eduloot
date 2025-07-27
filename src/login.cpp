#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "admin/core/adminMain.cpp"  
#include "merchant/core/merchantMain.cpp"
#include "student/core/student.cpp"
#include "User.cpp"
#include "Teacher.cpp"
#include "Parent.cpp"
#include "admin/core/admin_helpers.cpp"
#include "termcolor/termcolor.hpp"

using namespace std;

void adminMain();
void merchantMain();
void studentMain();
void teacherMain();
void parentMain();
void displayWelcomeMessage();
void displayLoginPrompt(string& email, string& password);
bool validateLogin(const string& filename, const string& inputEmail, const string& inputPassword, const string& userType, bool skipPasswordCheck);

int main() {
    string inputEmail;
    string inputPassword;
    bool loggedIn = false;

    while (!loggedIn) {
        displayWelcomeMessage();
        displayLoginPrompt(inputEmail, inputPassword);

        if (validateLogin("admin/files/adminAccount.txt", inputEmail, inputPassword, "admin", false)) {
            cout << termcolor::red << "\nLogging in as Admin...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem(1200);
            adminMain();
        }
        else if (validateLogin("merchantAccounts.txt", inputEmail, inputPassword, "merchant", false)) {
            cout << termcolor::red << "\nLogging in as Merchant...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem(1200);
            merchantMain(inputEmail);
        }
        else if (validateLogin("studentAccounts.txt", inputEmail, inputPassword, "student", false)) {
            cout << termcolor::red << "\nLogging in as Student...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem(1200);
            studentMain(inputEmail);
        }
        else if (validateLogin("teacherAccounts.txt", inputEmail, inputPassword, "teacher", false)) {
            cout << termcolor::red << "\nLogging in as Teacher...\n" << termcolor::reset;
            loggedIn = true;
            clearSystem(1200);
            Teacher teacher;
            teacher.teacherMain(inputEmail);
        }
        else if (validateLogin("parentAccounts.txt", inputEmail, inputPassword, "parent", false)) {
            cout << termcolor::red << "\nLogging in as Parent...\n" << termcolor::reset;
            loggedIn = true;

            string inputChildEmail;
            cout << "Enter your child's email: ";
            while (!(cin >> inputChildEmail) || inputChildEmail.empty()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid email. Please try again: ";
            }

            if (!validateLogin("studentAccounts.txt", inputChildEmail, "dummyParentAccessed", "student", true)) {
                cout << termcolor::red << "\nChild email not found. Please try again.\n" << termcolor::reset;
                loggedIn = false;
                continue;
            }

            clearSystem(1200);
            Parent parent;
            parent.parentMain(inputEmail, inputChildEmail);
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
    email = promptNonEmptyInput ("Email: ");
    password = promptNonEmptyInput ("Password: ");
}

bool validateLogin(const string& filename, const string& inputEmail, const string& inputPassword, const string& userType, bool skipPasswordCheck = false) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }
    string line;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            string email, username, password;
            stringstream split(line);

            getline(split, email, ',');
            getline(split, username, ',');
            getline(split, password, ',');
            
            if (inputEmail == email) {
                if (skipPasswordCheck || inputPassword == password) {
                    inFile.close();
                    return true;
                }
            }
        }
    }

    inFile.close();
    return false;
}