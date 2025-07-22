#include "Parent.h"
#include <iostream>
#include <limits>

using namespace std;

enum class ParentMenuOption { ViewBalance = 1, Transfer, Notifications, Transactions, Back };

void Parent::parentMain(string insertedEmail){
    setEmail(insertedEmail);
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
    int choice;

    cout << "Your child has " << getTokenBalance() << " tokens.\n";
    do {
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