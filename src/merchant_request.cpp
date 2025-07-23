#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "merchant_helpers.h"

using namespace std;

void reqAddProduct(string email) {
    ofstream outFile("productReq.txt", ios::app);
    Product p;

    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Enter Price: ";
    cin >> p.price;

    cout << "Enter quantity: ";
    cin >> p.quantity;

    cout << "Enter short description: ";
    cin.ignore();
    getline(cin, p.desc);

    outFile << email << ",add," << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;

    outFile.close();
    cout << "Product requested to admin.\n";
}

void reqDeleteProduct(string email) {
    vector<Product> productList;
    ifstream inFile("productList.txt");
    string line, reason;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            Product p;
            string priceStr, quantityStr, store;
            stringstream ss(line);

            getline(ss, store, ',');
            getline(ss, p.name, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, p.desc);

            if (store == email) {
                try {
                    p.price = stod(priceStr);
                    p.quantity = stoi(quantityStr);
                } catch (...) {
                    continue; // skip invalid lines
                }
                productList.push_back(p);
            }
        }
    }
    inFile.close();

    if (productList.empty()) {
        cout << "No products found for deletion.\n";
        return;
    }

    cout << "\n--- Choose a product to delete ---\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". " << productList[i].name
             << " (Current Stock: " << productList[i].quantity << ")\n";
    }

    int choice;
    cout << "Enter product number to delete: ";
    cin >> choice;

    if (choice < 1 || choice > productList.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    cin.ignore(); // flush newline
    cout << "Reason for deletion: ";
    getline(cin, reason);

    ofstream outFile("productReq.txt", ios::app);
    outFile << email << ",delete," << productList[choice - 1].name << "," << reason << endl;
    outFile.close();

    cout << "Deletion requested to admin.\n";
}

void reqCashout(string email) {
    int quantity;
    cout << "How many tokens would you like to convert?\n";
    cout << "(PHP 3.00 = 1 Token) with a 5 percent fee.\n";
    cout << "Tokens to convert: ";
    cin >> quantity;

    char choice;
    float totalAmount = (quantity *3.0f) * 0.95f;
    cout << "Total amount is PHP " << totalAmount << " (fee included).\n";
    cout << "Are you sure you want to convert " << quantity << " tokens? (y/n)\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y'){
        vector<MerchantAcc> balance;
        MerchantAcc m;
        string line;
        
        ifstream inFile("merchantBalance.txt");
        while (getline(inFile, line)) {
            if (!line.empty()) {
                string strBalance;
                stringstream ss(line);
                getline(ss, m.email, ',');
                getline(ss, strBalance);
                m.balance = stoi(strBalance);

                if (m.email == email){
                    if (m.balance >= quantity){
                        ofstream outFile("cashout.txt", ios::app);
                        outFile << email << "," << quantity << endl;
                        outFile.close();

                        cout << quantity << " tokens requested for cashout.\n";
                    } else {
                        cout << "You have don't have enough tokens to cashout.\n";
                    }
                }
            }
        }
        inFile.close();
    }
}

void reqChangePrice(string email) {
    vector<Product> productList;
    ifstream inFile("productList.txt");
    string line;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            Product p;
            string priceStr, quantityStr;
            stringstream ss(line);

            getline(ss, p.merchant, ',');
            getline(ss, p.name, ',');
            getline(ss, priceStr, ',');
            getline(ss, quantityStr, ',');
            getline(ss, p.desc);

            try {
                p.price = stod(priceStr);
                p.quantity = stoi(quantityStr);
            } catch (...) {
                continue;
            }

            if (p.merchant == email){
                productList.push_back(p);
            }
        }
    }
    inFile.close();

    if (productList.empty()) {
        cout << "No products available to request price change.\n";
        return;
    }

    cout << "\n--- Choose a product to request price change ---\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". " << productList[i].name
             << " (Current Price: " << productList[i].price << ")\n";
    }

    int choice;
    cout << "Enter product number to change price: ";
    cin >> choice;

    if (choice < 1 || choice > productList.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    double newPrice;
    cout << "Enter *new price* for " << productList[choice - 1].name << ": ";
    cin >> newPrice;

    cin.ignore();
    string reason;
    cout << "Enter reason for price change: ";
    getline(cin, reason);

    ofstream reqFile("productReq.txt", ios::app);
    if (!reqFile) {
        cout << "ERROR: Cannot open productReq.txt\n";
        return;
    }

    reqFile << email << ",change,"
            << productList[choice - 1].name << ","
            << newPrice << ","
            << reason << "\n";

    reqFile.close();
    cout << "Price change request submitted successfully.\n";
}

void viewRequests(string email) {
    ifstream inFile("productReq.txt");
    string line;

    if (!inFile) {
        cout << "\nERROR: Could not open productReq.txt\n";
        return;
    }

    vector<string> addRequests;
    vector<string> deleteRequests;
    vector<string> changePriceRequests;
    vector<string> cashoutRequests;

    while (getline(inFile, line)) {
        stringstream ss(line);
        string merchantEmail, action;

        getline(ss, merchantEmail, ',');
        getline(ss, action, ',');

        if (merchantEmail != email) {
            continue;
        }
        
        if (action == "add") {
            string name, price, quantity, desc;
            getline(ss, name, ',');
            getline(ss, price, ',');
            getline(ss, quantity, ',');
            getline(ss, desc);

            string formatted = "Product: " + name + "\nPrice: " + price + "\nQuantity: " + quantity + "\nDescription: " + desc + "\n";
            addRequests.push_back(formatted);
        } else if (action == "delete") {
            string name, reason;
            getline(ss, name, ',');
            getline(ss, reason);

            string formatted = "Product to delete: " + name + "\nReason: " + reason + "\n";
            deleteRequests.push_back(formatted);
        } else if (action == "change") {
            string name, price, reason;
            getline(ss, name, ',');
            getline(ss, price, ',');
            getline(ss, reason);

            string formatted = "Product: " + name + "\nChange price to: " + price + "\nReason: " + reason + "\n";
            changePriceRequests.push_back(formatted);
        }
    }

    inFile.close();

    cout << "\n--- Product Request(s) ---\n";

    if (!addRequests.empty()) {
        cout << "\n[Add Product Requests]\n";
        for (const string& req : addRequests) {
            cout << req << endl;
        }
    }

    if (!deleteRequests.empty()) {
        cout << "\n[Delete Product Requests]\n";
        for (const string& req : deleteRequests) {
            cout << req << endl;
        }
    }

    if (!changePriceRequests.empty()) {
        cout << "\n[Change Price Requests]\n";
        for (const string& req : changePriceRequests) {
            cout << req << endl;
        }
    }

    ifstream cashoutInFile("cashout.txt");

    cout << "\n[Token Cashout Requests]\n";
    while (getline(cashoutInFile, line)) {
        stringstream ss(line);
        string merchantEmail, amount;

        getline(ss, merchantEmail, ',');
        getline(ss, amount);

        if (merchantEmail == email) {
            cout << "Requested " << amount << " token(s) for cashout.\n";
        }
    }
}

void requestAdmin(string email) {
    int choice;

    do {
        cout << "\n--- What would you like to request? ---\n";
        cout << "1. Add Product\n";
        cout << "2. Delete Product\n";
        cout << "3. Change Product Price\n";
        cout << "4. Cashout\n";
        cout << "5. View Requests\n";
        cout << "6. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                reqAddProduct(email);
                break;
            case 2:
                reqDeleteProduct(email);
                break;
            case 3:
                reqChangePrice(email);
                break;
            case 4:
                reqCashout(email);
                break;
            case 5:
                viewRequests(email);
                break;
        }
    } while (choice != 6);
}