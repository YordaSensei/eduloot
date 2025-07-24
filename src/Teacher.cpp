#include "Teacher.h"
#include <iostream>

using namespace std;

enum class TeacherMenuOption { Wallet = 1, Purchase, Notifications, Transactions, Back };

void Teacher::teacherMain(string insertedEmail) {
    setEmail(insertedEmail);
    setUserType("teacher");

    int choice;
    do {
        cout << "\n--- Good day, Teacher! ---\n";
        cout << "1. Wallet\n";
        cout << "2. Purchase\n";
        cout << "3. Notifications\n";
        cout << "4. Transactions\n";
        cout << "5. Log Out\n";

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 5)) {
            continue;
        }

        switch(static_cast<TeacherMenuOption>(choice)) {
            case TeacherMenuOption::Wallet:
                wallet();
                break;
            case TeacherMenuOption::Purchase:
                purchase();
                break;
            case TeacherMenuOption::Notifications:
                notifications();
                break;
            case TeacherMenuOption::Transactions:
                transactions();
                break;
            case TeacherMenuOption::Back:
                break;
        }
    } while (choice != 5);

    cout << "Logging Out...";

}