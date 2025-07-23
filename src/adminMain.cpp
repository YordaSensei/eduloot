#include "admin/admin_includes.h"

#include "admin_manageAccounts.cpp"
#include "admin_notifications.cpp"
#include "admin_quests.cpp"
#include "admin_merchantRequests.cpp"
#include "admin_bank.cpp"
#include "admin_transactions.cpp"
#include "admin_emergencyFunds.cpp"

using namespace std;

enum AdminMenu {
    MANAGE_ACCOUNTS = 1,
    NOTIFICATIONS,
    QUESTS_TAB,
    MERCHANT_REQUESTS,
    BANK,
    EMERGENCY_FUNDS,
    VIEW_TRANSACTIONS,
    LOG_OUT
};

void printAdminMenu() {
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
    cout << "+------------------------------+\n" << termcolor::reset;
}

void adminMain() {
    int choice;

    do {
        printAdminMenu();

        while (true) {
            cout << termcolor::bright_yellow << "Choice: ";
            if (cin >> choice && choice >= MANAGE_ACCOUNTS && choice <= LOG_OUT) break;
            cout << termcolor::red << "Invalid choice. Please enter 1-8.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        system("cls");

        switch (choice) {
            case MANAGE_ACCOUNTS:
                manageAccounts();
                break;
            case NOTIFICATIONS:
                notifications();
                break;
            case QUESTS_TAB:
                questsTab();
                break;
            case MERCHANT_REQUESTS:
                merchantRequests();
                break;
            case BANK:
                bank();
                break;
            case EMERGENCY_FUNDS:
                emergencyFunds();
                break;
            case VIEW_TRANSACTIONS:
                viewTransactions();
                break;
            case LOG_OUT:
                break;
        }
    } while (choice != LOG_OUT);

    cout << termcolor::red << "\nLogging out...\n" << termcolor::reset;
    clearSystem();
}