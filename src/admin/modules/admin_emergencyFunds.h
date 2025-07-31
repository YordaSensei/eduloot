#pragma once
#include "../includes/admin_includes.h"

using namespace std;

struct studentreq {
    string email, reason, originalLine;
    int tokenAmount;
};

class EmergencyFundsModule {
    public:
        void emergencyFunds();

    private:
        vector<studentreq> LoadEmergencyRequests();
        void showEmergencyRequests(const vector<studentreq> &requests);
        void approveEmergencyRequest (studentreq &selected);
        void writeToWallet (const studentreq &selected);
        void logApproval (const studentreq &selected);
};

// Displays all emergency fund requests
void EmergencyFundsModule::emergencyFunds () {
    cout << termcolor::bold << termcolor::magenta
         << "\n+---------------------------------+\n"
         << "| " << termcolor::yellow << "    Provide Emergency Funds    " 
         << termcolor::magenta << " |\n"
         << "+---------------------------------+\n" << termcolor::reset;

    vector<studentreq> funds = LoadEmergencyRequests();  // Load all pending emergency fund requests into a vector for processing
    if (funds.empty()) {
        cout << termcolor::red << "(No pending emergency funds requests)\n" << termcolor::reset;
        return;
    }

    showEmergencyRequests(funds);

    int index = promptChoice(1, funds.size(),"Enter request number to approve (0 to cancel): "); 
    if (index == 0) return;

    approveEmergencyRequest(funds[index - 1]); // sa part na to, diretso ko na lang po as argument yung selected index ng vector instead of making another variable
}

// vector that stores the contents of the file
vector <studentreq> EmergencyFundsModule::LoadEmergencyRequests() {
    ifstream requestFundsFile("studentEmergencyFunds.txt");
    if (!requestFundsFile.is_open()) {
        cerr << "ERROR: Could not open studentEmergencyFunds.txt for reading.\n";
        return {}; 
    }

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

        funds.push_back(req);
    }
    requestFundsFile.close();
    return funds;
}

// prints the contents of the vector
void EmergencyFundsModule::showEmergencyRequests(const vector<studentreq> &requests) {
    for (size_t i = 0; i < requests.size(); i++) {
        cout << termcolor::yellow << i + 1 << ". " << requests[i].email << " | " 
             << requests[i].reason << " | " << requests[i].tokenAmount << termcolor::reset << endl;
    }
}

void EmergencyFundsModule::approveEmergencyRequest (studentreq &selected) {
    if (deleteLine("studentEmergencyFunds.txt", selected.originalLine)) {
        updateTotalTokens(-selected.tokenAmount);
        updateTokensOut(selected.tokenAmount);
        writeToWallet (selected);
        logApproval (selected);

        cout << termcolor::green << "\nEmergency fund approved. " << selected.tokenAmount
            << " tokens transferred to " << selected.email << termcolor::reset << endl;

        cout << termcolor::red << "\nReturning to menu...\n" << termcolor::reset;
        clearSystem(2500);
    }
}

void EmergencyFundsModule::writeToWallet (const studentreq &selected) {
    vector<string> lines;
    ifstream walletIn("studentBalance.txt");
    if (!walletIn.is_open()) {
        cerr << "ERROR: Could not open studentBalance.txt for reading.\n";
        return; 
    }

    string walletLine;
    bool found = false;

    while (getline(walletIn, walletLine)) {
        stringstream ss(walletLine);
        string email, balanceStr;
        getline(ss, email, ',');
        getline(ss, balanceStr);

        if (email == selected.email) {
            try {
                int balance = stoi(balanceStr) + selected.tokenAmount;
                lines.push_back(email + "," + to_string(balance));
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
    if (!walletOut.is_open()) {
        cerr << "ERROR: Could not open studentBalance.txt for reading.\n";
        return; 
    }
    
    for (const auto& approved : lines) walletOut << approved << '\n';
    walletOut.close();
}

void EmergencyFundsModule::logApproval (const studentreq &selected) {
    ofstream("admin/files/studentApprovedReqs.txt", ios::app) << selected.originalLine << endl;
    ofstream("admin/files/studentLoan.txt", ios::app) << selected.originalLine << endl;
}