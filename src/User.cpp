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
#include <iomanip>

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
    vector<string> merchantList;
    ifstream merchantInFile("merchantAccounts.txt");
    string line;

    cout << "\n+------------------------------+\n";
    cout << "|      Select a Merchant       |\n";
    cout << "+------------------------------+\n";
    
    while (getline(merchantInFile, line)) {
        if (!line.empty()) {
            string merchantEmail, username, password;
            stringstream split(line);

            getline(split, merchantEmail, ',');
            getline(split, username, ',');
            getline(split, password);

            merchantList.push_back(merchantEmail);
            cout << "|  " << merchantList.size() << ". " << setw(25) << left << merchantEmail << "|" << endl;
        }
    }

    cout << "|  " << merchantList.size() + 1 << ". " << setw(25) << left << "Back to Home" << "|" << endl;
    cout << "+------------------------------+\n";
    merchantInFile.close();

    if (merchantList.empty()) {
        cout << "No merchants available.\n";
        return;
    }

    int merchantChoice;
    cout << "Select number of merchant: ";
    if (!getNumericInput<int>(merchantChoice, "", "Invalid choice.", 1, static_cast<int>(merchantList.size() + 1))) {
        return;
    }

    if (merchantChoice == merchantList.size() + 1) {
        cout << "Returning to Home...\n";
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

    cout << "\n+------------------------------+\n";
    cout << "|        " << selectedMerchant << " Products         |\n";
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
        cout << "2. Refresh\n";

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 2)) {
            continue;
        }
        
        if (choice == 2) {
            inFile.open(userType + "TokenTransactions.txt");
        }

    } while (choice != 1);
}