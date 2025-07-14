#include <iostream>
#include "../include/admin/adminMain.h"
#include "../include/admin/manageAccounts.h"
#include "../include/admin/notifications.h"
#include "../include/admin/quests.h"
#include "../include/admin/merchantRequests.h"
#include "../include/admin/tokenBank.h"
#include "../include/admin/moneyBank.h"
#include "../include/admin/viewTransactions.h"

using namespace std;

int main() {
    int choice;

    do {
        cout << "\n--- Good day, Admin! ---\n";
        cout << "1. Manage accounts\n";
        cout << "2. Notifications\n";
        cout << "3. Quests Tab\n";
        cout << "4. Merchant Requests\n";
        cout << "5. Token Bank\n";
        cout << "6. Money Bank\n";
        cout << "7. View Transactions\n";
        cout << "8. Log Out\n";
        cout << "--------------------------\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageAccounts();
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
            case 7:
                break;
            case 8:
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }
    } while (choice != 8);

    cout << "\nLogging out...\n";
}
