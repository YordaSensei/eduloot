#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "adminMain.cpp"
#include "merchantMain.cpp"
#include "student.cpp"
#include "admin_helpers.cpp"
#include "admin/admin_functions.h"
#include "termcolor/termcolor.hpp"

using namespace std;

void adminMain();
void merchantMain();
void studentMain();
void teacherMain();

int main(){
    string inputEmail;
    string inputPassword;
    bool loggedIn = false;

    while (!loggedIn) {
        cout << termcolor::bold << termcolor::bright_magenta;
        cout << "\n+============================================+" << endl;
        cout << "|                                            |" << endl;
        cout << "|         WELCOME TO EDULOOT SYSTEM          |" << endl;
        cout << "|                                            |" << endl;
        cout << "+============================================+\n" << termcolor::reset;

        cout << termcolor::bold << termcolor::bright_blue;
        cout << "+--------------------------------------------+" << endl;
        cout << "|                  LOGIN                     |" << endl;
        cout << "+--------------------------------------------+" << termcolor::reset << endl;
        cout << termcolor::bold << termcolor::bright_blue << "Email:   " << termcolor::reset;
        cin >> inputEmail;
        cout << termcolor::bold << termcolor::bright_blue << "Password:   " << termcolor::reset;
        cin >> inputPassword;
        
        string line;

        ifstream adminInFile("adminAccount.txt");
        while (getline(adminInFile, line)) {
            if (!line.empty()) {
                string email, username, password;
                stringstream split(line);

                getline(split, email, ',');
                getline(split, username, ',');
                getline(split, password, ',');
                
                if (inputEmail == email && inputPassword == password){
                    cout << "Logging in...\n";
                    loggedIn = true;
                    clearSystem();
                    adminMain();
                    break;
                }
            }
        }

        adminInFile.close();
        if (loggedIn) break;

        ifstream merchantInFile("merchantAccounts.txt");
        while (getline(merchantInFile, line)) {
            if (!line.empty()) {
                string email, username, password;
                stringstream split(line);

                getline(split, email, ',');
                getline(split, username, ',');
                getline(split, password, ',');
                
                if (inputEmail == email && inputPassword == password){
                    cout << "Logging in...\n";
                    loggedIn = true;
                    clearSystem();
                    merchantMain(email);
                    break;
                }
            }
        }

        merchantInFile.close();
        if (loggedIn) break;

        ifstream studentInFile("studentAccounts.txt");
        while (getline(studentInFile, line)) {
            if (!line.empty()) {
                string email, username, password;
                stringstream split(line);

                getline(split, email, ',');
                getline(split, username, ',');
                getline(split, password, ',');
                
                if (inputEmail == email && inputPassword == password){
                    cout << "Logging in...\n";
                    loggedIn = true;
                    clearSystem();
                    studentMain(email);
                    break;
                }
            }
        }

        studentInFile.close();
        if (loggedIn) break;

        if (!loggedIn) {
            cout << termcolor::red << "Invalid email or password. Please try again.\n\n" << termcolor::reset;
        }
    }

    return 0;
}