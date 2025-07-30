#pragma once
#include "../includes/admin_includes.h"

using namespace std;

class BankModule {
    public:
        void showBankSummary();
    private:
        const float tokenRate = 3.00;

        int readTokensOut();
        int readTokensLeft();
        float readTotalMoney();
        void promptTokenTopUp();
};

// function to show bank summary
void BankModule::showBankSummary () {
    // calls all needed functions and assigns its return value to its corresponding variable
    int tokensOut = readTokensOut();
    int tokensLeft = readTokensLeft();
    float totalMoney = readTotalMoney();
    int totalTokens = tokensOut + tokensLeft;

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+--------------------------------------------------+\n";
    cout << "|            " << termcolor::bright_yellow << "      BANK SUMMARY         " << termcolor::magenta << "           |\n";
    cout << "+--------------------------------------------------+\n" << termcolor::reset;

    cout << fixed << setprecision(2);
    cout << termcolor::yellow; 
    cout << " Total Tokens:               " << totalTokens << " tokens (P" << totalTokens * tokenRate << ")\n";
    cout << " Tokens Out:                 " << tokensOut << " tokens (P" << tokensOut * tokenRate << ")\n";
    cout << " Total Money (in system):    P" << totalMoney << "\n";
    cout << " Admin Token Reserve:        " << tokensLeft << " tokens (P" << tokensLeft * tokenRate << ")\n" << termcolor::reset;
    cout << termcolor::magenta << "+--------------------------------------------------+\n" << termcolor::reset;

    promptTokenTopUp();
}

// Function to read total tokens that are out
int BankModule::readTokensOut() {
    ifstream tokenFile("admin/files/tokensOut.txt");
    string line;
    int tokensOut = 0;

    if (!tokenFile) {
        cout << termcolor::red << "ERROR: Could not open tokensOut.txt\n" << termcolor::reset;
        return 0;
    }

    while (getline(tokenFile, line)) { // gets the value inside the tokensOut file
        try {
            if (!line.empty()) tokensOut = stoi(line);
        } catch (...) {
            continue;
        }
    }

    tokenFile.close();
    return tokensOut;
}

int BankModule::readTokensLeft () {
    ifstream adminFile("admin/files/tokensSystem.txt");
    string line;
    int tokensLeft = 0;

    if (!adminFile) {
        cout << termcolor::red << "ERROR: Could not open tokensSystem.txt\n" << termcolor::reset;
        return 0;
    }

    while (getline(adminFile, line)) {
        try {
            if (!line.empty()) tokensLeft = stoi(line);
        } catch (...) {
            continue;
        }
    }

    adminFile.close();
    return tokensLeft;
}

float BankModule::readTotalMoney () {
    ifstream moneyFile("admin/files/moneySystem.txt");
    string line;
    float totalMoney = 0.00;

    if (!moneyFile) {
        cout << termcolor::red << "ERROR: Could not open moneySystem.txt\n" << termcolor::reset;
        return 0;
    }
    
    while (getline(moneyFile, line)) {
        try {
        if (!line.empty()) totalMoney = stof(line);
        } catch (...) {
            continue;
        }
    }

    moneyFile.close();
    return totalMoney;
}

// function that asks the admin for token top ups
void BankModule::promptTokenTopUp () {
    string input;
    int topUp;
    string choice;

    while (true) {
    string choice, input;
    int topUp = 0;
    
    cout << termcolor::bright_yellow << "\nAdd tokens to the system? [y/n]: ";
    getline(cin, choice);
    cout << termcolor::reset;

    if (choice == "y" || choice == "Y") {
        do {
            cout << termcolor::bold << "\nEnter number of tokens to add: " << termcolor::reset;
            getline(cin, input);

            if (input.empty()) {
                cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
            }
        } while (input.empty());

            try {
                topUp = stoi(input); // Convert string to int
            } catch (const exception& e) {
                cout << termcolor::red << "Invalid number. Please enter a valid integer.\n" << termcolor::reset;
                continue; // retry loop
            }

            if (topUp <= 0) {
                cout << termcolor::red << "Invalid token amount. Please enter a positive number.\n" << termcolor::reset;
            } else {
                updateTotalTokens(topUp);
                cout << termcolor::green << "\nSuccessfully added " << topUp << " tokens (P" << topUp * tokenRate << ") to the system.\n" << termcolor::reset;
                clearSystem(3000);
                break;
            }

        } else if (choice == "n" || choice == "N") {
            cout << termcolor::yellow << "No tokens added. Returning to menu...\n" << termcolor::reset;
            clearSystem(1200);
            break;

        } else {
            cout << termcolor::bright_red << "Invalid input. Please enter 'y' or 'n'.\n" << termcolor::reset;
        }
    }
}
