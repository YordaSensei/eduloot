#include "Parent.h"
#include <iostream>
#include <limits>

using namespace std;
Parent::Parent(const string& name, double tokenBalance) : User(name, tokenBalance) {}
enum class ParentMenuOption { ViewBalance = 1, Transfer, Notifications, Transactions, Back };

void Parent::parentMain(){
    int choice;

    do {
        cout << "\n--- Good day, Parent " << getName() << "! ---\n";
        cout << "1. Child's Wallet\n";
        cout << "2. Transfer Tokens\n";
        cout << "3. Notifications\n";
        cout << "4. Transactions\n";
        cout << "5. Log Out\n";
        cout << "Choice: ";
        cin >> choice;

        switch(static_cast<ParentMenuOption>(choice)) {
            case ParentMenuOption::ViewBalance:
                viewBalance();
                break;
            case ParentMenuOption::Transfer:
                double amount;
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


void Parent::viewBalance() const {
    int choice;

    cout << "Your child has " << getTokenBalance() << " tokens.\n";
    do {
        cout << "1. Back\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void Parent::transferToChild(double amount) {
    if (amount > 0 && amount <= getTokenBalance()) {
        setTokenBalance(getTokenBalance() - amount);
        cout << "Successfully transferred " << amount << " pesos.\n";
    } else {
        cout << "Invalid transfer amount/Insufficient balance.\n";
    }
}