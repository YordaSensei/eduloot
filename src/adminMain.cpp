#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

struct Account {
    string ciitEmail;       
    string username;
    string password;
};

struct Merchant {
    string shopname;      
    string username;
    string password;
};

bool isUsernameTaken (const string &accountsFile, const string &usernameToCheck) {
    ifstream file (accountsFile);
    if (!file.is_open()) return false;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;

        string username = line.substr(pos1 + 2, pos2 - pos1 - 2);
        
        if (username == usernameToCheck) {
            return true;
        }
    }

    return false;
}

bool isEmailTaken (const string &accountsFile, const string &emailToCheck) {
    ifstream file (accountsFile);
    if (!file.is_open()) return false;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        string email = line.substr(0, pos1);
        
        if (email == emailToCheck) {
            return true;
        }
    }

    return false;
}

void deleteLine (const string &filename, const string &targetLine) {
    ifstream inFile (filename);
    ofstream tempFile ("tempAccounts.txt");

    if (!inFile || !tempFile) {
    cout << "\nERROR: Failed to access file.\n";
    return;
    }   

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line != targetLine) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("tempAccounts.txt", filename.c_str());

    if (found) {
        cout << "\n-- Account deleted successfully --\n";
    } else {
        cout << "\n-- Account NOT found --\n";
    }
}

void editLine (const string &filename, const string &targetLine, const string &updatedLine) {
    ifstream inFile (filename);
    ofstream tempFile ("tempAccounts.txt");

    if (!inFile || !tempFile) {
    cout << "\nERROR: Failed to access file.\n";
    return;
    }   

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line == targetLine) {
            tempFile << updatedLine << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("tempAccounts.txt", filename.c_str());

    if (found) {
        cout << "\n-- Account edited successfully --\n";
    } else {
        cout << "\n-- Account NOT found --\n";
    }
}

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
                    accountsFile << acc.ciitEmail << ", " << acc.username << ", " << acc.password << endl;
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
                    accountsFile << shop.shopname << ", " << shop.username << ", " << shop.password << endl;
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
            
                string concat = emailOrShop + ", " + username + ", " + password;
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

                string oldDetails = findemailOrShop + ", " + findusername + ", " + findpassword;

                cout << "\n-- Enter New Account Details --\n";

                if (choice == 3)cout << "Shop Name: ";
                else cout << "CIIT Email: ";

                getline(cin, emailOrShop);

                cout << "Username: ";
                getline(cin, username);

                cout << "Password: ";
                getline(cin, password);

                string newDetails = emailOrShop + ", " + username + ", " + password;

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

int main() {
    int choice;

    do {
        cout << "\n--- Good day, Admin! ---\n";
        cout << "1. Manage accounts\n";
        cout << "2. Notifications\n";
        cout << "3. Quests Tab\n";
        cout << "4. Merchant Requests\n";
        cout << "5. Token Bank\n";
        cout << "6. Money Bank\n";
        cout << "7. View Transactions\n";
        cout << "8. Log Out\n";
        cout << "--------------------------\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageAccounts();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }
    } while (choice != 8);

    cout << "\nLogging out...\n";
}
