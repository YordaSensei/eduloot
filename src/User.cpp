#include "User.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "admin/includes/admin_helpers.h"
#include "product_helpers.h"
#include "merchant_helpers.h"

using namespace std;
    
enum class WalletOption { ViewBalance = 1, Purchase, Convert, Back };
int tokenToPHPValue = 3;

void User::wallet() {
    int choice;

    do {
        cout << "\n--- Token Wallet ---\n";
        cout << "1. View Balance\n";
        cout << "2. Purchase Tokens\n";
        cout << "3. Convert to Cash\n";
        cout << "4. Back to Home\n";

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 4)) {
            continue;
        }

        switch(static_cast<WalletOption>(choice)) {
            case WalletOption::ViewBalance:
                viewBalance();
                break;
            case WalletOption::Purchase:
                purchaseTokens();
                break;
            case WalletOption::Convert:
                convertTokens();
                break;
            case WalletOption::Back:
            break;
        }
    } while (choice != 4);
}

void User::viewBalance() {
    string line;
    ifstream inFile(userType + "Balance.txt");

    if (!inFile.is_open()) {
        cout << "Error opening balance file.\n";
        return;
    }
    
    bool found = false;
    int choice;

    do {
        while (getline(inFile, line)) {
            if (!line.empty()) {
                string strBalance;
                stringstream split(line);
                string fileEmail;

                getline(split, fileEmail, ',');
                getline(split, strBalance);

                if (fileEmail == email) {
                    this->tokenBalance = stoi(strBalance);
                    cout << "Token Balance: " << this->tokenBalance << endl;
                    found = true;
                    break;
                }
            }
        }
        inFile.close();

        if (!found) {
            this->tokenBalance = 0;
            cout << "Token Balance: 0\n";
        }

        cout << "1. Back\n";
        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void User::purchase() {
}

void User::purchaseTokens() {
    int inputAmount;
    cout << "\n--- Purchase Tokens ---\n";
    cout << "How many tokens would you like to purchase? (PHP 3.00 = 1 Token): ";
    
    if (!getNumericInput(inputAmount, "PHP", "Invalid amount. Please enter a positive number.", 1)) {
        return;
    }

    char choice;
    int tokensToAdd = inputAmount / tokenToPHPValue;
    cout << "Total tokens to be recieved : " << tokensToAdd << ".\n";
    cout << "Are you sure you want to purchase PHP" << inputAmount << " amount of tokens? (y/n)\n";

    if (!getYesNoInput(choice, "Choice: ", "Invalid choice.")) {
        return;
    }

    if (choice == 'y') {
        int newBalance = tokenBalance + tokensToAdd;
        updateBalanceInFile(newBalance);
        recordTransaction("PURCHASE", tokensToAdd, newBalance);
        viewBalance();
        cout << "Purchase successful! New balance: " << newBalance << " tokens.\n";
    } else {
        cout << "Purchase cancelled.\n";
    }
}

void User::convertTokens() {
    int tokensToConvert;
    cout << "\n--- Convert Tokens to PHP ---\n";
    cout << "Current exchange rate: 1 Token = PHP 3.00\n";
    cout << "How many tokens would you like to convert to PHP? ";
    
    if (!getNumericInput(tokensToConvert, "Tokens: ", "Invalid amount. Please enter a positive number.", 1, tokenBalance)) {
        return;
    }

    char choice;
    int phpAmount = tokensToConvert * tokenToPHPValue;
    cout << "You will receive PHP" << phpAmount << " for " << tokensToConvert << " tokens.\n";
    cout << "Confirm conversion? (y/n): ";
    
    if (!getYesNoInput(choice, "Choice: ", "Invalid choice.")) {
        return;
    }

    if (choice == 'y') {
        int newBalance = tokenBalance - tokensToConvert;
        updateBalanceInFile(newBalance);
        recordTransaction("CONVERSION", -tokensToConvert, newBalance);
        viewBalance();
        cout << "Conversion successful! New balance: " << newBalance << " tokens.\n";

    } else {
        cout << "Conversion cancelled.\n";
    }
}

void User::notifications() {
    int choice;

    do {
        cout << "\n--- Notifications ---\n";
        cout << "\n---------------------\n";
        cout << "1. Back to Home\n";

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void User::transactions() {
    int choice;
    ifstream inFile(userType + "TokenTransactions.txt");
    
    do {
        cout << "\n--- Transaction History ---\n";
        cout << "---------------------------\n";
        
        if (inFile.is_open()) {
            string line;
            bool hasTransactions = false;
            
            while (getline(inFile, line)) {
                if (!line.empty()) {
                    stringstream ss(line);
                    string fileEmail, type, amountStr, balanceStr;
                    
                    getline(ss, fileEmail, ',');
                    getline(ss, type, ',');
                    getline(ss, amountStr, ',');
                    getline(ss, balanceStr);
                    
                    if (fileEmail == email) {
                        hasTransactions = true;
                        int amount = stoi(amountStr);
                        int balance = stoi(balanceStr);
                        
                        cout << "Type: " << type 
                             << " | Amount: " << (amount >= 0 ? "+" : "") << amount
                             << " | Balance: " << balance
                             << endl;
                    }
                }
            }
            
            if (!hasTransactions) {
                cout << "No transactions found.\n";
            }
            
            inFile.close();
            
        } else {
            cout << "No transaction history available.\n";
        }
        
        cout << "\n---------------------------\n";
        cout << "1. Back to Home\n";
        cout << "2. Refresh\n";  // Added refresh option

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 2)) {
            continue;
        }
        
        if (choice == 2) {
            inFile.open(userType + "TokenTransactions.txt");
        }

    } while (choice != 1);
}