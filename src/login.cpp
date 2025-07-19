#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "adminMain.cpp"
#include "merchantMain.cpp"
#include "student.cpp"
#include "admin_helpers.cpp"

using namespace std;

void adminMain();
void merchantMain();
void studentMain();
void teacherMain();

int main(){
    string inputEmail;
    string inputPassword;

    cout << "--- LOG IN ---\n";
    cout << "Email: ";
    cin >> inputEmail;
    cout << "Password: ";
    cin >> inputPassword;

    bool loggedIn = false;
    string line;

    //Admin validation
    ifstream adminInFile("adminAccount.txt");
    while (getline(adminInFile, line)) {
        if (!line.empty()) {
            string email, username, password;
            stringstream split(line);

            getline(split, email, ',');
            getline(split, username, ',');
            getline(split, password, ',');
            
            if (inputEmail == email && inputPassword == password){
                cout << "Login Successful!\n";
                loggedIn = true;
                adminMain();
                break;
            }
        }
    }

    adminInFile.close();

    //Merchant Validation
    ifstream merchantInFile("merchantAccounts.txt");
    while (getline(merchantInFile, line)) {
        if (!line.empty()) {
            string email, username, password;
            stringstream split(line);

            getline(split, email, ',');
            getline(split, username, ',');
            getline(split, password, ',');
            
            if (inputEmail == email && inputPassword == password){
                cout << "Login Successful!\n";
                loggedIn = true;
                merchantMain(email);
                break;
            }
        }
    }

    merchantInFile.close();

    //Student Validation
    ifstream studentInFile("studentAccounts.txt");
    while (getline(studentInFile, line)) {
        if (!line.empty()) {
            string email, username, password;
            stringstream split(line);

            getline(split, email, ',');
            getline(split, username, ',');
            getline(split, password, ',');
            
            if (inputEmail == email && inputPassword == password){
                cout << "Login Successful!\n";
                loggedIn = true;
                studentMain();
                break;
            }
        }
    }

    studentInFile.close();

    if (!loggedIn) {
        cout << "Invalid email or password.\n";
    }

    return 0;
}