#pragma once
#include "../includes/admin_includes.h"

using namespace std;

class NotificationModule {
public:
    void showNotifications();
private:
    struct NotificationFile { string title; string filename; };
    static const vector<NotificationFile> notifFiles;
    void displayNotification(const NotificationFile& notif);
};

const vector<NotificationModule::NotificationFile> NotificationModule::notifFiles = {
    {"Product Requests", "productReq.txt"},
    {"Merchant Cash Out Requests", "cashout.txt"},
    {"Emergency Fund Requests", "studentEmergencyFunds.txt"},
    {"Student Balances", "studentBalance.txt"},
    {"Student Accomplished Quests", "studentAccomplishedQuests.txt"}
};

void NotificationModule::showNotifications() {
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+---------------------------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << "          NOTIFICATIONS                 " << termcolor::magenta << "|\n";
    cout << "+---------------------------------------------+\n";
    cout << termcolor::reset;

    for (const auto& notif : notifFiles) {
        displayNotification(notif);
    }

    cout << termcolor::bold << termcolor::yellow << "\nEnd of Notifications\n" << termcolor::reset;
}

void NotificationModule::displayNotification(const NotificationFile& notif) {
         cout << termcolor::bold << termcolor::bright_yellow
         << "\n[" << notif.title << "]\n"
         << termcolor::reset << termcolor::magenta
         << "+---------------------------------------------+\n";

        ifstream file(notif.filename);
        if (!file) {
            cout << termcolor::red << " File not found: " << notif.filename;
            cout << string(43 - notif.filename.length(), ' ')
                << termcolor::magenta << "\n+---------------------------------------------+\n";
            return;
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
            cout << termcolor::yellow << " (No pending entries)                        " 
            << termcolor::magenta << "\n";
        }

        cout << "+---------------------------------------------+\n" << termcolor::reset;
        file.close();
}
