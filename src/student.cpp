#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void viewBalance() {
    int choice;

    cout << "You have" << " tokens.\n";
    do {
        cout << "1. Back\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void wallet() {
    int choice;

    do {
        cout << "\n--- Token Wallet ---\n";
        cout << "1. View Balance\n";
        cout << "2. Purchase Tokens\n";
        cout << "3. Convert to Cash\n";
        cout << "4. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                viewBalance();
                break;
            case 2:
                break;
            case 3:
                break;
        }
    } while (choice != 4);
}

void purchase() {
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
                break;
            case 2:
                break;
        }
    } while (choice != 3);
}

void rewards() {
    int choice;

    do {
        cout << "\n--- Tasks ---\n";
        cout << "\n-------------\n";
        cout << "1. Tasks Completed\n";
        cout << "2. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                break;
        }
    } while (choice != 2);
}

void notification() {
    int choice;

    do {
        cout << "\n--- Notifications ---\n";
        cout << "\n---------------------\n";
        cout << "1. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void transaction() {
    int choice;

    do {
        cout << "\n--- Transaction History ---\n";
        cout << "\n---------------------------\n";
        cout << "1. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

int main() {
    int choice;

    do {
        cout << "\n--- Good day, Student! ---\n";
        cout << "1. Wallet\n";
        cout << "2. Purchase\n";
        cout << "3. Rewards / Tasks\n";
        cout << "4. Notification\n";
        cout << "5. Transactions\n";
        cout << "6. Request Emergency Fund\n";
        cout << "7. Log Out\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                wallet();
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
        }
    } while (choice != 7);

    cout << "Logging Out...";
    return 0;
}