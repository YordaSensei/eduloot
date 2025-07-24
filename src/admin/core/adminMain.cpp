#include "../includes/admin_includes.h"
#include "adminMain.h"

#include "../modules/admin_manageAccounts.cpp"
#include "../modules/admin_notifications.cpp"
#include "../modules/admin_quests.cpp"
#include "../modules/admin_merchantRequests.cpp"
#include "../modules/admin_bank.cpp"
#include "../modules/admin_transactions.cpp"
#include "../modules/admin_emergencyFunds.cpp"

using namespace std;

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

        choice = promptChoice(1, 8, "Choice: ");
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
        }
    } while (choice != 8);

    cout << termcolor::red << "\nLogging out...\n" << termcolor::reset;
    clearSystem(1200);
}