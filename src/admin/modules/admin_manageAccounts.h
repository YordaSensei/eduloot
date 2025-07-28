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

// Global map that links account types to their corresponding file name, display color, and title.
// Used in AccountManager for handling different user account files.
const map<int, tuple<string, ostream& (*)(ostream&), string>> AccountManager::accountsOption = {
    {1, {"studentAccounts.txt", termcolor::blue, "STUDENT ACCOUNTS"}},
    {2, {"teacherAccounts.txt", termcolor::green, "TEACHER ACCOUNTS"}},
    {3, {"merchantAccounts.txt", termcolor::yellow, "MERCHANT ACCOUNTS"}},
    {4, {"parentAccounts.txt", termcolor::cyan, "PARENT ACCOUNTS"}}
};


// main menu for account manager
void AccountManager::manageAccounts() {
    int choice;
    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|        MANAGE ACCOUNTS        |\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. View Accounts             |\n";
        cout << "|  2. Create Account            |\n";
        cout << "|  3. Edit Account              |\n";
        cout << "|  4. Delete Account            |\n";
        cout << "|  5. Back                      |\n";
        cout << "+-------------------------------+\n" << termcolor::reset;

        do {
            choice = promptChoice(1, 5, "Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
        system("cls");

        // Executes the corresponding function based on the admin's menu choice
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

// Function to display the account type menu to minimize code repetition
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
    cout << "+-------------------------------+\n";

    do {
        choice = promptChoice(1, 5, "Choice: ");
        if (choice == 0) {
            cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
        }
    } while (choice == 0);
    system("cls");
    return choice;
}


// Function to display the contents of a specific account type file with a formatted header
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
        accountFile.close();
        cout << termcolor::reset;
    } else {
        cout << termcolor::red <<  "\nERROR opening file: " << filename << termcolor::reset << endl;
    }

    cout << headerColor << "+-----------------------------------+\n";
    cout << termcolor::red << "Press 0 to cancel\n" << termcolor::reset;
}

// function for viewing accounts
void AccountManager::viewAccounts() {
    int choice;
    do {
        do {
            choice = printAccountTypeMenu("VIEW");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);

        if (choice==5) {
            cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
            clearSystem(1200);
            return;
        } 

        // Check if the chosen option exists in the map
        if (!accountsOption.count(choice)) {
            cout << termcolor::bright_red << "\nInvalid choice. Try again.\n" << termcolor::reset;
            continue;
        }

        // structured binding with 'auto' to simplify access to the tuple (filename, color, title) for the selected account type
        auto option = accountsOption.at(choice);            // auto = tuple<string, ostream& (*)(ostream&), string>
        string filename = get<0>(option);                   // filename of the account records
        ostream& (*color)(ostream&)   = get<1>(option);     // color function pointer (termcolor)
        string title    = get<2>(option);                   // section title 

        displayAccountType(filename, color, title);
    } while (choice !=  5);
}

void AccountManager::createAccount() {
    int choice;

    do {
        // Prompt the user for account type until they enter something valid
        do {
            choice = printAccountTypeMenu("CREATE");

            // Prevent user from selecting 0
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);

        if (choice == 5) {
            cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
            clearSystem(1200); 
            return;
        } 

        if (!accountsOption.count(choice)) {
            cout << termcolor::bright_red << "\nInvalid choice. Try again.\n" << termcolor::reset;
            continue;
        }

        auto option = accountsOption.at(choice);
        string filename                 = get<0>(option); 
        ostream& (*color)(ostream&)     = get<1>(option); 
        string title                    = get<2>(option); 

        displayAccountType(filename, color, title);
        
        // For Student, Teacher, and Parent accounts
        if (choice == 1 || choice == 2 || choice == 4) {
            Account acc;

            // Ask for a valid CIIT email
            while (true) {
                acc.ciitEmail = promptNonEmptyInput("Email: ");

                if (cancelInput(acc.ciitEmail)) {
                    return;
                }

                // Check if the email is valid (contains domain, no spaces)
                if (acc.ciitEmail.find("@ciit.edu.ph") == string::npos || acc.ciitEmail.find(" ") != string::npos) {
                    cout << termcolor::bright_red << "\nERROR: Please enter a valid CIIT Email (must contain @ciit.edu.ph and no spaces)\n" << termcolor::reset;
                    continue;
                }

                // Check if email already exists
                if (isEmailTaken(filename, acc.ciitEmail)) {
                    cout << termcolor::bright_red << "\nERROR: Account already exists!\n" << termcolor::reset;
                    continue;
                }

                break;
            }

            // Prompt for a unique username
            while (true) {
                acc.username = promptNonEmptyInput("Username: ");

                if (cancelInput(acc.username)) {
                    return;
                }

                // Check if username is already used
                if (isUsernameTaken(filename, acc.username)) {
                    cout << termcolor::bright_red << "\nERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                    continue;
                } else {
                    break;
                }
            }

            // Ask for a password
            acc.password = promptNonEmptyInput("Password: ");
            if (cancelInput(acc.password)) {
                return;
            }
            
            // Append account details to file
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

        // For Merchant account creation
        else if (choice == 3) {
            Merchant shop;

            // Prompt for unique shop name
            while (true) {
                shop.shopname = promptNonEmptyInput("Shop Name: ");

                if (cancelInput(shop.shopname)) {
                    return;
                }

                // Reuses isEmailTaken to check for duplicate shop names
                if (isEmailTaken(filename, shop.shopname)) {
                    cout << termcolor::bright_red << "ERROR: Shop already exists!\n" << termcolor::reset;
                    continue;
                } else {
                    break;
                }
            }

            // Prompt for a unique username
            while (true) {
                shop.username = promptNonEmptyInput("Username: ");

                if (cancelInput(shop.username)) {
                    return;
                }

                if (isUsernameTaken(filename, shop.username)) {
                    cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                    continue;
                } else {
                    break;
                }
            }

            // Ask for a password
            shop.password = promptNonEmptyInput("Password: ");
            if (cancelInput(shop.password)) {
                return;
            }

            // Append merchant details to file
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

    } while (choice != 5); // Loop until user chooses to return
}

void AccountManager::deleteAccount() {
    int choice;
    do {
       do {
            choice = printAccountTypeMenu("DELETE");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);

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
        string filename                 = get<0>(option);
        ostream& (*color)(ostream&)     = get<1>(option);
        string title                    = get<2>(option);
        displayAccountType(filename, color, title);

        cout << termcolor::bold << termcolor::bright_yellow;
        cout << "\n+----------------------------------------+\n";
        cout << "|              ENTER DETAILS             |\n";
        cout << "+----------------------------------------+\n";
        cout << termcolor::reset; 

        // Depending on the account type, either prompt for shop name or CIIT email
        string promptLabel = (choice == 3) ? "Shop Name: " : "CIIT Email: ";

        // Prompt for the unique identifier (email/shop), cancel if "0"
        string emailOrshop = promptNonEmptyInput(promptLabel);
        if (cancelInput(emailOrshop)) {
            return;
        }

        // Prompt for username, cancel if "0"
        string username    = promptNonEmptyInput("Username: ");
        if (cancelInput(username)) {
            return;
        }

        // Prompt for password, cancel if "0"
        string password    = promptNonEmptyInput("Password: ");
        if (cancelInput(password)) {
             return;
        }

        // Combine details into a single line string for deletion
        string accountToDelete = emailOrshop + "," + username + "," + password;
        deleteLine(filename, accountToDelete);  // Call helper to delete the specific line from file
        clearSystem(2000);
        break;
    } while (choice != 5);
}

void AccountManager::editAccount() {
    int choice;

    do {
        do {
            choice = printAccountTypeMenu("EDIT");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);

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

        // Collect credentials of the account to find
        string findemailOrShop = promptNonEmptyInput(label);
        if (cancelInput(findemailOrShop)) {
                return;
        }
        string findusername = promptNonEmptyInput("Username: ");
        if (cancelInput(findusername)) {
                return;
        }
        string findpassword = promptNonEmptyInput("Password: ");
        if (cancelInput(findpassword)) {
                return;
        }
        string oldDetails = findemailOrShop + "," + findusername + "," + findpassword;

        // Search for the account in the file
        bool accountFound = false;
        string line;
        ifstream findAccount(filename);
        while (getline(findAccount, line)) {
            if (line == oldDetails) {
                accountFound = true;
                break; // Stop once found
            } 
        } 
        findAccount.close();

        if (accountFound) {
            cout << termcolor::green << "Account found!\n" << termcolor::reset;
        } else {
            cout << termcolor::red << "Account not found.\n" << termcolor::reset;
            return; // exists the function if account is not found
        }
        
        // Prompt user for new account details
        cout << termcolor::bold << termcolor::bright_magenta;
        cout << "\n+----------------------------------------+\n";
        cout << "|              NEW DETAILS               |\n";
        cout << "+----------------------------------------+\n";
        cout << termcolor::reset;

        string emailOrShop, username;

        // Input new email/shop and validate
        while (true) {
            emailOrShop = promptNonEmptyInput(label);

            if (cancelInput(emailOrShop)) {
                    return;
            }

            if (emailOrShop == findemailOrShop || isEmailTaken(filename, emailOrShop)) {
                cout << termcolor::bright_red << "ERROR: That " << ((choice == 3) ? "shop name" : "email") << " already exists!\n" << termcolor::reset;
                continue;
            } else {
                break;
            }
        }

        // Input new username and validate
        while (true) {
            username = promptNonEmptyInput("Username: ");

            if (cancelInput(username)) {
                    return;
            }

            if (username == findusername || isUsernameTaken(filename, username)) {
                cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                continue;
            } else {
                break;
            }
        }

        // Input new password
        string password = promptNonEmptyInput("Password: ");
        if (cancelInput(password)) {
            return;
        }

        string newDetails = emailOrShop + "," + username + "," + password;

        // Replace old account details with new ones in file
        editLine(filename, oldDetails, newDetails);
        clearSystem(2000);
        
    } while (choice != 5);
}