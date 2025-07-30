#include "Wallet.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>
#include "../../admin/includes/admin_helpers.h"

using namespace std;

enum class WalletOption { ViewBalance = 1, Purchase, Convert, Back };

void Wallet::wallet() {
    int choice;

    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_cyan << "          Wallet            " << termcolor::blue << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. View Balance             |\n";
        cout << "|  2. Purchase Tokens          |\n";
        cout << "|  3. Convert to Cash          |\n";
        cout << "|  4. "<< termcolor::bright_cyan <<"Back to Home             "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n"<< termcolor::reset;

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 4)) {
            continue;
        }

        switch(static_cast<WalletOption>(choice)) {
            case WalletOption::ViewBalance:
                system("cls");
                viewBalance();
                break;
            case WalletOption::Purchase:
                system("cls");
                purchaseTokens();
                break;
            case WalletOption::Convert:
                system("cls");
                convertTokens();
                break;
            case WalletOption::Back:
                cout << termcolor::red << "Returning to Home...\n";
                clearSystem();
            break;
        }
    } while (choice != 4);
}

void Wallet::viewBalance() {
    initializeBalanceIfNeeded(getUserType() + "Balance.txt");
    
    string line;
    ifstream inFile(getUserType() + "Balance.txt");

    int choice;

    do {
        while (getline(inFile, line)) {
            if (!line.empty()) {
                string strBalance;
                stringstream split(line);
                string fileEmail;

                getline(split, fileEmail, ',');
                getline(split, strBalance);

                if (fileEmail == getEmail()) {
                    setTokenBalance(stoi(strBalance));
                    cout << termcolor::bold << termcolor::blue;
                    cout << "\n+------------------------------+\n";
                    cout << "|" << termcolor::bright_cyan << " Token Balance: " << setw(13) << left <<  getTokenBalance() << termcolor::blue << "|";
                    cout << "\n+------------------------------+\n";
                    break;
                }
            }
        }
        inFile.close();

        cout << "1. " << termcolor::bright_cyan << "Back to Home\n";
        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 1)) {
            continue;
        }
    } while (choice != 1);
}

void Wallet::purchaseTokens() {
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
        int newBalance = getTokenBalance() + tokensToAdd;
        updateBalanceInFile(newBalance);
        recordTransaction("PURCHASE", tokensToAdd, newBalance);
        viewBalance();
        cout << "Purchase successful! New balance: " << newBalance << " tokens.\n";
    } else {
        cout << "Purchase cancelled.\n";
    }
}

void Wallet::convertTokens() {
    int tokensToConvert;
    cout << "\n--- Convert Tokens to PHP ---\n";
    cout << "Current exchange rate: 1 Token = PHP 3.00\n";
    cout << "How many tokens would you like to convert to PHP? ";
    
    if (!getNumericInput(tokensToConvert, "Tokens: ", "Invalid amount. Please enter a positive number.", 1, getTokenBalance())) {
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
        int newBalance = getTokenBalance() - tokensToConvert;
        updateBalanceInFile(newBalance);
        recordTransaction("CONVERSION", -tokensToConvert, newBalance);
        viewBalance();
        cout << "Conversion successful! New balance: " << newBalance << " tokens.\n";

    } else {
        cout << "Conversion cancelled.\n";
    }
}