#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

#include "../../termcolor/termcolor.hpp"

#include "student_helpers.h"
#include "../modules/student_wallet.cpp"
#include "../modules/student_purchase.cpp"
#include "../modules/student_quests.cpp"
#include "../modules/student_notifications.cpp"
#include "../modules/student_transactions.cpp"
#include "../modules/student_emergencyFunds.cpp"

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
        cout << termcolor::reset;
        system("cls");

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
            case 7:
                cout << termcolor::red << "Logging Out...";
                clearSystem();
        }
    } while (choice != 7);
}