#include "Purchase.h"
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include "../../admin/includes/admin_helpers.h"
#include "../../merchant/core/merchant_helpers.h"
#include "../../product_helpers.h"

void Purchase::purchase() {
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

void Purchase::displayProducts(const std::string& selectedMerchant) {
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

bool Purchase::processPurchase(const std::string& selectedMerchant, const Product& product, int productQty, int totalAmount) {
    ifstream balanceFile(getUserType() + "Balance.txt");
    string line;
    int userBalance = 0;
    bool userFound = false;

    while (getline(balanceFile, line)) {
        if (!line.empty()) {
            string fileEmail, strBalance;
            stringstream split(line);
            getline(split, fileEmail, ',');
            getline(split, strBalance);

            if (fileEmail == getEmail()) {
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

void Purchase::updateProductQuantity(const std::string& selectedMerchant, const Product& product, int productQty) {
        vector<Product> products;
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

                if (p.merchant == selectedMerchant && p.name == product.name) {
                    p.quantity -= productQty;
                }

                products.push_back(p);
            }
        }
        productInFile.close();

        ofstream productOutFile("productList.txt");
        for (const auto& p : products) {
            productOutFile << p.merchant << "," << p.name << "," 
                        << p.price << "," << p.quantity << "," 
                        << p.desc << endl;
        }
        productOutFile.close();
}

void Purchase::recordProductTransaction(const std::string& selectedMerchant,
                                  const Product& product,
                                  int totalAmount,
                                  int productQty,
                                  const std::string& currentUserBalance,
                                  const std::string& currentMerchantBalance) {
        time_t now = time(0);
        string dt = ctime(&now);
        dt.pop_back();

        ofstream transactionOutFile(getUserType() + "ProductTransactions.txt", ios::app);
        transactionOutFile << getEmail() << "," << selectedMerchant << "," 
                        << product.name << "," << totalAmount << "," 
                        << productQty << "," << currentUserBalance << "," 
                        << currentMerchantBalance << "," << dt << endl;
        transactionOutFile.close();
}