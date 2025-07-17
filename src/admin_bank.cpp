#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "admin_helpers.cpp"

using namespace std;

void bank () {
    int totalTokens = 0, totalMoney = 0, tokensOut = 0, tokensLeft = 0, topUp;
    string line;
    const int tokenRate = 3;

    ifstream tokenFile ("tokensOut.txt");
    if (tokenFile.is_open()) {
        while (getline(tokenFile, line)) {
            size_t pos = line.find(",");
            if (pos != string::npos) {
                string tokens = line.substr(pos + 1);
                int token = stoi(tokens);
                tokensOut += token;
            }
        }
        tokenFile.close();
    } else {
        cout << "\nERROR opening tokensOut.txt\n";
    }

    ifstream adminFile ("tokensSystem.txt");
    if (adminFile.is_open()) {
        while (getline(adminFile, line)) {
            int token = stoi(line);
            tokensLeft += token;
        }
        adminFile.close();
    } else {
        cout << "\nERROR opening adminTokens.txt\n";
    }

    ifstream moneyFile ("moneySystem.txt");
    if (adminFile.is_open()) {
        while (getline(moneyFile, line)) {
            int money = stoi(line);
            totalMoney = money;
        }
        adminFile.close();
    } else {
        cout << "\nERROR opening adminTokens.txt\n";
    }

    totalTokens = tokensOut + tokensLeft;

    cout << "\n--- BANK SUMMARY ---\n";
    cout << "Total Tokens (in system):   " << totalTokens << " tokens (P" << totalTokens * tokenRate << ")\n";
    cout << "Tokens Out:                 " << tokensOut << " tokens (P" << tokensOut * tokenRate << ")\n";
    cout << "Total Money (in system):    " << "P" << totalMoney << "\n";
    cout << "-----------------------\n";
    cout << "Admin Token Reserve:        " << tokensLeft << " tokens (P" << tokensLeft * tokenRate << ")\n";

    int choice;
    cout << "\nAdd more tokens to the system?\n";
    cout << "1. Yes\n";
    cout << "2. No\n";
    cout << "--------------------------------\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 1) {
        cout << "\nEnter number of tokens to add: ";
        cin >> topUp;

        if (topUp > 0) {
            updateTotalTokens(topUp);
            cout << "\nSuccessfully added " << topUp << " tokens (₱" << topUp * tokenRate << ") to the system.\n";
        } else {
            cout << "\nInvalid token amount.\n";
        }
    } else if (choice == 2) {
        cout << "\nReturning to dashboard...\n";
    } else {
        cout << "\nInvalid choice.\n";
    }
}