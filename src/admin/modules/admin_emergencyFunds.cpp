#include "../includes/admin_includes.h"

using namespace std;

struct studentreq {
    string email, reason, originalLine;
    int tokenAmount;
};

void emergencyFunds() {
    cout << termcolor::bold << termcolor::magenta
         << "\n+---------------------------------+\n"
         << "| " << termcolor::yellow << "    Provide Emergency Funds    " 
         << termcolor::magenta << " |\n"
         << "+---------------------------------+\n" << termcolor::reset;

    vector<studentreq> funds;
    ifstream inFile("studentEmergencyFunds.txt"); 
    string line;

    while (getline(inFile, line)) {
        studentreq req;
        req.originalLine = line;
        string tokenStr;
        stringstream ss(line);

        getline(ss, req.email, ',');
        getline(ss, req.reason, ',');
        getline(ss, tokenStr);

        try {
            req.tokenAmount = stoi(tokenStr);
            funds.push_back(req);
        } catch (...) {
            continue;
        }
    }
    inFile.close();

    if (funds.empty()) {
        cout << termcolor::red << "(No pending emergency funds requests)\n" << termcolor::reset;
        return;
    }

    for (size_t i = 0; i < funds.size(); i++) {
        cout << termcolor::yellow << i + 1 << ". " << funds[i].email << " | " 
             << funds[i].reason << " | " << funds[i].tokenAmount << termcolor::reset << endl;
    }

    cout << termcolor::magenta << "+---------------------------------+\n" << termcolor::reset;

    int index;
    cout << termcolor::cyan << "Enter 0 to return to menu.\n" << termcolor::reset;
    index = promptValidatedIndex("Enter request number to approve: ", funds.size(), true); 
    if (index == 0) {
        cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
        clearSystem(1200);
        return;
    }

    studentreq selected = funds[index - 1];
    updateTotalTokens(-selected.tokenAmount);

    ofstream tokensOut("tokensOut.txt", ios::app);
    tokensOut << selected.email << "," << selected.tokenAmount << endl;
    tokensOut.close();

    if (deleteLine("studentEmergencyFunds.txt", selected.originalLine)) {
        ofstream("studentApprovedReqs.txt", ios::app) << selected.originalLine << endl;
        ofstream("studentLoan.txt", ios::app) << selected.originalLine << endl;

        vector<string> lines;
        ifstream walletIn("studentBalance.txt");
        string walletLine;
        bool found = false;

        while (getline(walletIn, walletLine)) {
            stringstream ss(walletLine);
            string username, balanceStr;
            getline(ss, username, ',');
            getline(ss, balanceStr);

            if (username == selected.email) {
                int balance = stoi(balanceStr) + selected.tokenAmount;
                lines.push_back(username + "," + to_string(balance));
                found = true;
            } else {
                lines.push_back(walletLine);
            }
        }
        walletIn.close();

        if (!found)
            lines.push_back(selected.email + "," + to_string(selected.tokenAmount));

        ofstream walletOut("studentBalance.txt");
        for (const auto& l : lines) walletOut << l << '\n';
        walletOut.close();

        cout << termcolor::green << "\nEmergency fund approved. " << selected.tokenAmount
            << " tokens transferred to " << selected.email << termcolor::reset << endl;

        cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
        clearSystem(2000);
    }
}
