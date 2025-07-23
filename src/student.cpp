#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "student_helpers.h"
#include "termcolor/termcolor.hpp"
using namespace std;

#include "student_wallet.cpp"
#include "student_purchase.cpp"
#include "student_quests.cpp"
#include "student_notifications.cpp"
#include "student_transactions.cpp"
#include "student_emergencyFunds.cpp"

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
        cout << termcolor::bright_cyan << "Choice: ";
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
                studentNotifications(email);
                break;
            case 5:
                studentTransactions(email);
                break;
            case 6:
                emergencyFunds(email);
                break;
        }
    } while (choice != 7);

    cout << "Logging Out...";
}