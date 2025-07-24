#include "../includes/admin_includes.h"

using namespace std;

int printAccountTypeMenu(const string& title) {
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

    while (true) {
        cout << termcolor::bright_yellow << "Choice: ";
        if (cin >> choice && choice >= 1 && choice <= 5) break;
        cout << termcolor::red << "Invalid choice. Please enter 1-5.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    return choice;
}

void viewAccounts() {
    int choice;
    string line;

    do {
        choice = printAccountTypeMenu("VIEW");
        
        ifstream file;
        switch (choice) {
            case 1:
                file.open("studentAccounts.txt");
                cout << termcolor::bold << termcolor::bright_blue;
                cout << "\n+--------------------------------------------+\n";
                cout << "|             STUDENT ACCOUNTS               |\n";
                cout << "+--------------------------------------------+\n";
                cout << termcolor::reset;
                break;
                
            case 2:
                file.open("teacherAccounts.txt");
                cout << termcolor::bold << termcolor::bright_green;
                cout << "\n+--------------------------------------------+\n";
                cout << "|             TEACHER ACCOUNTS               |\n";
                cout << "+--------------------------------------------+\n";
                cout << termcolor::reset;
                break;
                
            case 3:
                file.open("merchantAccounts.txt");
                cout << termcolor::bold << termcolor::bright_yellow;
                cout << "\n+--------------------------------------------+\n";
                cout << "|            MERCHANT ACCOUNTS               |\n";
                cout << "+--------------------------------------------+\n";
                cout << termcolor::reset;
                break;
                
            case 4:
                file.open("parentAccounts.txt");
                cout << termcolor::bold << termcolor::bright_cyan;
                cout << "\n+--------------------------------------------+\n";
                cout << "|              PARENT ACCOUNTS               |\n";
                cout << "+--------------------------------------------+\n";
                cout << termcolor::reset;
                break;
                
            case 5:
                break;

            default:
                cout << termcolor::bold << termcolor::red
                    << "\nERROR: Invalid choice!"
                    << termcolor::reset << endl;
                continue;
        }

        if (file.is_open()) {
            cout << termcolor::bold << termcolor::grey;
            while (getline(file, line)) {
                cout << line << endl;
            }
            cout << termcolor::reset;
            file.close();
        }
         else {
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
        choice = printAccountTypeMenu("CREATE");

    switch (choice) {
            case 1: case 2: case 4: {
                string filename;
                if (choice == 1) {
                    filename = "studentAccounts.txt";
                    cout << termcolor::bold << termcolor::bright_blue;
                    cout << "\n+--------------------------------------------+\n";
                    cout << "|              STUDENT ACCOUNT               |\n";
                    cout << "+--------------------------------------------+\n";
                    cout << termcolor::reset;
                } else if (choice == 2) {
                    filename = "teacherAccounts.txt";
                    cout << termcolor::bold << termcolor::bright_green;
                    cout << "\n+--------------------------------------------+\n";
                    cout << "|             TEACHER ACCOUNTS               |\n";
                    cout << "+--------------------------------------------+\n";
                    cout << termcolor::reset;
                } else if (choice == 4) {
                    filename = "parentAccounts.txt";
                    cout << termcolor::bold << termcolor::bright_cyan;
                    cout << "\n+--------------------------------------------+\n";
                    cout << "|              PARENT ACCOUNTS               |\n";
                    cout << "+--------------------------------------------+\n";
                    cout << termcolor::reset;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

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
                    }

                    break;
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
                break;
            }

            case 3: {
                string filename = "merchantAccounts.txt";
                accountsFile.open(filename, ios::app);

                cout << termcolor::bold << termcolor::bright_yellow;
                cout << "\n+--------------------------------------------+\n";
                cout << "|            MERCHANT ACCOUNTS               |\n";
                cout << "+--------------------------------------------+\n";
                cout << termcolor::reset;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                while (true) {
                    shop.shopname = promptNonEmptyInput("Shop Name: ");

                    if (isEmailTaken(filename, shop.shopname)) {
                        cout << termcolor::bright_red << "ERROR: Shop already exists!\n" << termcolor::reset;
                        continue;
                    }

                    break;
                }

                while (true) {
                    shop.username = promptNonEmptyInput("Username: ");

                    if (isUsernameTaken(filename, shop.username)) {
                        cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                        continue;
                    }

                    break;
                }
                
                shop.password = promptNonEmptyInput("Password: ");

                if (accountsFile.is_open()) {
                    accountsFile << shop.shopname << "," << shop.username << "," << shop.password << endl;
                    accountsFile.close();
                    cout << termcolor::green << "\nShop created successfully!\n" << termcolor::reset;
                    clearSystem(2000);
                } else {
                    cout << termcolor::bright_red << "\nERROR: Cannot open file\n" << termcolor::reset;
                    clearSystem(2000);
                }
                break;
            }
            case 5:
                cout << "\nReturning to menu...\n";
                clearSystem(1500);
                break;
            default:
                cout << termcolor::bright_red << "\nERROR: Invalid Choice!\n";
                continue;
        }

    } while (choice != 5);
}

void deleteAccount() {
    int choice;
    do {
       choice = printAccountTypeMenu("DELETE");

        switch (choice) {
            case 1: case 2: case 3: case 4: {
                string findemailOrShop, findusername, findpassword, filename;

                cout << termcolor::bold << termcolor::bright_yellow;
                cout << "\n+----------------------------------------+\n";
                cout << "|              ENTER DETAILS             |\n";
                cout << "+----------------------------------------+\n";
                cout << termcolor::reset;

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                string promptLabel = (choice == 3) ? "Shop Name: " : "CIIT Email: ";
                findemailOrShop = promptNonEmptyInput(promptLabel);
                findusername    = promptNonEmptyInput("Username: ");
                findpassword    = promptNonEmptyInput("Password: ");

                switch (choice) {
                    case 1: filename = "studentAccounts.txt"; break;
                    case 2: filename = "teacherAccounts.txt"; break;
                    case 3: filename = "merchantAccounts.txt"; break;
                    case 4: filename = "parentAccounts.txt"; break;
                }

                string concat = findemailOrShop + "," + findusername + "," + findpassword;
                deleteLine(filename, concat);
                clearSystem(2000);
                break;
            }

            case 5:
                system("cls");
                break;

            default:
                cout << termcolor::bright_red << "\nERROR: Enter a valid choice!\n" << termcolor::reset;
        }
    } while (choice != 5);
}

void editAccount() {
    int choice;

    do {
        string findemailOrShop, findusername, findpassword,
                emailOrShop, username, password,
                oldDetails, filename, line;

        choice = printAccountTypeMenu("EDIT");

        switch (choice) {
            case 1: case 2: case 3: case 4: {
                if (choice == 1) filename = "studentAccounts.txt";
                if (choice == 2) filename = "teacherAccounts.txt";
                if (choice == 3) filename = "merchantAccounts.txt";
                if (choice == 4) filename = "parentAccounts.txt";

                string label = (choice == 3) ? "Shop Name: " : "CIIT Email: ";

                cout << termcolor::bold << termcolor::bright_magenta;
                cout << "\n+-----------------------------------------+\n";
                cout << "|              FIND ACCOUNT               |\n";
                cout << "+-----------------------------------------+\n";
                cout << termcolor::reset;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                while (true) {
                findemailOrShop = promptNonEmptyInput(label);
                    findusername = promptNonEmptyInput("Username: ");
                    findpassword = promptNonEmptyInput("Password: ");
                    oldDetails = findemailOrShop + "," + findusername + "," + findpassword;

                    bool accountFound = false;
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
                }

                cout << termcolor::bold << termcolor::bright_magenta;
                cout << "\n+----------------------------------------+\n";
                cout << "|              NEW DETAILS               |\n";
                cout << "+----------------------------------------+\n";
                cout << termcolor::reset;

                while (true) {
                    emailOrShop = promptNonEmptyInput(label);

                    if (emailOrShop == findemailOrShop) break;

                    if (isEmailTaken(filename, emailOrShop)) {
                        cout << termcolor::bright_red << "ERROR: That " << ((choice == 3) ? "shop name" : "email") << " already exists!\n" << termcolor::reset;
                        continue;
                    }

                    break;
                }

                while (true) {
                    username = promptNonEmptyInput("Username: ");

                    if (username == findusername) break;

                    if (isUsernameTaken(filename, username)) {
                        cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                        continue;
                    }

                    break;
                }

                password = promptNonEmptyInput("Password: ");
                string newDetails = emailOrShop + "," + username + "," + password;

                editLine(filename, oldDetails, newDetails);
                clearSystem(2000);
                break;
            }

            case 5:
                system("cls");
                break;

            default:
                cout << termcolor::bright_red << "\nERROR: Invalid Choice!\n" << termcolor::reset;
                break;
        }

    } while (choice != 5);
}

void manageAccounts () {
    int choice;

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+--------------------------------+\n";
        cout << "|  " << termcolor::bright_yellow << "      MANAGE ACCOUNTS         " << termcolor::magenta << "|\n";
        cout << "+--------------------------------+\n";
        cout << "|  1. View all accounts          |\n";
        cout << "|  2. Create accounts            |\n";
        cout << "|  3. Delete account             |\n";
        cout << "|  4. Edit account information   |\n";
        cout << "|  5. Back to Dashboard          |\n";
        cout << "+--------------------------------+\n"<< termcolor::reset;

        choice = promptChoice(1, 5, "Choice: ");
        system("cls");

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