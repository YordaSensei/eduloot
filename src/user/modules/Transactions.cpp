#include "Transactions.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../admin/includes/admin_helpers.h"

void Transactions::transactions() {
    int choice;
    ifstream tokenInFile(getUserType() + "TokenTransactions.txt");
    ifstream productInFile(getUserType() + "ProductTransactions.txt");
    
    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "      Token Transactions      "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n" << endl;
        
        if (tokenInFile.is_open()) {
            string line;
            bool hasTransactions = false;
            
            while (getline(tokenInFile, line)) {
                if (!line.empty()) {
                    stringstream ss(line);
                    string fileEmail, type, amountStr, balanceStr;
                    
                    getline(ss, fileEmail, ',');
                    getline(ss, type, ',');
                    getline(ss, amountStr, ',');
                    getline(ss, balanceStr);
                    
                    if (fileEmail == getEmail()) {
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
            
            tokenInFile.close();

        } else {
            cout << "No token transaction history available.\n";
        }

        cout << "\n+------------------------------+\n" << endl;

        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "     Product Transactions     "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n" << endl;

        if (productInFile.is_open()) {
            string line;
            bool hasTransactions = false;
            
            while (getline(productInFile, line)) {
                if (!line.empty()) {
                    string fileEmail, merchant, name, price, quantity, userBal, merchantBal, time;
                    stringstream split(line);

                    getline(split, fileEmail, ',');
                    getline(split, merchant, ',');
                    getline(split, name, ',');
                    getline(split, price, ',');
                    getline(split, quantity, ',');
                    getline(split, userBal, ',');
                    getline(split, merchantBal, ',');
                    getline(split, time);

                    if (fileEmail == getEmail()) {
                        cout << "You bought " << quantity << " " << name << "(s) from " << merchant
                        << " for " << price << " token(s) at " << time << " | You currently have " << userBal << " token(s)." << endl;
                    }
                }
            }
            
            if (!hasTransactions) {
                cout << "No transactions found.\n";
            }
            
            productInFile.close();

        } else {
            cout << "No product transaction history available.\n";
        }


        cout << "\n+------------------------------+\n" << endl;
        
        cout << "1. " << termcolor::bright_cyan << "Back to Home\n" << termcolor::blue;
        cout << "2. " << termcolor::bright_cyan << "Refresh\n";

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 2)) {
            continue;
        }
        
        if (choice == 2) {
            tokenInFile.open(getUserType() + "TokenTransactions.txt");
            productInFile.open(getUserType() + "ProductTransactions.txt");
        }

    } while (choice != 1);
}