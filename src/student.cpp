#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "student_helpers.h"
using namespace std;

#include "student_wallet.cpp"
#include "student_purchase.cpp"
#include "student_quests.cpp"

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

void studentMain(string email) {
    int choice;

    do {
        cout << "\n--- Good day, Student! ---\n";
        cout << "1. Wallet\n";
        cout << "2. Purchase\n";
        cout << "3. Quests\n";
        cout << "4. Notification\n";
        cout << "5. Transactions\n";
        cout << "6. Request Emergency Fund\n";
        cout << "7. Log Out\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                wallet(email);
                break;
            case 2:
                purchase(email);
                break;
            case 3:
                quests(email);
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
}