#pragma once
#include "../includes/admin_includes.h"

using namespace std;

struct studentreq {
    string email, reason, originalLine;
    int tokenAmount;
};

class emergencyFundsModule {
    public:
        void emergencyFunds();

    private:
        vector<studentreq> LoadEmergencyRequests();
        void showEmergencyRequests(const vector<studentreq> &requests);
        void approveEmergencyRequest (studentreq &selected);
        void writeToWallet (const studentreq &selected);
        void logApproval (const studentreq &selected);
};

void emergencyFundsModule::emergencyFunds () {
    cout << termcolor::bold << termcolor::magenta
         << "\n+---------------------------------+\n"
         << "| " << termcolor::yellow << "    Provide Emergency Funds    " 
         << termcolor::magenta << " |\n"
         << "+---------------------------------+\n" << termcolor::reset;

    vector<studentreq> funds = LoadEmergencyRequests();
    if (funds.empty()) {
        cout << termcolor::red << "(No pending emergency funds requests)\n" << termcolor::reset;
        return;
    }

    showEmergencyRequests(funds);

    int index = promptChoice(1, funds.size(),"Enter request number to approve (0 to cancel): "); 
    if (cancelInput(index)) {
        return;
    }

    approveEmergencyRequest(funds[index - 1]);
}

vector <studentreq> emergencyFundsModule::LoadEmergencyRequests() {
    ifstream requestFundsFile("admin/files/studentEmergencyFunds.txt");
    vector<studentreq> funds;
    string line;

    while (getline(requestFundsFile, line)) {
        stringstream split(line);
        studentreq req;
        req.originalLine = line;
        string tokenStr;

        getline(split, req.email, ',');
        getline(split, req.reason, ',');
        getline(split, tokenStr);

        try {
            req.tokenAmount = stoi(tokenStr);
        } catch(...) {
            continue;
        }
    }
    requestFundsFile.close();
    return funds;
}

void emergencyFundsModule::showEmergencyRequests(const vector<studentreq> &requests) {
    for (size_t i = 0; i < requests.size(); i++) {
        cout << termcolor::yellow << i + 1 << ". " << requests[i].email << " | " 
             << requests[i].reason << " | " << requests[i].tokenAmount << termcolor::reset << endl;
    }
}

void emergencyFundsModule::approveEmergencyRequest (studentreq &selected) {
    updateTotalTokens(-selected.tokenAmount);

    ofstream tokensOut("admin/files/tokensOut.txt", ios::app);
    tokensOut << selected.email << "," << selected.tokenAmount << endl;
    tokensOut.close();

    if (deleteLine("studentEmergencyFunds.txt", selected.originalLine)) {
        writeToWallet (selected);
        logApproval (selected);

        cout << termcolor::green << "\nEmergency fund approved. " << selected.tokenAmount
            << " tokens transferred to " << selected.email << termcolor::reset << endl;

        cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
        clearSystem(2500);
    }
}

void emergencyFundsModule::writeToWallet (const studentreq &selected) {
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
            try {
                int balance = stoi(balanceStr) + selected.tokenAmount;
                lines.push_back(username + "," + to_string(balance));
                found = true;
            } catch (...) {
                continue;
            }
        } else {
            lines.push_back(walletLine);
        }
    }
    walletIn.close();

    if (!found)
        lines.push_back(selected.email + "," + to_string(selected.tokenAmount));

    ofstream walletOut("studentBalance.txt");
    for (const auto& approved : lines) walletOut << approved << '\n';
    walletOut.close();
}

void emergencyFundsModule::logApproval (const studentreq &selected) {
    ofstream("admin/files/studentApprovedReqs.txt", ios::app) << selected.originalLine << endl;
    ofstream("admin/files/studentLoan.txt", ios::app) << selected.originalLine << endl;
}