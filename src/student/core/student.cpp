#include <iomanip>

#include "student_helpers.h"
#include "../modules/student_wallet.cpp"
#include "../modules/student_purchase.h"
#include "../modules/student_quests.cpp"
#include "../modules/student_notifications.h"
#include "../modules/student_transactions.h"
#include "../modules/student_emergencyFunds.h"

void studentMain(string email) {
    int choice;

    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_cyan << "    Good day, Student!      " << termcolor::blue << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. Wallet                   |\n";
        cout << "|  2. Purchase                 |\n";
        cout << "|  3. Quests                   |\n";
        cout << "|  4. Notification             |\n";
        cout << "|  5. Transactions             |\n";
        cout << "|  6. Request Emergency Fund   |\n";
        cout << "|  7. Log Out                  |\n";
        cout << "+------------------------------+\n"<< termcolor::reset;
        do {
            choice = promptChoice(1,7,"Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);

        system("cls");

        switch(choice) {
            case 1:
                wallet(email);
                break;
            case 2:
                studentPurchase purchase;
                purchase.purchase(email);
                break;
            case 3:
                quests(email);
                break;
            case 4:
                studentNotifications notifs;
                notifs.notifications(email);
                break;
            case 5:
                studentTransactions transacs;
                transacs.transactions(email);
                break;
            case 6:
                emergencyFunds funds;
                funds.requestFunds(email);
                break;
            case 7:
                cout << termcolor::red << "Logging Out...";
                clearSystem();
        }
    } while (choice != 7);
}