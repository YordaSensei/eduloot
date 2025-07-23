#include "admin/admin_includes.h"

using namespace std;

void viewAccounts() {
    int choice;
    string line;

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|  " << termcolor::bright_yellow << "           VIEW              " << termcolor::magenta << "|\n";
        cout << "+-------------------------------+\n";

        cout << "|  1. Student                   |\n";
        cout << "|  2. Teacher                   |\n";
        cout << "|  3. Merchant                  |\n";
        cout << "|  4. Parent                    |\n";
        cout << "|  5. Back                      |\n";
        cout << "+-------------------------------+\n" << termcolor::reset;

        cout << termcolor::bright_yellow << "Choice: ";
        cin >> choice;
        cin.ignore();
        cout << termcolor::reset;
        clearSystem();
        
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
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|  " << termcolor::bright_yellow << "         CREATE              " << termcolor::magenta << "|\n";
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
        system("cls");

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
                }else if (choice == 2) {
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

                do {
                    cout << termcolor::bright_yellow << "CIIT Email: ";
                    getline(cin, acc.ciitEmail);
                    cout << termcolor::reset;

                    if (acc.ciitEmail.empty()) {
                        cout << termcolor::bright_red << "\nERROR: Email cannot be empty.\n" << termcolor::reset;
                        continue;
                    }

                    if (acc.ciitEmail.find("@ciit.edu.ph") == string::npos || acc.ciitEmail.find(" ") != string::npos) {
                        cout << termcolor::bright_red << "\nERROR: Please enter a valid CIIT Email (must contain @ciit.edu.ph and no spaces)\n" << termcolor::reset;
                        continue;
                    }

                    if (isEmailTaken(filename, acc.ciitEmail)) {
                        cout << termcolor::bright_red << "\nERROR: Account already exists!\n" << termcolor::reset;
                        continue;
                    }

                    break;
                } while (true);

                do {
                    cout << termcolor::bright_yellow << "Username: ";
                    getline(cin, acc.username);
                    cout << termcolor::reset;

                    if (acc.username.empty()) {
                        cout << termcolor::bright_red << "\nERROR: Username cannot be empty.\n" << termcolor::reset;
                        continue;
                    }

                    if (isUsernameTaken(filename, acc.username)) {
                        cout << termcolor::bright_red << "\nERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                        continue;
                    }

                    break;
                } while (true);

                do {
                    cout << termcolor::bright_yellow << "Password: ";
                    getline(cin, acc.password);
                    cout << termcolor::reset;

                    if (acc.password.empty()) {
                        cout << termcolor::bright_red << "\nERROR: Password cannot be empty.\n" << termcolor::reset;
                        continue;
                    }

                    break;
                } while (true);

                accountsFile.open(filename, ios::app);
                if (accountsFile.is_open()) {
                    accountsFile << acc.ciitEmail << "," << acc.username << "," << acc.password << endl;
                    accountsFile.close();
                    cout << termcolor::green << "\nAccount created successfully!\n" << termcolor::reset;
                    clearSystem();
                } else {
                    cout << termcolor::bright_red << "\nERROR: Cannot open file.\n" << termcolor::reset;
                    clearSystem();
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
                
                do {
                    cout << termcolor::bright_yellow << "Shop Name: ";
                    getline(cin, shop.shopname);
                    cout << termcolor::reset;

                    if (shop.shopname.empty()) {
                        cout << termcolor::bright_red << "ERROR: Shop name cannot be empty.\n" << termcolor::reset;
                        continue;
                    }

                    if (isEmailTaken(filename, shop.shopname)) {
                        cout << termcolor::bright_red << "ERROR: Shop already exists!\n" << termcolor::reset;
                        continue;
                    }

                    break;
                } while (true);

                do {
                    cout << termcolor::bright_yellow << "Username: ";
                    getline(cin, shop.username);
                    cout << termcolor::reset;

                    if (shop.username.empty()) {
                        cout << termcolor::bright_red << "ERROR: Username cannot be empty.\n" << termcolor::reset;
                        continue;
                    }

                    if (isUsernameTaken(filename, shop.username)) {
                        cout << termcolor::bright_red << "ERROR: Username already exists! Please try a different one.\n" << termcolor::reset;
                        continue;
                    }

                    break;
                } while (true);

                do {
                    cout << termcolor::bright_yellow << "Password: ";
                    getline(cin, shop.password);
                    cout << termcolor::reset;

                    if (shop.password.empty()) {
                        cout << termcolor::bright_red << "ERROR: Password cannot be empty.\n" << termcolor::reset;
                    } else {
                        break;
                    }
                } while (true);

                if (accountsFile.is_open()) {
                    accountsFile << shop.shopname << "," << shop.username << "," << shop.password << endl;
                    accountsFile.close();
                    cout << termcolor::green << "\nShop created successfully!\n" << termcolor::reset;
                    clearSystem();
                } else {
                    cout << termcolor::bright_red << "\nERROR: Cannot open file\n" << termcolor::reset;
                    clearSystem();
                }
                break;
            }
            case 5:
                cout << "\nReturning to menu...\n";
                clearSystem();
                break;
            default:
                cout << termcolor::bright_red << "\nERROR: Invalid Choice!\n";
                continue;
        }

    } while (choice != 5);
}

void deleteAccount() {
    int choice;
    string emailOrShop, username, password;
    string filename;

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|  " << termcolor::bright_yellow << "          DELETE             " << termcolor::magenta << "|\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. Student                   |\n";
        cout << "|  2. Teacher                   |\n";
        cout << "|  3. Merchant                  |\n";
        cout << "|  4. Parent                    |\n";
        cout << "|  5. Back                      |\n";
        cout << "+-------------------------------+\n";
        cout << termcolor::reset;

        while (true) {
            cout << termcolor::bright_yellow << "Choice: ";
            if (cin >> choice && choice >= 1 && choice <= 5) break;
            cout << termcolor::red << "Invalid choice. Please enter 1-5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        system("cls");

        switch (choice) {
            case 1: case 2: case 3: case 4: {
                string findemailOrShop, findusername, findpassword;

                cout << termcolor::bold << termcolor::bright_yellow;
                cout << "\n+----------------------------------------+\n";
                cout << "|              ENTER DETAILS             |\n";
                cout << "+----------------------------------------+\n";
                cout << termcolor::reset;

                cout << termcolor::bright_yellow;

                if (choice == 3)
                    cout << "Shop Name: ";
                else
                    cout << "CIIT Email: ";

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                getline(cin, findemailOrShop);
                while (findemailOrShop.empty()) {
                    cout << termcolor::red << "This field cannot be empty.\n Please enter a value: " << termcolor::reset;
                    getline(cin, findemailOrShop);
                }

                cout << "Username: ";
                getline(cin, findusername);
                while (findusername.empty()) {
                    cout << termcolor::red << "Username cannot be empty.\n Please enter a username: " << termcolor::reset;
                    getline(cin, findusername);
                }

                cout << "Password: ";
                getline(cin, findpassword);
                while (findpassword.empty()) {
                    cout << termcolor::red << "Password cannot be empty.\n Please enter a password: " << termcolor::reset;
                    getline(cin, findpassword);
                }

                cout << termcolor::reset;

                if (choice == 1) filename = "studentAccounts.txt"; 
                if (choice == 2) filename = "teacherAccounts.txt"; 
                if (choice == 3)filename = "merchantAccounts.txt"; 
                if (choice == 4)filename = "parentAccounts.txt"; 
            
                string concat = emailOrShop + "," + username + "," + password;
                deleteLine(filename, concat);
                clearSystem();
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

void editAccount () {
    int choice;
    string findemailOrShop, findusername, findpassword;
    string emailOrShop, username, password;
    string filename;

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|  " << termcolor::bright_yellow << "           EDIT               " << termcolor::magenta << "|\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. Student                   |\n";
        cout << "|  2. Teacher                   |\n";
        cout << "|  3. Merchant                  |\n";
        cout << "|  4. Parent                    |\n";
        cout << "|  5. Back                      |\n";
        cout << "+-------------------------------+\n";
        cout << termcolor::reset;

        while (true) {
            cout << termcolor::bright_yellow << "Choice: ";
            if (cin >> choice && choice >= 1 && choice <= 5) break;
            cout << termcolor::red << "Invalid choice. Please enter 1-5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        system("cls");

        switch (choice) {
            case 1: case 2: case 3: case 4: {
                if (choice == 1) filename = "studentAccounts.txt"; 
                if (choice == 2) filename = "teacherAccounts.txt"; 
                if (choice == 3)filename = "merchantAccounts.txt"; 
                if (choice == 4)filename = "parentAccounts.txt"; 

                cout << termcolor::bold << termcolor::bright_magenta;
                cout << "\n+-----------------------------------------+\n";
                cout << "|              FIND ACCOUNT               |\n";
                cout << "+-----------------------------------------+\n";
                cout << termcolor::reset;

                cout << termcolor::bright_yellow;

                if (choice == 3)
                    cout << "Shop Name: ";
                else
                    cout << "CIIT Email: ";

                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                
                getline(cin, findemailOrShop);
                while (findemailOrShop.empty()) {
                    cout << termcolor::red << "This field cannot be empty.\n Please enter a value: " << termcolor::reset;
                    getline(cin, findemailOrShop);
                }

                cout << "Username: ";
                getline(cin, findusername);
                while (findusername.empty()) {
                    cout << termcolor::red << "Username cannot be empty.\n Please enter a username: " << termcolor::reset;
                    getline(cin, findusername);
                }

                cout << "Password: ";
                getline(cin, findpassword);
                while (findpassword.empty()) {
                    cout << termcolor::red << "Password cannot be empty.\n Please enter a password: " << termcolor::reset;
                    getline(cin, findpassword);
                }
                cout << termcolor::reset;

                string oldDetails = findemailOrShop + "," + findusername + "," + findpassword;

                cout << termcolor::bold << termcolor::bright_magenta;
                cout << "\n+----------------------------------------+\n";
                cout << "|              NEW DETAILS               |\n";
                cout << "+----------------------------------------+\n";
                cout << termcolor::reset;

                cout << termcolor::bright_magenta;

                if (choice == 3)
                    cout << "Shop Name: ";
                else
                    cout << "Email: ";

                getline(cin, emailOrShop);
                while (emailOrShop.empty()) {
                    cout << termcolor::red << "This field cannot be empty.\n Please enter a value: " << termcolor::reset;
                    getline(cin, emailOrShop);
                }

                cout << "Username: ";
                getline(cin, username);
                while (username.empty()) {
                    cout << termcolor::red << "Username cannot be empty.\n Please enter a username: " << termcolor::reset;
                    getline(cin, username);
                }

                cout << "Password: ";
                getline(cin, password);
                while (password.empty()) {
                    cout << termcolor::red << "Password cannot be empty.\n Please enter a password: " << termcolor::reset;
                    getline(cin, password);
                }

                cout << termcolor::reset;

                string newDetails = emailOrShop + "," + username + "," + password;

                editLine (filename, oldDetails, newDetails);
                clearSystem();
                break;
            }
            case 5: 
                system("cls");
                break;
            default:
                cout << termcolor::bright_red << "\nERROR: Invalid Choice!\n" << termcolor::reset;
                continue;
        }

    } while (choice !=5);
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

        while (true) {
            cout << termcolor::bright_yellow << "Choice: ";
            if (cin >> choice && choice >= 1 && choice <= 5) break;
            cout << termcolor::red << "Invalid choice. Please enter 1-5.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
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