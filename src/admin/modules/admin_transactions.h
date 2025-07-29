#pragma once
#include "../includes/admin_includes.h"

using namespace std;

class TransactionsModule {
    public:
        void showTransactions();
    private:
        struct transactionFile { string title; string filename;};
        static const vector<transactionFile> transFiles;
        void displayTransaction(const transactionFile& transacs);
};

const vector<TransactionsModule::transactionFile> TransactionsModule::transFiles = {
        {"Token Purchases (Student)", "studentBalance.txt"},
        {"Emergency Funds", "admin/files/studentApprovedReqs.txt"},
        {"Token Purchases (Teacher)", "teacherBalance.txt"},
        {"Token Refunds", "tokenRefunds.txt"},
        {"Quest Approvals", "admin/files/approvedQuests.txt"},
        {"Merchant Requests", "admin/files/approvedReq.txt"}
};

void TransactionsModule::showTransactions() {
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+---------------------------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << "         TRANSACTION LOGS               " << termcolor::magenta << "|\n";
    cout << "+---------------------------------------------+\n";
    cout << termcolor::reset;

    for (const auto& transacs : transFiles) {
        displayTransaction(transacs);
    }

    cout << termcolor::bold << termcolor::yellow << "\nEnd of Transactions\n" << termcolor::reset;
}

void TransactionsModule::displayTransaction (const transactionFile& transacs) {
    cout << termcolor::bold << termcolor::bright_yellow
        << "\n[" << transacs.title << "]\n"
        << termcolor::reset << termcolor::magenta
        << "+---------------------------------------------+\n";

        ifstream file(transacs.filename);
        if (!file) {
            cout << termcolor::red << " File not found: " << transacs.filename;
            cout << string(43 - transacs.filename.length(), ' ')
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
            cout << termcolor::yellow << " (No entries found)  " << termcolor::magenta << "\n";
        }

        cout << "+---------------------------------------------+\n" << termcolor::reset;
        file.close();
    }

