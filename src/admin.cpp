#include <iostream>

using namespace std;

void manageAccounts () {
    int choice;

    do {
        cout << "\n--- Manage Accounts ---\n";
        cout << "1. View all accounts\n";
        cout << "2. Create accounts\n";
        cout << "3. Delete or Suspend account\n";
        cout << "4. Edit account information\n";
        cout << "5. Back to Dashboard\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageAccounts();
                break;
            case 2:
            case 3:
            case 4:
            case 5:
                break;
            default:
                cout << "\nERROR: Invalid Choice!";
                continue;
        }

        
    } while (choice != 5);

}

int main () {
    int choice;

    do {
        cout << "\n--- Good day, Admin! ---\n";
        cout << "1. Manage accounts\n";
        cout << "2. Notifications\n";
        cout << "3. Quests Tab\n";
        cout << "4. Token Bank\n";
        cout << "5. Money Bank\n";
        cout << "6. View Transactions\n";
        cout << "7. Log Out\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageAccounts();
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                break;
            default:
                cout << "\nERROR: Invalid Choice!";
                continue;
        }
    } while (choice != 7);

    cout << "\nLogging out...";
    return 0;
}