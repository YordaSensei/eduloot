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

// HELPER FUNCTIONS -------------------------------------------------------------------------------------------------------------------------------------------

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
    ofstream tempFile ("tempFile.txt");

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
    rename("tempFile.txt", filename.c_str());

    if (found) {
        cout << "\n-- Successful --\n";
    } else {
        cout << "\n-- NOT found (check spelling/case) --\n";
    }
}

void editLine (const string &filename, const string &targetLine, const string &updatedLine) {
    ifstream inFile (filename);
    ofstream tempFile ("tempFile.txt");

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
    rename("tempFile.txt", filename.c_str());

    if (found) {
        cout << "\n-- Edited successfully --\n";
    } else {
        cout << "\n-- NOT found --\n";
    }
}

void updateTotalTokens (int change) {
    int systemTokens = 0;
    string line;

    ifstream inFile ("tokensSystem.txt");
    if (inFile.is_open()) {
        getline(inFile, line);
        if (!line.empty()){
            systemTokens = stoi(line);
        }
        inFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }

    systemTokens += change;
    if (systemTokens < 0) systemTokens = 0;

    ofstream outFile ("tokensSystem.txt");
    if(outFile.is_open()) {
        outFile << systemTokens << endl;
        outFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }
}

void updateTotalMoney (int pesos) {
    int systemMoney = 0;
    const int toke_rate = 3;
    string line;

    ifstream inFile ("moneySystem.txt");
    if (inFile.is_open()) {
        getline(inFile, line);
        if (!line.empty()){
            systemMoney = stoi(line);
        }
        inFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }

    systemMoney += pesos;
    if (systemMoney < 0) systemMoney = 0;

    ofstream outFile ("moneySystem.txt");
    if(outFile.is_open()) {
        outFile << systemMoney << endl;
        outFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }
}

// MANAGE ACCOUNTS -------------------------------------------------------------------------------------------------------------------------------------

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

// NOTIFICATIONS ------------------------------------------------------------------------------------------------------------------------------------------

void notifications () {
    cout << "\n--- Viewing Notifications ---\n";

    struct NotificationFile {
        string title;
        string filename;
    };

    NotificationFile notifFiles[] = {
        {"Product Add Requests", "productReq.txt"},
        {"Product Delete Requests", "deleteProductReq.txt"},
        {"Merchant Concerns", "concerns.txt"},
        {"Merchant Cash Out Requests", "cashout.txt"},
        {"Emergency Fund Requests", "emergencyfunds.txt"},
        {"Student Balances", "studentBalance.txt"},
        {"Student Accomplished Quests", "studentAccomplishedQuests.txt"}
    };

    for (const auto& notif : notifFiles) {
        cout << "\n[" << notif.title << "]\n";
        ifstream file(notif.filename);

        if (!file) {
            cout << "(No file found: " << notif.filename << ")\n";
            continue;
        }

        string line;
        bool empty = true;
        while (getline(file, line)) {
            empty = false;
            cout << "- " << line << endl;
        }

        if (empty) {
            cout << "(No pending entries)\n";
        }

        file.close();
    }
}

// QUESTS --------------------------------------------------------------------------------------------------------------------------------------------------

void viewQuests () {
    ifstream inFile ("quests.txt");
    string line;

     if (!inFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    cout << "\n--- Available Quests ---\n";
    cout << "--------------------------\n";

    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

void approveStudentQuests () {
    string readFile = "studentAccomplishedQuests.txt";
    string line, student, quest;
    int tokenAmount;

    // Show all completed quests
    cout << "\n--- Quests Completed by Students ---\n";
    ifstream inFile(readFile);
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    // Input details for approval
    cout << "\n--- Enter Details to Approve ---\n";
    cout << "Student Username: ";
    getline(cin, student);
    cout << "Quest Name: ";
    getline(cin, quest);
    cout << "Token Amount: ";
    cin >> tokenAmount;
    cin.ignore();

    string approvedLine = student + ", " + quest + ", " + to_string(tokenAmount);
    deleteLine(readFile, approvedLine);

    bool found = false;
    string walletFile = "studentBalance.txt";
    ifstream walletIn(walletFile);
    ofstream tempFile("tempBalance.txt");
    string walletLine;

    while (getline(walletIn, walletLine)) {
        size_t pos = walletLine.find(',');
        string username = walletLine.substr(0, pos);
        int balance = stoi(walletLine.substr(pos + 1));

        if (username == student) {
            balance += tokenAmount;
            tempFile << username << ", " << balance << endl;
            found = true;
        } else {
            tempFile << walletLine << endl;
        }
    }

    walletIn.close();

    if (!found) {
        tempFile << student << ", " << tokenAmount << endl;
    }

    tempFile.close();
    remove(walletFile.c_str());
    rename("tempBalance.txt", walletFile.c_str());

    ofstream outFile("ApprovedQuests.txt", ios::app);
    outFile << approvedLine << endl;
    outFile.close();

    cout << "\nQuest Approved and " << tokenAmount << " tokens added to " << student << "'s wallet.\n";
}

void createQuest () {
    int tokenAmount;
    string quest;

    cout << "\n--- Create Quests ---\n";
    cout << "-----------------------\n";
    cout << "Quest: ";
    getline (cin, quest);
    cout << "Token Reward: ";
    cin >> tokenAmount;
    cin.ignore();

    string concat = quest + ", " + to_string(tokenAmount);

    ofstream outFile("quests.txt", ios::app);
    if (!outFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    outFile << concat << endl;
    outFile.close();
}

void deleteQuest () {
    string quest;
    int tokenAmount;
    string filename = "quests.txt";

    cout << "\n--- Delete Quest ---\n";
    cout << "----------------------\n";
    cout << "Enter the quest: ";
    getline (cin, quest);
    cout << "Enter Token Amount: ";
    cin >> tokenAmount;

    string concat = quest + ", " + to_string(tokenAmount);
    deleteLine(filename, concat);
}

void questsTab () {
    int choice;

    do {
        cout << "\n--- Quests Tab ---\n";
        cout << "--------------------\n";
        cout << "1. View Available Quests\n";
        cout << "2. Approve Student Quest\n";
        cout << "3. Create Quest\n";
        cout << "4. Delete Quest\n";
        cout << "5. Back\n";
        cout << "--------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                viewQuests();
                break;
            case 2:
                approveStudentQuests();
                break;
            case 3:
                createQuest();
                break;
            case 4:
                deleteQuest();
                break;
            case 5:
                break;
            default:
                cout << "\nERROR: Invalid choice!\n";
                continue;
        }
    } while (choice != 5);
}

// MERHCANT REQUESTS ----------------------------------------------------------------------------------------------------------------------------------------

void approveMerchantRequests () {
    int choice, price, quantity;
    string file, name, desc;
    ifstream inFile;
    ofstream outFile;

    do {
        cout << "\n--- Select Request Type ---\n";
        cout << "-----------------------------\n";
        cout << "1. Products\n";
        cout << "2. Concerns\n";
        cout << "3. Cash Out\n";
        cout << "4. Back\n";
        cout << "------------------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                cout << "\n--- Product Requests ---\n";
                cout << "-----------------------------\n";
                cout << "1. Add Product\n";
                cout << "2. Delete Product\n";
                cout << "3. Edit Product\n";
                cout << "4. Back\n";
                cout << "------------------------------\n";
                cout << "Choice: ";
                cin >> choice;
                cin.ignore();

                switch (choice) {
                    case 1: {
                        string file = "productReq.txt";
                        string productLine;

                        ifstream inFile(file);
                        cout << "\n--- Pending Add Product Requests ---\n";
                        while (getline(inFile, productLine)) {
                            if (productLine.find("add,") == 0) {
                                cout << productLine << endl;
                            }
                        }
                        inFile.close();

                        cout << "\n--- Approve Request ---\n";
                        cout << "Enter full request line to approve (copy-paste exactly):\n";
                        getline(cin, productLine);

                        ofstream approvedFile("approvedReq.txt", ios::app);
                        approvedFile << productLine << endl;
                        approvedFile.close();

                        string productEntry = productLine.substr(4); 
                        ofstream prodFile("productList.txt", ios::app);
                        prodFile << productEntry << endl;
                        prodFile.close();

                        deleteLine("productReq.txt", productLine);

                        cout << "\nProduct approved and added.\n";
                        break;
                    }


                    case 2: {
                        cout << "\n--- Delete Product ---\n";
                        cout << "Product Name: ";
                        getline(cin, name);
                        cout << "Price: ";
                        cin >> price;
                        cin.ignore();
                        cout << "Quantity: ";
                        cin >> quantity;
                        cin.ignore();
                        cout << "Description: ";
                        getline(cin, desc);

                        string target = "add," + name + "," + to_string(price) + "," + to_string(quantity) + "," + desc;
                        deleteLine("productList.txt", target);
                        break;
                    }

                    case 3: {
                        cout << "\n--- Edit Product ---\n";
                        cout << "[Old Product Info]\n";
                        string oldName, oldDesc;
                        int oldPrice, oldQuantity;
                        cout << "Name: ";
                        getline(cin, oldName);
                        cout << "Price: ";
                        cin >> oldPrice;
                        cin.ignore();
                        cout << "Quantity: ";
                        cin >> oldQuantity;
                        cin.ignore();
                        cout << "Description: ";
                        getline(cin, oldDesc);

                        string oldLine = "add," + oldName + "," + to_string(oldPrice) + "," + to_string(oldQuantity) + "," + oldDesc;

                        cout << "\n[New Product Info]\n";
                        cout << "New Name: ";
                        getline(cin, name);
                        cout << "New Price: ";
                        cin >> price;
                        cin.ignore();
                        cout << "New Quantity: ";
                        cin >> quantity;
                        cin.ignore();
                        cout << "New Description: ";
                        getline(cin, desc);

                        string newLine = name + "," + to_string(price) + "," + to_string(quantity) + "," + desc;

                        editLine("productList.txt", oldLine, newLine);
                        break;
                    }
                }
                break;
            }

            case 2: {
                string concernLine, merchant;
                file = "concerns.txt";
                inFile.open(file);

                cout << "\n--- Pending Merchant Concerns ---\n";
                while (getline(inFile, concernLine)) {
                    cout << concernLine << endl;
                }
                inFile.close();

                cout << "\n--- Approve Concern ---\n";
                cout << "Enter full concern line to approve (copy-paste or retype):\n";
                getline(cin, concernLine);

                outFile.open("approvedReq.txt", ios::app);
                outFile << "concern," + concernLine << endl;
                outFile.close();

                deleteLine("concerns.txt", concernLine);
                break;
            }

            case 3: {
                string cashoutLine;
                file = "cashout.txt";
                inFile.open(file);

                cout << "\n--- Pending Cash Out Requests ---\n";
                while (getline(inFile, cashoutLine)) {
                    cout << cashoutLine << endl;
                }
                inFile.close();

                cout << "\n--- Approve Cash Out ---\n";
                cout << "Enter full cash out line to approve (copy-paste or retype):\n";
                getline(cin, cashoutLine);

                outFile.open("approvedReq.txt", ios::app);
                outFile << "cashout," + cashoutLine << endl;
                outFile.close();

                deleteLine("cashout.txt", cashoutLine);
                break;
            }

            case 4:
                break;

            default:
                cout << "\nERROR: Invalid choice!\n";
                break;
        }

    } while (choice != 4);
}

void merchantRequests() {
    int choice;

    do {
        cout << "\n--- Merchant Requests ---\n";
        cout << "---------------------------\n";
        cout << "1. View Requests\n";
        cout << "2. Back to dashboard\n";
        cout << "---------------------------\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                approveMerchantRequests();
                break;
            case 2:
                break;
            default:
                cout << "\nERROR: Invalid choice!\n";
                continue;
        }
    } while (choice != 2);
}

// BANK -----------------------------------------------------------------------------------------------------------------------------------------------------

void bank () {
    int totalTokens = 0, totalMoney = 0, tokensOut = 0, tokensLeft = 0, topUp;
    string line;
    const int tokenRate = 3;

    ifstream tokenFile ("tokensOut.txt");
    if (tokenFile.is_open()) {
        while (getline(tokenFile, line)) {
            size_t pos = line.find(",");
            if (pos != string::npos) {
                string tokens = line.substr(pos + 1);
                int token = stoi(tokens);
                tokensOut += token;
            }
        }
        tokenFile.close();
    } else {
        cout << "\nERROR opening tokensOut.txt\n";
    }

    ifstream adminFile ("tokensSystem.txt");
    if (adminFile.is_open()) {
        while (getline(adminFile, line)) {
            int token = stoi(line);
            tokensLeft += token;
        }
        adminFile.close();
    } else {
        cout << "\nERROR opening adminTokens.txt\n";
    }

    ifstream moneyFile ("moneySystem.txt");
    if (adminFile.is_open()) {
        while (getline(moneyFile, line)) {
            int money = stoi(line);
            totalMoney = money;
        }
        adminFile.close();
    } else {
        cout << "\nERROR opening adminTokens.txt\n";
    }

    totalTokens = tokensOut + tokensLeft;

    cout << "\n--- BANK SUMMARY ---\n";
    cout << "Total Tokens (in system):   " << totalTokens << " tokens (P" << totalTokens * tokenRate << ")\n";
    cout << "Tokens Out:                 " << tokensOut << " tokens (P" << tokensOut * tokenRate << ")\n";
    cout << "Total Money (in system):    " << "P" << totalMoney << "\n";
    cout << "-----------------------\n";
    cout << "Admin Token Reserve:        " << tokensLeft << " tokens (P" << tokensLeft * tokenRate << ")\n";

    int choice;
    cout << "\nAdd more tokens to the system?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";
    cout << "--------------------------------\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nEnter number of tokens to add: ";
        cin >> topUp;

        if (topUp > 0) {
            updateTotalTokens(topUp);
            cout << "\nSuccessfully added " << topUp << " tokens (₱" << topUp * tokenRate << ") to the system.\n";
        } else {
            cout << "\nInvalid token amount.\n";
        }
    } else if (choice == 2) {
        cout << "\nReturning to dashboard...\n";
    } else {
        cout << "\nInvalid choice.\n";
    }
}

// TRANSACTIONS ---------------------------------------------------------------------------------------------------------------------------------------------

void viewTransactions () {
    cout << "\n--- Viewing All Transactions ---\n";

    struct TransactionFile {
        string title;
        string filename;
    };

    TransactionFile transactionFiles[] = {
        {"Token Purchases", "tokenPurchases.txt"},
        {"Token Refunds", "tokenRefunds.txt"},
        {"Token to Cash Conversions", "tokenConversions.txt"},
        {"Quest Approvals", "ApprovedQuests.txt"},
        {"Merchant Cash Outs", "cashout.txt"}
    };

    for (const auto& tx : transactionFiles) {
        cout << "\n[" << tx.title << "]\n";
        ifstream file(tx.filename);

        if (!file) {
            cout << "(No file found: " << tx.filename << ")\n";
            continue;
        }

        string line;
        bool empty = true;
        while (getline(file, line)) {
            empty = false;
            cout << "- " << line << endl;
        }

        if (empty) {
            cout << "(No entries found)\n";
        }

        file.close();
    }
}


void adminMain() {
    int choice;

    do {
        cout << "\n--- Good day, Admin! ---\n";
        cout << "1. Manage accounts\n";
        cout << "2. Notifications\n";
        cout << "3. Quests Tab\n";
        cout << "4. Merchant Requests\n";
        cout << "5. Bank\n";
        cout << "6. View Transactions\n";
        cout << "7. Log Out\n";
        cout << "--------------------------\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageAccounts();
                break;
            case 2:
                notifications();
                break;
            case 3:
                questsTab();
                break;
            case 4:
                merchantRequests();
                break;
            case 5:
                bank();
                break;
            case 6:
                viewTransactions();
                break;
            case 7:
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }
    } while (choice != 7);

    cout << "\nLogging out...\n";
}