#pragma once
#include "../includes/admin_includes.h"

using namespace std;

class bankModule {
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
void bankModule::showBankSummary () {
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
int bankModule::readTokensOut() {
    ifstream tokenFile("admin/files/tokensOut.txt");
    string line;
    int tokensOut = 0;

    if (!tokenFile) {
        cout << termcolor::red << "ERROR: Could not open tokensOut.txt\n" << termcolor::reset;
        return 0;
    }

    while (getline(tokenFile, line)) { // gets the value inside the tokensOut file
        try {
            if (!line.empty()) tokensLeft = stoi(line);
        } catch (...) {
            continue;
        }
    }

    tokenFile.close();
    return tokensOut;
}

int bankModule::readTokensLeft () {
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

float bankModule::readTotalMoney () {
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
void bankModule::promptTokenTopUp () {
    int topUp;
    string choice;

    while (true) {
        cout << termcolor::bright_yellow << "\nAdd tokens to the system? [y/n]: ";
        getline(cin, choice);
        cout << termcolor::reset;

        if (choice == "y" || choice == "Y"){
            cout << termcolor::bold << "\nEnter number of tokens to add: " << termcolor::reset;
            cin >> topUp;

            if (cin.fail() || topUp <= 0) { // handles invalid inputs and negative numbers
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << termcolor::red << "Invalid token amount. Please enter a positive number.\n" << termcolor::reset;
            } else {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
