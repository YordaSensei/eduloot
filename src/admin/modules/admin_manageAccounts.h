#pragma once
#include "../includes/admin_includes.h"

using namespace std;


class AccountManager {
    public:
        void manageAccounts();

    private:
        enum AccountType {
            STUDENT = 1,
            TEACHER,
            MERCHANT,
            PARENT,
            BACK
        };

        int printAccountTypeMenu(const string &title);
        void viewAccounts();
        void createAccount();
        void deleteAccount();
        void editAccount();
        void displayAccountType(const string &filename, ostream& (*headerColor)(ostream&), const string &title);
        
        static const map<int, tuple<string, ostream& (*)(ostream&), string>> accountsOption;
};

const map<int, tuple<string,  ostream& (*)(ostream&), string>> AccountManager::accountsOption = {
    {1, {"studentAccounts.txt", termcolor::blue, "STUDENT ACCOUNTS"}},
    {2, {"teacherAccounts.txt", termcolor::green, "TEACHER ACCOUNTS"}},
    {3, {"merchantAccounts.txt", termcolor::yellow, "MERCHANT ACCOUNTS"}},
    {4, {"parentAccounts.txt", termcolor::cyan, "PARENT ACCOUNTS"}}
};

void AccountManager::manageAccounts() {
    int choice;
    do {
        cout << termcolor::bold << termcolor::cyan;
        cout << "\n+-------------------------------+\n";
        cout << "|        MANAGE ACCOUNTS        |\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. View Accounts             |\n";
        cout << "|  2. Create Account            |\n";
        cout << "|  3. Edit Account              |\n";
        cout << "|  4. Delete Account            |\n";
        cout << "|  5. Back                      |\n";
        cout << "+-------------------------------+\n" << termcolor::reset;

        choice = promptChoice(1, 5, "Choice: ");
        system("cls");

        switch (choice) {
            case 1:viewAccounts(); break;
            case 2: createAccount(); break;
            case 3: editAccount(); break;
            case 4: deleteAccount(); break;
            case 5:
                cout << termcolor::red << "Returning...\n" << termcolor::reset;
                clearSystem(1200);
                break;
            default: 
                cout << termcolor::bright_red << "\nInvalid choice!\n" << termcolor::reset;
                continue;
        }
    } while (choice != 5);
}

int AccountManager::printAccountTypeMenu(const string& title) {
    int choice;
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-------------------------------+\n";
    cout << "|  " << termcolor::bright_yellow << setw(29) << left << title << termcolor::magenta <<   "|\n";
    cout << "+-------------------------------+\n";
    cout << "|  1. Student                   |\n";
    cout << "|  2. Teacher                   |\n";
    cout << "|  3. Merchant                  |\n";
    cout << "|  4. Parent                    |\n";
    cout << "|  5. Back                      |\n";
    cout << "+-------------------------------+\n" << termcolor::reset;

    choice = promptChoice(1, 5, "Choice: ");
    system("cls");
    return choice;
}

void AccountManager::displayAccountType(const string &filename, ostream& (*headerColor)(ostream&), const string &title) {
    ifstream accountFile (filename);
    string line;

    cout << headerColor << termcolor::bold;
    cout << "\n+-----------------------------------+\n";
    cout << "|        " << setw(27) << left << title << "|\n";
    cout << "+-----------------------------------+\n";
    cout << termcolor::reset;

    if (accountFile.is_open()) {
        cout << termcolor::bold << termcolor::grey;
        while (getline(accountFile, line)) {
            cout << "- " << line << "\n";
        }
        cout << termcolor::reset;
        accountFile.close();
    } else {
        cout << termcolor::red <<  "\nERROR opening file: " << filename << termcolor::reset << endl;
    }
}

void AccountManager::viewAccounts() {
    int choice;
    do {
        choice = printAccountTypeMenu("VIEW");
        if (choice==5) {
            cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
            clearSystem(1200);
            return;
        } 

        if (!accountsOption.count(choice)) {
            cout << termcolor::bright_red << "\nInvalid choice. Try again.\n" << termcolor::reset;
            continue;
        }

        auto option = accountsOption.at(choice);
        string filename = get<0>(option);
        ostream& (*color)(ostream&)   = get<1>(option);
        string title    = get<2>(option);

        displayAccountType(filename, color, title);
    } while (choice !=  5);
}

void AccountManager::createAccount() {
    int choice;

    do {
        choice = printAccountTypeMenu("CREATE");

        if (choice==5) {
            cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
            clearSystem(1200);
            return;
        } 

        if (!accountsOption.count(choice)) {
            cout << termcolor::bright_red << "\nInvalid choice. Try again.\n" << termcolor::reset;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto option = accountsOption.at(choice);
        string filename                 = get<0>(option);
        ostream& (*color)(ostream&)     = get<1>(option);
        string title                    = get<2>(option);
        displayAccountType(filename, color, title);
        
        if (choice == 1 || choice == 2 || choice == 4) {
            Account acc;
            
            while (true) {
                acc.ciitEmail = promptNonEmptyInput("Email: ");

                if (acc.ciitEmail.find("@ciit.edu.ph") == string::npos || acc.ciitEmail.find(" ") != string::npos) {
                    cout << termcolor::bright_red << "\nERROR: Please enter a valid CIIT Email (must contain @ciit.edu.ph and no spaces)\n" << termcolor::reset;
                    continue;
                }

                if (isEmailTaken(filename, acc.ciitEmail)) {
                    cout << termcolor::bright_red << "\nERROR: Account already exists!\n" << termcolor::reset;
                    continue;
                }

                break;
            }

            while (true) {
                acc.username = promptNonEmptyInput("Username: ");

                if (isUsernameTaken(filename, acc.username)) {
                    cout << termcolor::bright_red << "\nERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                    continue;
                } else {
                    break;
                }
            }

            acc.password = promptNonEmptyInput("Password: ");

            ofstream accountsFile(filename, ios::app);
            if (accountsFile.is_open()) {
                accountsFile << acc.ciitEmail << "," << acc.username << "," << acc.password << endl;
                accountsFile.close();
                cout << termcolor::green << "\nAccount created successfully!\n" << termcolor::reset;
                clearSystem(2000);
            } else {
                cout << termcolor::bright_red << "\nERROR: Cannot open file.\n" << termcolor::reset;
                clearSystem(2000);
            }
            
        }

        else if (choice == 3) {
            Merchant shop;
            shop.shopname = promptNonEmptyInput("Shop Name: ");

            if (isEmailTaken(filename, shop.shopname)) {
                cout << termcolor::bright_red << "ERROR: Shop already exists!\n" << termcolor::reset;
                continue;
            }
                
            shop.username = promptNonEmptyInput("Username: ");

            if (isUsernameTaken(filename, shop.username)) {
                cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                continue;
            }

            shop.password = promptNonEmptyInput("Password: ");

            ofstream accountsFile(filename, ios::app);
            if (accountsFile.is_open()) {
                accountsFile << shop.shopname << "," << shop.username << "," << shop.password << endl;
                accountsFile.close();
                cout << termcolor::green << "\nShop created successfully!\n" << termcolor::reset;
                clearSystem(2000);
            } else {
                cout << termcolor::bright_red << "\nERROR: Cannot open file\n" << termcolor::reset;
                clearSystem(2000);
            }
        }
    }while (choice != 5);
}

void AccountManager::deleteAccount() {
    int choice;
    do {
       choice = printAccountTypeMenu("DELETE");

        if (choice==5) {
            cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
            clearSystem(1200);
            return;
        } 

        if (!accountsOption.count(choice)) {
            cout << termcolor::bright_red << "\nInvalid choice. Try again.\n" << termcolor::reset;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto option = accountsOption.at(choice);
        string filename                 = get<0>(option);
        ostream& (*color)(ostream&)     = get<1>(option);
        string title                    = get<2>(option);
        displayAccountType(filename, color, title);

        cout << termcolor::bold << termcolor::bright_yellow;
        cout << "\n+----------------------------------------+\n";
        cout << "|              ENTER DETAILS             |\n";
        cout << "+----------------------------------------+\n";
        cout << termcolor::reset; 

        string promptLabel = (choice == 3) ? "Shop Name: " : "CIIT Email: ";
        string emailOrshop = promptNonEmptyInput(promptLabel);
        string username    = promptNonEmptyInput("Username: ");
        string password    = promptNonEmptyInput("Password: ");

        string accountToDelete = emailOrshop + "," + username + "," + password;
        deleteLine(filename, accountToDelete);
        clearSystem(2000);
        break;
    } while (choice != 5);
}

void AccountManager::editAccount() {
    int choice;

    do {
        choice = printAccountTypeMenu("EDIT");

        if (choice==5) {
            cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
            clearSystem(1200);
            return;
        } 

        if (!accountsOption.count(choice)) {
            cout << termcolor::bright_red << "\nInvalid choice. Try again.\n" << termcolor::reset;
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        auto option = accountsOption.at(choice);
        string filename                 = get<0>(option);
        ostream& (*color)(ostream&)     = get<1>(option);
        string title                    = get<2>(option);
        displayAccountType(filename, color, title);

        cout << termcolor::bold << termcolor::bright_magenta;
        cout << "\n+-----------------------------------------+\n";
        cout << "|              FIND ACCOUNT               |\n";
        cout << "+-----------------------------------------+\n";
        cout << termcolor::reset;

        string label = (choice == 3) ? "Shop Name: " : "CIIT Email: ";
        string findemailOrShop = promptNonEmptyInput(label);
        string findusername = promptNonEmptyInput("Username: ");
        string findpassword = promptNonEmptyInput("Password: ");
        string oldDetails = findemailOrShop + "," + findusername + "," + findpassword;

        bool accountFound = false;
        string line;
        ifstream findAccount(filename);
            while (getline(findAccount, line)) {
                if (line == oldDetails) {
                    accountFound = true;
                } 
            } 
            findAccount.close();

            if (accountFound) {
                cout << termcolor::green << "Account found!\n" << termcolor::reset;
            } else {
                cout << termcolor::red << "Account not found.\n" << termcolor::reset;
                continue; 
            }
                
        cout << termcolor::bold << termcolor::bright_magenta;
        cout << "\n+----------------------------------------+\n";
        cout << "|              NEW DETAILS               |\n";
        cout << "+----------------------------------------+\n";
        cout << termcolor::reset;

        string emailOrShop, username;
        while (true) {
            emailOrShop = promptNonEmptyInput(label);
            if (emailOrShop == findemailOrShop || isEmailTaken(filename, emailOrShop)) {
                cout << termcolor::bright_red << "ERROR: That " << ((choice == 3) ? "shop name" : "email") << " already exists!\n" << termcolor::reset;
                continue;
            } else {
                break;
            }
        }

        while (true) {
            username = promptNonEmptyInput("Username: ");
            if (username == findusername || isUsernameTaken(filename, username)) {
                cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                continue;
            } else {
                break;
            }
        }

        string password = promptNonEmptyInput("Password: ");
        string newDetails = emailOrShop + "," + username + "," + password;

        editLine(filename, oldDetails, newDetails);
        clearSystem(2000);
        
    } while (choice != 5);
}