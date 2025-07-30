#include "../modules/User.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "../../admin/includes/admin_helpers.h"
#include "../../product_helpers.h"
#include "../../merchant/core/merchant_helpers.h"
#include <iomanip>

using namespace std;
    
enum class WalletOption { ViewBalance = 1, Purchase, Convert, Back };
int tokenToPHPValue = 3;

void User::wallet() {
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

void User::viewBalance() {
    initializeBalanceIfNeeded(userType + "Balance.txt");
    
    string line;
    ifstream inFile(userType + "Balance.txt");

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
                    cout << termcolor::bold << termcolor::blue;
                    cout << "\n+------------------------------+\n";
                    cout << "|" << termcolor::bright_cyan << " Token Balance: " << setw(13) << left <<  this->tokenBalance << termcolor::blue << "|";
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

void User::purchase() {
    vector<string> merchantList;
    ifstream merchantInFile("merchantAccounts.txt");
    string line;

    cout << termcolor::bold << termcolor::blue;
    cout << "\n+------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "      Select a Merchant       "<< termcolor::blue <<"|\n";
    cout << "+------------------------------+\n";
    
    while (getline(merchantInFile, line)) {
        if (!line.empty()) {
            string merchantEmail, username, password;
            stringstream split(line);

            getline(split, merchantEmail, ',');
            getline(split, username, ',');
            getline(split, password);

            merchantList.push_back(merchantEmail);
            cout << "|  " << merchantList.size() << ". " << setw(25) << left << merchantEmail << termcolor::blue << "|" << endl;
        }
    }

    cout << "|  " << merchantList.size() + 1 << ". " << setw(25) << left << termcolor::bright_cyan << "Back to Home" << termcolor::blue << "|" << endl;
    cout << "+------------------------------+\n";
    merchantInFile.close();

    if (merchantList.empty()) {
        cout << "No merchants available.\n";
        return;
    }

    int merchantChoice;
    if (!getNumericInput<int>(merchantChoice, "Select number of merchant: ", "Invalid choice.", 1, static_cast<int>(merchantList.size() + 1))) {
        return;
    }

    if (merchantChoice == merchantList.size() + 1) {
        cout << termcolor::red << "Returning to Home...\n";
        return;
    }

    string selectedMerchant = merchantList[merchantChoice - 1];
    displayProducts(selectedMerchant);
}


void User::displayProducts(const std::string& selectedMerchant) {
    vector<Product> productList;
    ifstream productInFile("productList.txt");
    string line;

    while (getline(productInFile, line)) {
        if (!line.empty()) {
            Product p;
            string strPrice, strQuantity;
            stringstream split(line);

            getline(split, p.merchant, ',');
            getline(split, p.name, ',');
            getline(split, strPrice, ',');
            getline(split, strQuantity, ',');
            getline(split, p.desc);

            p.price = stod(strPrice);
            p.quantity = stoi(strQuantity);

            if (p.merchant == selectedMerchant) {
                productList.push_back(p);
            }
        }
    }
    productInFile.close();

    if (productList.empty()) {
        cout << "No products available for this merchant.\n";
        return;
    }
    
    cout << termcolor::bold << termcolor::blue;
    cout << "\n+------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "        " << selectedMerchant << " Products         "<< termcolor::blue <<"|\n";
    cout << "+------------------------------+\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << (i + 1) << ". " << productList[i].name 
             << " | Price: " << productList[i].price << " tokens" 
             << " | Stock(s) left: " << productList[i].quantity << endl;
    }
    cout << "+------------------------------+\n";

    int productChoice;
    cout << "Select number of product: ";
    if (!getNumericInput<int>(productChoice, "", "Invalid product selection.", 1, static_cast<int>(productList.size()))) {
        return;
    }

    int productQty;
    cout << "Quantity: ";
    if (!getNumericInput(productQty, "", "Invalid quantity.", 1)) {
        return;
    }

    Product selectedProduct = productList[productChoice - 1];
    int totalAmount = productQty * selectedProduct.price;

    if (productQty > selectedProduct.quantity) {
        cout << "Not enough stock available.\n";
        return;
    }

    cout << "Selected: " << selectedProduct.name << " | Price: " << selectedProduct.price << " tokens" << endl;
    cout << "Total Amount: " << totalAmount << endl;
    
    char confirm;
    cout << "Are you sure you want to purchase " << productQty << " " << selectedProduct.name << "? (y/n): ";
    if (!getYesNoInput(confirm, "", "Invalid choice.")) {
        return;
    }

    if (confirm == 'y') {
        if (processPurchase(selectedMerchant, selectedProduct, productQty, totalAmount)) {
            cout << "Purchased successfully!\n";
        }
    } else {
        cout << "Purchase cancelled.\n";
    }
}

bool User::processPurchase(const std::string& selectedMerchant, const Product& product, int productQty, int totalAmount) {
    ifstream balanceFile(userType + "Balance.txt");
    string line;
    int userBalance = 0;
    bool userFound = false;

    while (getline(balanceFile, line)) {
        if (!line.empty()) {
            string fileEmail, strBalance;
            stringstream split(line);
            getline(split, fileEmail, ',');
            getline(split, strBalance);

            if (fileEmail == email) {
                userBalance = stoi(strBalance);
                userFound = true;
                break;
            }
        }
    }
    balanceFile.close();

    if (!userFound) {
        cout << "User balance not found.\n";
        return false;
    }

    if (userBalance < totalAmount) {
        cout << "You don't have enough tokens to purchase.\n";
        return false;
    }

    updateBalanceInFile(userBalance - totalAmount);
    
    vector<MerchantAcc> merchantBalance;
    bool merchantFound = false;
    ifstream merchantInFile("merchantBalance.txt");
    
    while (getline(merchantInFile, line)) {
        if (!line.empty()) {
            MerchantAcc m;
            string strBalance;
            stringstream split(line);

            getline(split, m.email, ',');
            getline(split, strBalance);
            m.balance = stoi(strBalance);

            if (m.email == selectedMerchant) {
                m.balance += totalAmount;
                merchantFound = true;
            }

            merchantBalance.push_back(m);
        }
    }
    merchantInFile.close();

    if (!merchantFound) {
        MerchantAcc nm;
        nm.email = selectedMerchant;
        nm.balance = totalAmount;
        merchantBalance.push_back(nm);
    }

    ofstream merchantOutFile("merchantBalance.txt");
    for (const auto& m : merchantBalance) {
        merchantOutFile << m.email << "," << m.balance << endl;
    }
    merchantOutFile.close();

    updateProductQuantity(selectedMerchant, product, productQty);

    string currentUserBalance = to_string(userBalance - totalAmount);
    string currentMerchantBalance = to_string(merchantFound ? 
        merchantBalance.back().balance : totalAmount);
    
    recordProductTransaction(selectedMerchant, product, totalAmount, 
                           productQty, currentUserBalance, 
                           currentMerchantBalance);

    return true;
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
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+--------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "          NOTIFICATIONS         " << termcolor::blue << "|\n";
        cout << "+--------------------------------+\n";
        cout << termcolor::reset;
        
        displayAdminMessages();
        
        displaySystemAlerts();
        
        cout << termcolor::bold << termcolor::blue;
        cout << "+--------------------------------+\n";
        cout << "| 1. " << termcolor::bright_cyan << "Back to Home " << termcolor::blue << setw(17) << "|\n";
        cout << "| 2. " << termcolor::bright_cyan << "Refresh" << termcolor::blue << setw(23) << "|\n";
        cout << "+--------------------------------+\n";
        cout << termcolor::reset;

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 2)) {
            continue;
        }
        
        if (choice == 2) {
            system("cls");
        }
    } while (choice != 1);
}

void User::displayAdminMessages() {
    cout << termcolor::bold << termcolor::blue;
    cout << "\n+--------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "       MESSAGES FROM ADMIN      " << termcolor::blue << "|\n";
    cout << "+--------------------------------+\n";
    cout << termcolor::reset;
    
    ifstream msgFile(userType + "AdminMessages.txt");
    string line;
    bool hasMessages = false;
    
    while (getline(msgFile, line)) {
        if (!line.empty()) {
            string recipient, message;
            stringstream ss(line);
            
            getline(ss, recipient, ',');
            getline(ss, message);
            
            if (recipient == email || recipient == userType) {
                cout << " • " << message << "\n";
                hasMessages = true;
            }
        }
    }
    
    if (!hasMessages) {
        cout << " No messages from admin.\n";
    }
    
    msgFile.close();
    cout << termcolor::blue << "+--------------------------------+\n";
    cout << termcolor::reset;
}

void User::displaySystemAlerts() {
    cout << termcolor::bold << termcolor::blue;
    cout << "\n+--------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "          SYSTEM ALERTS         " << termcolor::blue << "|\n";
    cout << "+--------------------------------+\n";
    cout << termcolor::reset;
    
    ifstream balanceFile(userType + "Balance.txt");
    string line;
    bool hasAlerts = false;
    
    while (getline(balanceFile, line)) {
        if (!line.empty()) {
            string fileEmail, strBalance;
            stringstream ss(line);
            
            getline(ss, fileEmail, ',');
            getline(ss, strBalance);
            
            if (fileEmail == email) {
                int balance = stoi(strBalance);
                if (balance < 0) {
                    cout << termcolor::red << " ⚠ Your balance is negative (" << balance 
                         << " tokens). Please settle your debt.\n";
                    hasAlerts = true;
                }
            }
        }
    }
    balanceFile.close();
    
    ifstream alertsFile("systemAlerts.txt");
    while (getline(alertsFile, line)) {
        if (!line.empty()) {
            string recipient, alert;
            stringstream ss(line);
            
            getline(ss, recipient, ',');
            getline(ss, alert);
            
            if (recipient == email || recipient == "ALL") {
                cout << " ⚠ " << alert << "\n";
                hasAlerts = true;
            }
        }
    }
    alertsFile.close();
    
    if (!hasAlerts) {
        cout << " No system alerts.\n";
    }
    
    cout << termcolor::blue << "+--------------------------------+\n";
    cout << termcolor::reset;
}

void User::transactions() {
    int choice;
    ifstream tokenInFile(userType + "TokenTransactions.txt");
    ifstream productInFile(userType + "ProductTransactions.txt");
    
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

                    if (fileEmail == email) {
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
            tokenInFile.open(userType + "TokenTransactions.txt");
            productInFile.open(userType + "ProductTransactions.txt");
        }

    } while (choice != 1);
}