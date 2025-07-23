#include "User.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "admin/admin_helpers.h"
#include "product_helpers.h"
#include "merchant_helpers.h"

using namespace std;
    
enum class WalletOption { ViewBalance = 1, Purchase, Convert, Back };

void User::wallet() {
    int choice;

    do {
        cout << "\n--- Token Wallet ---\n";
        cout << "1. View Balance\n";
        cout << "2. Purchase Tokens\n";
        cout << "3. Convert to Cash\n";
        cout << "4. Back to Home\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 4)) {
            continue;
        }

        switch(static_cast<WalletOption>(choice)) {
            case WalletOption::ViewBalance:
                viewBalance();
                break;
            case WalletOption::Purchase:
                purchaseTokens();
                break;
            case WalletOption::Convert:
                convertTokens();
                break;
            case WalletOption::Back:
            break;
        }
    } while (choice != 4);
}

void User::viewBalance() {
    ifstream inFile(userType + "Balance.txt");

    if (!inFile.is_open()) {
        cout << "Error opening balance file.\n";
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

                getline(split, this->email, ',');
                getline(split, strBalance);

                if (this->email == email) {
                    this->tokenBalance = stoi(strBalance);
                    cout << "Token Balance: " << this->tokenBalance << endl;
                    found = true;
                    break;
                }
            }
        }
        inFile.close();

        if (!found) {
            this->tokenBalance = 0;
            cout << "Token Balance: 0\n";
        }

        cout << "1. Back\n";
        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void User::purchase() {
    int choice;

    do {
        cout << "\n--- Make a Purchase ---\n";
        cout << "1. Scan QR Code\n";
        cout << "2. Input Merchant Code\n";
        cout << "3. Back to Home\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 3)) {
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Please input QR CODE : \n"; //temp
                break;
            case 2:
                string code;
                cout << "Merchant Code : ";
                cin >> code;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
        }
    } while (choice != 3);
}

void User::purchaseTokens() {
    int choice = 0;

    do {
        cout << "\n--- Purchase Tokens ---\n";
        cout << "\n---------------------\n";
        cout << "1. Input token amount\n";
        cout << "2. Back to Home\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 2)) {
            continue;
        }

        switch(choice) {
            case 1:
                int change;
                if (!getValidInput(change, "Please input token amount : ", "Invalid amount entered.")) {
                    continue;
                }
                updateTotalTokens(change);
                break;
            case 2:
                break;
        }
    } while (choice !=2);
}

void User::convertTokens() {
    int choice;

    do {
        cout << "\n--- Convert Tokens ---\n";
        cout << "\n---------------------\n";
        cout << "1. Back to Home\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }

    } while (choice != 1);
}

void User::notifications() {
    int choice;

    do {
        cout << "\n--- Notifications ---\n";
        cout << "\n---------------------\n";
        cout << "1. Back to Home\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void User::transactions() {
    int choice;

    do {
        cout << "\n--- Transaction History ---\n";
        cout << "\n---------------------------\n";
        cout << "1. Back to Home\n";

        if (!getValidInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}