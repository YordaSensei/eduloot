#include "admin/admin_includes.h"

using namespace std;

void viewTransactions() {
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+---------------------------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << "         TRANSACTION LOGS               " << termcolor::magenta << "|\n";
    cout << "+---------------------------------------------+\n";
    cout << termcolor::reset;

    struct TransactionFile {
        string title;
        string filename;
    };

    TransactionFile transactionFiles[] = {
        {"Token Purchases (Student)", "studentBalance.txt"},
        {"Token Purchases (Teacher)", "teacherBalance.txt"},
        {"Token Refunds", "tokenRefunds.txt"},
        {"Quest Approvals", "approvedQuests.txt"},
        {"Merchant Cash Outs", "cashout.txt"}
    };

    for (const auto& tx : transactionFiles) {
        cout << termcolor::bold << termcolor::bright_yellow;
        cout << "\n[" << tx.title << "]\n";
        cout << termcolor::reset << termcolor::magenta;
        cout << "+---------------------------------------------+\n";

        ifstream file(tx.filename);
        if (!file) {
            cout << termcolor::red << " File not found: " << tx.filename;
            int space = 43 - (int)tx.filename.length();
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
            cout << termcolor::yellow << " (No entries found)  " << termcolor::magenta << "\n";
        }

        cout << "+---------------------------------------------+\n" << termcolor::reset;
        file.close();
    }

    cout << termcolor::bold << termcolor::yellow << "\nEnd of Transactions\n" << termcolor::reset;
}
