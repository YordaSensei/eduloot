#include "../modules/Parent.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>

using namespace std;

enum class ParentMenuOption { Wallet = 1, viewChildBal, Transfer, Notifications, Transactions, Back };

void Parent::parentMain(string insertedEmail, string insertedChildEmail){
    setEmail(insertedEmail);
    setInsertedChildEmail(insertedChildEmail);
    setUserType("parent");

    int choice;
    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_cyan << "    Good day, Parent!      " << termcolor::blue << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. Wallet                   |\n";
        cout << "|  2. Child's Balance          |\n";
        cout << "|  3. Transfer Tokens          |\n";
        cout << "|  4. Notifications            |\n";
        cout << "|  5. Transactions             |\n";
        cout << "|  6. Log Out                  |\n";
        cout << "+------------------------------+\n"<< termcolor::reset;

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 6)) {
            continue;
        }

        switch(static_cast<ParentMenuOption>(choice)) {
            case ParentMenuOption::Wallet:
                wallet();
                break;
            case ParentMenuOption::viewChildBal:
                viewChildBal();
                break;
            case ParentMenuOption::Transfer:
                transferToChild();
                break;
            case ParentMenuOption::Notifications:
                notifications();
                break;
            case ParentMenuOption::Transactions:
                transactions();
                break;
            case ParentMenuOption::Back:
                cout << termcolor::red << "Logging Out...";
                clearSystem();
                break;
        }
    } while (choice != 6);
}

void Parent::viewChildBal() {
    ifstream inFile("studentBalance.txt");
    if (!inFile.is_open()) {
        cout << "Error opening student's balance file.\n";
        return;
    }

    string line;
    bool found = false;
    int choice;

    do {
        while (getline(inFile, line)) {
            if (!line.empty()) {
                string strBalance;
                stringstream split(line);

                getline(split, this->childEmail, ',');
                getline(split, strBalance);

                if (this->childEmail == childEmail) {
                    this->childTokenBalance = stoi(strBalance);
                    cout << "\n+------------------------------+\n";
                    cout << "|" << termcolor::bright_cyan << " Child's Token Balance: " << setw(13) << left <<  this->childTokenBalance << termcolor::blue << "|";
                    cout << "\n+------------------------------+\n";
                    found = true;
                    break;
                }
            }
        }
        inFile.close();

        if (!found) {
            this->childTokenBalance = 0;
            cout << "\n+------------------------------+\n";
            cout << "|" << termcolor::bright_cyan << setw(30) << left << "  Token Balance: 0" << termcolor::blue << "|";
            cout << "\n+------------------------------+\n";
        }

        cout << "1. " << termcolor::bright_cyan << "Back to Home\n";
        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void Parent::transferToChild() {
    int amount;
    cout << "\n--- Transfer Tokens to Child ---\n";
    cout << "Your current balance: " << getTokenBalance() << " tokens\n";
    cout << "Child's current balance: " << childTokenBalance << " tokens\n";
    cout << "Enter amount to transfer: ";
    
    if (!getNumericInput(amount, "", "Invalid amount. Please enter a positive number.", 1, getTokenBalance())) {
        return;
    }

    char confirm;
    cout << "Are you sure you want to transfer " << amount << " tokens to your child? (y/n): ";
    if (!getYesNoInput(confirm, "", "Invalid choice.")) {
        return;
    }

    if (confirm == 'y') {
        
        int newParentBalance = getTokenBalance() - amount;
        updateBalanceInFile(newParentBalance);
        recordTransaction("TRANSFER_OUT", -amount, newParentBalance);

        
        int newChildBalance = childTokenBalance + amount;
        updateChildBalance(childEmail, newChildBalance);
        recordChildTransaction(childEmail, "TRANSFER_IN", amount, newChildBalance);

        cout << "Transfer successful!\n";
        cout << "Your new balance: " << newParentBalance << " tokens\n";
        cout << "Child's new balance: " << newChildBalance << " tokens\n";
    } else {
        cout << "Transfer cancelled.\n";
    }
}

void Parent::updateChildBalance(const string& childEmail, int newBalance) {
    vector<string> lines;
    string line;
    bool found = false;
    
    ifstream inFile("studentBalance.txt");
    
    while (getline(inFile, line)) {
        if (!line.empty()) {
            size_t pos = line.find(',');
            string fileEmail = line.substr(0, pos);
            
            if (fileEmail == childEmail) {
                lines.push_back(childEmail + "," + to_string(newBalance));
                found = true;
            } else {
                lines.push_back(line);
            }
        }
    }
    inFile.close();
    
    if (!found) {
        lines.push_back(childEmail + "," + to_string(newBalance));
    }
    
    ofstream outFile("studentBalance.txt");
    for (const auto& line : lines) {
        outFile << line << "\n";
    }
    outFile.close();
}

void Parent::recordChildTransaction(const string& childEmail, const string& type, int amount, int newBalance) {
    time_t now = time(0);
    string dt = ctime(&now);
    dt.pop_back();

    ofstream outFile("studentTokenTransactions.txt", ios::app);
    if (outFile.is_open()) {
        outFile << childEmail << "," << type << "," << amount << "," << newBalance << "," << dt << endl;
        outFile.close();
    }
}