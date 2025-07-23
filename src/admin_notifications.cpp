#include "admin/admin_includes.h"

using namespace std;

void notifications() {
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+---------------------------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << "          NOTIFICATIONS                 " << termcolor::magenta << "|\n";
    cout << "+---------------------------------------------+\n";
    cout << termcolor::reset;

    struct NotificationFile {
        string title;
        string filename;
    };

    NotificationFile notifFiles[] = {
        {"Product Requests", "productReq.txt"},
        {"Merchant Concerns", "concerns.txt"},
        {"Merchant Cash Out Requests", "cashout.txt"},
        {"Emergency Fund Requests", "studentEmergencyFunds.txt"},
        {"Student Balances", "studentBalance.txt"},
        {"Student Accomplished Quests", "studentAccomplishedQuests.txt"}
    };

    for (const auto& notif : notifFiles) {
        cout << termcolor::bold << termcolor::bright_yellow;
        cout << "\n[" << notif.title << "]\n";
        cout << termcolor::reset << termcolor::magenta;
        cout << "+---------------------------------------------+\n";

        ifstream file(notif.filename);
        if (!file) {
            cout << termcolor::red << " File not found: " << notif.filename;
            int space = 43 - (int)notif.filename.length();
            cout << string(space, ' ') << termcolor::magenta << "\n";
            cout << "+---------------------------------------------+\n";
            continue;
        }

        string line;
        bool empty = true;
        while (getline(file, line)) {
            if (!line.empty()) {
                empty = false;
                cout << " " << termcolor::white << line;
                int padding = 45 - (int)line.length();
                if (padding > 0) cout << string(padding, ' ');
                cout << termcolor::magenta << "\n";
            }
        }

        if (empty) {
            cout << termcolor::yellow << " (No pending entries)                        " << termcolor::magenta << "\n";
        }

        cout << "+---------------------------------------------+\n" << termcolor::reset;
        file.close();
    }

    cout << termcolor::bold << termcolor::yellow << "\nEnd of Notifications\n" << termcolor::reset;
}
