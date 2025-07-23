#include "admin/admin_includes.h"

using namespace std;

struct studentreq {
    string email;
    string reason;
    int tokenAmount;
    string originalLine;
};

void emergencyFunds() {
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+---------------------------------+\n";
    cout << "| "  << termcolor::yellow <<  "    Provide Emergency Funds    " << termcolor::magenta <<    " |\n";
    cout << "+---------------------------------+\n";
    cout << termcolor::reset;

    vector<studentreq> funds;
    ifstream inFile ("studentEmergencyFunds.txt"); 
    string line;

    while (getline(inFile, line)) {
        studentreq req;
        string tokenStr;
        stringstream ss(line);
        req.originalLine = line;

        getline (ss, req.email, ',');
        getline (ss, req.reason, ',');
        getline (ss, tokenStr);

        try {
            req.tokenAmount = stoi(tokenStr);
        } catch (...) {
            continue;
        }

        funds.push_back(req);
    }

    int displayedIndex = 1;
    bool hasRequests = false;
    for (size_t i = 0; i < funds.size(); i++) {
        hasRequests = true;
        cout << termcolor::yellow << displayedIndex << ". " << funds[i].email << " | " 
        << funds[i].reason << " | " << funds[i].tokenAmount << termcolor::reset << endl;
            displayedIndex++;
    }

    if (!hasRequests) {
        cout << termcolor::red << "(No pending emergency funds requests)\n";
    }

    int index;
    cout << termcolor::magenta << "+-----------------------------------+\n" << termcolor::reset;
    while (true) {
        cout << termcolor::bright_yellow << "Enter request number to approve: ";
        if (cin >> index && index > 0 && index <= (int)funds.size()) break;
        cout << termcolor::red << "Invalid input. Please enter a valid index.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (index <= 0 || index > funds.size()) return;

    studentreq selected = funds[index - 1];

    updateTotalTokens(-selected.tokenAmount);

    ofstream approveFile ("studentApprovedReqs.txt", ios::app);
    approveFile << selected.originalLine << endl;
    approveFile.close();

    ofstream reminders ("studentLoan.txt", ios::app);
    reminders << selected.originalLine;
    reminders.close();

    deleteLine("studentEmergencyFunds.txt", selected.originalLine);

        vector<string> balanceLines;
        ifstream walletIn("studentBalance.txt");
        string walletLine;
        bool found = false;

        while (getline(walletIn, walletLine)) {
            stringstream ss(walletLine);
            string username, balanceStr;
            getline(ss, username, ',');
            getline(ss, balanceStr);

            if (username == selected.email) {
                int balance = stoi(balanceStr);
                balance += selected.tokenAmount;
                balanceLines.push_back(username + "," + to_string(balance));
                found = true;
            } else {
                balanceLines.push_back(walletLine);
            }
        }
        walletIn.close();

        if (!found) {
            balanceLines.push_back(selected.email + "," + to_string(selected.tokenAmount));
        }

        ofstream walletOut("studentBalance.txt");
        for (const string& line : balanceLines) {
            walletOut << line << endl;
        }
        walletOut.close();

        cout << termcolor::green << "Emergency fund approved. " << selected.tokenAmount << " tokens transferred to " << selected.email << termcolor::reset << endl;
        cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
        clearSystem();
}