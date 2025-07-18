#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "admin_helpers.h"
#include "admin_structs.h"

using namespace std;

void viewAccounts() {
    int choice;
    string line;

    do {
        cout << "\n        [VIEW]\n";
        cout << "--- Select Account Type ---\n";
        cout << "---------------------------\n";
        cout << "1. Student\n";
        cout << "2. Teacher\n";
        cout << "3. Merchant\n";
        cout << "4. Parent\n";
        cout << "5. Back\n";
        cout << "---------------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();
        
        ifstream file;
        switch (choice) {
            case 1:
                file.open("studentAccounts.txt");
                cout << "\n--- Student Accounts ---\n";
                break;
            case 2:
                file.open("teacherAccounts.txt");
                cout << "\n--- Teacher Accounts ---\n";
                break;
            case 3:
                file.open("merchantAccounts.txt");
                cout << "\n--- Merchant Accounts ---\n";
                break;
            case 4:
                file.open("parentAccounts.txt");
                cout << "\n--- Parent Accounts ---\n";
                break;
            case 5:
                break;
            default:
                cout << "ERROR: Invalid choice!";
                continue;
        }

        if (file.is_open()) {
            cout << "--------------------------\n";
            while (getline(file, line)) {
                cout << line << endl;
            }

            file.close();
        } else {
            cout << "\nERROR opening file\n";
        }
    }while (choice!= 5);
}

void createAccount() {
    int choice;
    Account acc;
    Merchant shop;
    ofstream accountsFile;

    do {
    cout << "\n        [CREATE]\n";
    cout << "--- Select Account Type ---\n";
    cout << "---------------------------\n";
    cout << "1. Student\n";
    cout << "2. Teacher\n";
    cout << "3. Merchant\n";
    cout << "4. Parent\n";
    cout << "5. Back\n";
    cout << "--------------------------\n";
    cout << "Choice: ";
    cin >> choice;
    cin.ignore();

    switch (choice) {
            case 1: case 2: case 4: {
                string filename;
                if (choice == 1) {
                    filename = "studentAccounts.txt";
                    cout << "\n--- Creating Student Account ---\n";
                }else if (choice == 2) {
                    filename = "teacherAccounts.txt";
                    cout << "\n--- Creating Teacher Account ---\n";
                } else if (choice == 4) {
                    filename = "parentAccounts.txt";
                    cout << "\n--- Creating Parent Account ---\n";
                }

                do {
                    cout << "CIIT Email: ";
                    getline (cin, acc.ciitEmail);

                    if (acc.ciitEmail.find("@ciit.edu.ph") == string::npos || acc.ciitEmail.find(" ") != string::npos) {
                        cout << "\nERROR: Please enter a valid CIIT Email (@ciit.edu.ph and no spaces)\n";
                        continue;
                    }

                    if (isEmailTaken(filename, acc.ciitEmail)) {
                        cout << "\nERROR: Account already exists!\n";
                        continue;
                    } 
                    
                    break;
                }while (true);

                do {
                    cout << "Username: ";
                    getline (cin, acc.username);
                    if (isUsernameTaken(filename, acc.username)) {
                        cout << "\nERROR: Username already exists!\n Please try a different one.\n";
                        continue;
                    } else {
                        break;
                    }
                } while (true);

                cout << "Password: ";
                getline (cin, acc.password);

                accountsFile.open(filename, ios::app);
                if (accountsFile.is_open()) {
                    accountsFile << acc.ciitEmail << "," << acc.username << "," << acc.password << endl;
                    accountsFile.close();
                    cout << "\nAccount created successfully!\n";
                } else {
                    cout << "\nERROR: Cannot open file\n";
                }

                break;
            }

            case 3: {
                string filename = "merchantAccounts.txt";
                accountsFile.open(filename, ios::app);

                cout << "\n--- Creating Merchant Account ---\n";

                do {
                    cout << "Shop Name: ";
                    getline (cin, shop.shopname);

                    if (isEmailTaken(filename, shop.shopname)) {
                    cout << "\nERROR: Shop already exists!\n";
                        continue;
                    } else {
                        break;
                    }
                } while(true);

                do {
                    cout << "Username: ";
                    getline (cin, shop.username);
                    if (isUsernameTaken(filename, shop.username)) {
                        cout << "\nERROR: Username already exists!\nPlease try a different one.\n";
                    } else {
                        break;
                    }
                }while (true);

                cout << "Password: ";
                getline (cin, shop.password);

                if (accountsFile.is_open()) {
                    accountsFile << shop.shopname << "," << shop.username << "," << shop.password << endl;
                    accountsFile.close();
                    cout << "\nShop created successfully!\n";
                } else {
                    cout << "\nERROR: Cannot open file\n";
                }
                break;
            }
            case 5:
                cout << "\nReturning to menu...\n";
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }

    } while (choice != 5);
}

void deleteAccount() {
    int choice;
    string emailOrShop, username, password;
    string filename;

    do {
        cout << "           [DELETE]\n";
        cout << "\n--- Select Account Type ---\n";
        cout << "-----------------------------\n";
        cout << "1. Student\n";
        cout << "2. Teacher\n";
        cout << "3. Merchant\n";
        cout << "4. Parent\n";
        cout << "5. Back\n";
        cout << "-----------------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: case 2: case 3: case 4: {
                cout << "\n-- Enter Details --\n";

                if (choice == 3) cout << "Shop Name: ";
                else cout << "CIIT Email: ";

                getline(cin, emailOrShop);

                cout << "Username: ";
                getline(cin, username);

                cout << "Password: ";
                getline(cin, password);

                if (choice == 1) filename = "studentAccounts.txt"; 
                if (choice == 2) filename = "teacherAccounts.txt"; 
                if (choice == 3)filename = "merchantAccounts.txt"; 
                if (choice == 4)filename = "parentAccounts.txt"; 
            
                string concat = emailOrShop + "," + username + "," + password;
                deleteLine(filename, concat);
                break;
            }

            case 5:
                break;
            default:
                cout << "\nERROR: Enter a valid choice!\n";
        }
    } while (choice != 5);
}

void editAccount () {
    int choice;
    string findemailOrShop, findusername, findpassword;
    string emailOrShop, username, password;
    string filename;

    do {
        cout << "\n         [EDIT]\n";
        cout << "--- Select Account Type ---\n";
        cout << "---------------------------\n";
        cout << "1. Student\n";
        cout << "2. Teacher\n";
        cout << "3. Merchant\n";
        cout << "4. Parent\n";
        cout << "5. Back\n";
        cout << "---------------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: case 2: case 3: case 4: {
                if (choice == 1) filename = "studentAccounts.txt"; 
                if (choice == 2) filename = "teacherAccounts.txt"; 
                if (choice == 3)filename = "merchantAccounts.txt"; 
                if (choice == 4)filename = "parentAccounts.txt"; 

                cout << "\n-- Find account --\n";
                if (choice == 3)cout << "Shop Name: ";
                else cout << "CIIT Email: ";
                getline (cin, findemailOrShop);

                cout << "Username: ";
                getline(cin, findusername);

                cout << "Password: ";
                getline(cin, findpassword);

                string oldDetails = findemailOrShop + "," + findusername + "," + findpassword;

                cout << "\n-- Enter New Account Details --\n";

                if (choice == 3)cout << "Shop Name: ";
                else cout << "CIIT Email: ";

                getline(cin, emailOrShop);

                cout << "Username: ";
                getline(cin, username);

                cout << "Password: ";
                getline(cin, password);

                string newDetails = emailOrShop + "," + username + "," + password;

                editLine (filename, oldDetails, newDetails);
                break;
            }
            case 5: 
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }

    } while (choice !=5);
}

void manageAccounts () {
    int choice;

    do {
        cout << "\n--- Manage Accounts ---\n";
        cout << "-------------------------\n";
        cout << "1. View all accounts\n";
        cout << "2. Create accounts\n";
        cout << "3. Delete account\n";
        cout << "4. Edit account information\n";
        cout << "5. Back to Dashboard\n";
        cout << "--------------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                viewAccounts();
                break;
            case 2:
                createAccount();
                break;
            case 3:
                deleteAccount();
                break;
            case 4:
                editAccount();
                break;
            case 5:
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }

    } while (choice != 5);

}