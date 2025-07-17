#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

using namespace std;

void notifications () {
    cout << "\n--- Viewing Notifications ---\n";

    struct NotificationFile {
        string title;
        string filename;
    };

    NotificationFile notifFiles[] = {
        {"Product Add Requests", "productReq.txt"},
        {"Product Delete Requests", "deleteProductReq.txt"},
        {"Merchant Concerns", "concerns.txt"},
        {"Merchant Cash Out Requests", "cashout.txt"},
        {"Emergency Fund Requests", "emergencyfunds.txt"},
        {"Student Balances", "studentBalance.txt"},
        {"Student Accomplished Quests", "studentAccomplishedQuests.txt"}
    };

    for (const auto& notif : notifFiles) {
        cout << "\n[" << notif.title << "]\n";
        ifstream file(notif.filename);

        if (!file) {
            cout << "(No file found: " << notif.filename << ")\n";
            continue;
        }

        string line;
        bool empty = true;
        while (getline(file, line)) {
            empty = false;
            cout << "- " << line << endl;
        }

        if (empty) {
            cout << "(No pending entries)\n";
        }

        file.close();
    }
}