#include "User.h"
#include <iostream>
#include <limits>

using namespace std;

User::User(const string& name, double tokenBalance) : name(name), tokenBalance(tokenBalance) {}
enum class WalletOption { ViewBalance = 1, Purchase, Convert, Back };

void User::wallet() const {
    int choice;

    do {
        cout << "\n--- Token Wallet ---\n";
        cout << "1. View Balance\n";
        cout << "2. Purchase Tokens\n";
        cout << "3. Convert to Cash\n";
        cout << "4. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch(static_cast<WalletOption>(choice)) {
            case WalletOption::ViewBalance:
                viewBalance();
                break;
            case WalletOption::Purchase:
                purchase();
                break;
            case WalletOption::Convert:
                convert();
                break;
            case WalletOption::Back:
            break;
        }
    } while (choice != 4);
}

void User::viewBalance() const {
    int choice;

    cout << "You have " << getTokenBalance() << " tokens.\n";
    do {
        cout << "1. Back\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void User::purchase() const {
    int choice;

    do {
        cout << "\n--- Make a Purchase ---\n";
        cout << "1. Scan QR Code\n";
        cout << "2. Input Merchant Code\n";
        cout << "3. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

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

void User::convert() const {
    int choice;

    do {
        cout << "\n--- Convert Tokens ---\n";
        cout << "\n---------------------\n";
        cout << "1. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void User::notifications() const {
    int choice;

    do {
        cout << "\n--- Notifications ---\n";
        cout << "\n---------------------\n";
        cout << "1. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void User::transactions() const {
    int choice;

    do {
        cout << "\n--- Transaction History ---\n";
        cout << "\n---------------------------\n";
        cout << "1. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}