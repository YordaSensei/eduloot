#include "../includes/admin_includes.h"

#include "../modules/admin_manageAccounts.h"
#include "../modules/admin_notifications.h"
#include "../modules/admin_quests.h"
#include "../modules/admin_merchantRequests.h"
#include "../modules/admin_bank.h"
#include "../modules/admin_transactions.h"
#include "../modules/admin_emergencyFunds.h"

using namespace std;

// displayds admin menu
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

// runs admin menu
void adminMain() {
    int choice;

    do {
        printAdminMenu();

        do {
            choice = promptChoice(1, 8, "Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
        system("cls"); // clears the terminal

        switch (choice) {
            case 1:
                AccountManager accounts;
                accounts.manageAccounts();
                break;
            case 2: {
                NotificationModule notifications;
                notifications.showNotifications();
                break;
            }
            case 3: {
                QuestsModule quests;
                quests.questsTab();
                break;
            }
            case 4: {
                MerchantRequestsModule merchantModule;
                merchantModule.merchantRequest();
                break;
            }
            case 5: {
                BankModule bank;
                bank.showBankSummary();
                break;
            }
            case 6:
                EmergencyFundsModule funds;
                funds.emergencyFunds();
                break;
            case 7: {
                TransactionsModule transactions;
                transactions.showTransactions();
                break;
            }
            case 8:
                break;
            default: 
                cout << termcolor::bright_red << "\nInvalid choice!\n" << termcolor::reset;
                continue;
        }
    } while (choice != 8);

    cout << termcolor::red << "\nLogging out...\n" << termcolor::reset;
    clearSystem(1200);
}