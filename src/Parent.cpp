#include "Parent.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

enum class ParentMenuOption { ViewBalance = 1, Transfer, Notifications, Transactions, Back };

void Parent::parentMain(string insertedEmail, string insertedChildEmail){
    setEmail(insertedEmail);
    setInsertedChildEmail(insertedChildEmail);
    setUserType("parent");

    int choice;
    do {
        cout << "\n--- Good day, Parent! ---\n";
        cout << "1. Child's Wallet\n";
        cout << "2. Transfer Tokens\n";
        cout << "3. Notifications\n";
        cout << "4. Transactions\n";
        cout << "5. Log Out\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 5)) {
            continue;
        }

        switch(static_cast<ParentMenuOption>(choice)) {
            case ParentMenuOption::ViewBalance:
                viewBalance();
                break;
            case ParentMenuOption::Transfer:
                int amount;
                if (!(cin >> amount)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid amount entered.\n";
                    continue;
                }
                transferToChild(amount);
                break;
            case ParentMenuOption::Notifications:
                notifications();
                break;
            case ParentMenuOption::Transactions:
                transactions();
                break;
            case ParentMenuOption::Back:
                break;
        }
    } while (choice != 5);

    cout << "Logging Out...";

}

void Parent::viewBalance() {
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
                    cout << "Child's Token Balance: " << this->childTokenBalance << endl;
                    found = true;
                    break;
                }
            }
        }
        inFile.close();

        if (!found) {
            this->childTokenBalance = 0;
            cout << "Child's Token Balance: 0\n";
        }

        cout << "1. Back\n";
        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void Parent::transferToChild(int amount) {
    if (amount > 0 && amount <= getTokenBalance()) {
        updateTotalTokens(getTokenBalance() - amount);

        
        cout << "Successfully transferred " << amount << " tokens.\n";
    } else {
        cout << "Invalid transfer amount/Insufficient balance.\n";
    }
}