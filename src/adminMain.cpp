#include "admin/admin_includes.h"

#include "admin_manageAccounts.cpp"
#include "admin_notifications.cpp"
#include "admin_quests.cpp"
#include "admin_merchantRequests.cpp"
#include "admin_bank.cpp"
#include "admin_transactions.cpp"
#include "admin_emergencyFunds.cpp"

using namespace std;

void adminMain() {
    int choice;

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_yellow << "     Good day, Admin!       " << termcolor::magenta << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. Manage accounts          |\n";
        cout << "|  2. Notifications            |\n";
        cout << "|  3. Quests Tab               |\n";
        cout << "|  4. Merchant Requests        |\n";
        cout << "|  5. Bank                     |\n";
        cout << "|  6. Emergency Funds          |\n";
        cout << "|  7. View Transactions        |\n";
        cout << "|  8. Log Out                  |\n";
        cout << "+------------------------------+\n"<< termcolor::reset;

        cout << termcolor::bright_yellow << "Choice: ";
        cin >> choice;
        cout << termcolor::reset;
        system("cls");


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
                emergencyFunds();
                break;
            case 7:
                viewTransactions();
                break;
            case 8:
                break;
            default:
                cout << "\nERROR: Invalid Choice!\n";
                continue;
        }
    } while (choice != 8);

    cout << termcolor::red << "\nLogging out...\n" << termcolor::reset;
    clearSystem();
}