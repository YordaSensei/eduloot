#include "admin/admin_includes.h"

using namespace std;

void bank () {
    int totalTokens = 0, tokensOut = 0, tokensLeft = 0, topUp;
    float totalMoney = 0.00;
    string line, choice;
    const float tokenRate = 3.00;

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
        cout << "\nERROR opening tokensSystem.txt\n";
    }

    ifstream moneyFile ("moneySystem.txt");
    if (moneyFile.is_open()) {
        while (getline(moneyFile, line)) {
            float money = stof(line);
            totalMoney = money;
        }
        moneyFile.close();
    } else {
        cout << "\nERROR opening moneySystem.txt\n";
    }

    totalTokens = tokensOut + tokensLeft;

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+--------------------------------------------------+\n";
    cout << "|            " << termcolor::bright_yellow << "      BANK SUMMARY         " << termcolor::magenta << "           |\n";
    cout << "+--------------------------------------------------+\n";

    cout << termcolor::reset;

    cout << termcolor::yellow << " Total Tokens (in system):   " << totalTokens << " tokens (P" << totalTokens * tokenRate << ")\n";
    cout << " Tokens Out:                 " << tokensOut << " tokens (P" << tokensOut * tokenRate << ")\n";
    cout << " Total Money (in system):    " << "P" << totalMoney << "\n";
    cout << " Admin Token Reserve:        " << tokensLeft << " tokens (P" << tokensLeft * tokenRate << ")\n" << termcolor::reset;

    cout << termcolor::magenta << "+--------------------------------------------------+\n" << termcolor::reset;

    while (true) {
        cout << termcolor::bright_yellow << "\nAdd tokens to the system? [y/n]: ";
        getline(cin, choice);
        cout << termcolor::reset;

        if (choice == "y" || choice == "Y" || choice == "n" || choice == "N") {
            break;
        } else {
            cout << termcolor::bright_red << "Invalid input. Please enter 'y' or 'n'.\n" << termcolor::reset;
        }
    }

   if (choice == "y" || choice == "Y") {
    while (true) {
        cout << termcolor::bold << "\nEnter number of tokens to add: " << termcolor::reset;
        cin >> topUp;

        if (cin.fail() || topUp <= 0) {
            cin.clear(); // clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            cout << termcolor::red << "Invalid token amount. Please enter a positive number.\n" << termcolor::reset;
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clean any trailing newline
            break; // valid input
        }
    }

        updateTotalTokens(topUp);
        cout << termcolor::green << "\nSuccessfully added " << topUp << " tokens (₱" << topUp * tokenRate << ") to the system.\n" << termcolor::reset;
        clearSystem();
    }

}