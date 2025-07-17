#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "admin_helpers.cpp"

using namespace std;

void viewTransactions () {
    cout << "\n--- Viewing All Transactions ---\n";

    struct TransactionFile {
        string title;
        string filename;
    };

    TransactionFile transactionFiles[] = {
        {"Token Purchases", "tokenPurchases.txt"},
        {"Token Refunds", "tokenRefunds.txt"},
        {"Token to Cash Conversions", "tokenConversions.txt"},
        {"Quest Approvals", "ApprovedQuests.txt"},
        {"Merchant Cash Outs", "cashout.txt"}
    };

    for (const auto& tx : transactionFiles) {
        cout << "\n[" << tx.title << "]\n";
        ifstream file(tx.filename);

        if (!file) {
            cout << "(No file found: " << tx.filename << ")\n";
            continue;
        }

        string line;
        bool empty = true;
        while (getline(file, line)) {
            empty = false;
            cout << "- " << line << endl;
        }

        if (empty) {
            cout << "(No entries found)\n";
        }

        file.close();
    }
}