#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "admin_manageAccounts.cpp"
#include "admin_notifications.cpp"
#include "admin_quests.cpp"
#include "admin_merchantRequests.cpp"
#include "admin_bank.cpp"
#include "admin_transactions.cpp"

using namespace std;

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