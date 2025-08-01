#pragma once
#include "../core/merchant_helpers.h"

class MerchantRequest {
    public:
        void requestAdmin(string email);

    private:
        void reqAddProduct(string email);
        void reqDeleteProduct(string email);
        void reqCashout(string email);
        void reqChangePrice(string email);
        void viewRequests(string email);
};

void MerchantRequest::reqAddProduct(string email) {
    ofstream outFile("productReq.txt", ios::app);
    Product p;

    cout << termcolor::bold << termcolor::yellow;
    cout << "\n+------------------------------+\n";
    cout << "|  " << termcolor::bright_white << "       Add Product          " << termcolor::yellow << "|\n";
    cout << "+------------------------------+\n";

    p.name = promptNonEmptyInput("Enter name: ");
    p.price = promptValidatedQuantity("Enter Price: ");
    p.quantity = promptValidatedQuantity("Enter Quantity: ");
    p.desc = promptNonEmptyInput("Enter description: ");

    outFile << email << ",add," << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;

    outFile.close();
    cout << termcolor::red << "Product requested to admin.\n";
    clearSystem();
}

void MerchantRequest::reqDeleteProduct(string email) {
    vector<Product> productList;
    ifstream inFile("productList.txt");
    string line;

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

    cout << termcolor::bold << termcolor::yellow;
    cout << "\n+------------------------------+\n";
    cout << "|  " << termcolor::bright_white << "      Delete Product        " << termcolor::yellow << "|\n";
    cout << "+------------------------------+\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". " << productList[i].name
             << " (Current Stock: " << productList[i].quantity << ")\n";
    }
    cout << "+------------------------------+\n";

    int choice = promptChoice(1,productList.size(),"Enter product number to delete (0 to cancel): ");

    if (choice == 0) {
        cout << termcolor::red << "\nCancelled. Returning to menu...\n" << termcolor::reset;
        clearSystem(1200);
        return;
    } 

    string reason = promptNonEmptyInput("Reason for deletion: ");

    ofstream outFile("productReq.txt", ios::app);
    outFile << email << ",delete," << productList[choice - 1].name << "," << reason << endl;
    outFile.close();

    cout << termcolor::red << "Deletion requested to admin.\n";
    clearSystem(2000);
}

void MerchantRequest::reqCashout(string email) {
    cout << termcolor::bold << termcolor::yellow;
    cout << "\n+------------------------------+\n";
    cout << "|  " << termcolor::bright_white << "      Request Cashout       " << termcolor::yellow << "|\n";
    cout << "+------------------------------+\n";

    cout << "How many tokens would you like to convert?\n";
    cout << "(PHP 3.00 = 1 Token) with a 5 percent fee.\n";
    int quantity = promptValidatedQuantity("Tokens to convert: ");

    float totalAmount = (quantity *3.0f) * 0.95f;
    cout << termcolor::yellow << "Total amount is PHP " << totalAmount << " (fee included).\n";
    
    cout << "Are you sure you want to convert " << quantity << " tokens? (1 - Yes, 0 - No)\n";
    int choice = promptChoice (1,1,"Choice: ");

    if (choice == 0) {
        cout << termcolor::red << "\nCancelled. Returning to menu...\n" << termcolor::reset;
        clearSystem(1200);
        return;
    } 

    if (choice = 1){
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

                        cout << termcolor::red << quantity << " tokens requested for cashout.\n";
                        clearSystem(2000);
                    } else {
                        cout << termcolor::red << "You have don't have enough tokens to cashout.\n";
                        clearSystem(2000);
                    }
                }
            }
        }
        inFile.close();
    }
}

void MerchantRequest::reqChangePrice(string email) {
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
        cout << termcolor::red << "No products available to request price change.\n";
        return;
    }

    cout << termcolor::bold << termcolor::yellow;
    cout << "\n+------------------------------+\n";
    cout << "|  " << termcolor::bright_white << "    Request Price Change    " << termcolor::yellow << "|\n";
    cout << "+------------------------------+\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". " << productList[i].name
             << " (Current Price: " << productList[i].price << ")\n";
    }

    int choice = promptChoice (1,productList.size(),"Enter product number to change price (0 to cancel): ");
    if (choice == 0) {
        cout << termcolor::red << "\nCancelled. Returning to menu...\n" << termcolor::reset;
        clearSystem(1200);
        return;
    } 

    int newPrice = promptValidatedQuantity("Enter new price: ");
    string reason = promptNonEmptyInput("Enter reason for price change: ");

    ofstream reqFile("productReq.txt", ios::app);
    if (!reqFile) {
        cout << termcolor::red << "ERROR: Cannot open productReq.txt\n";
        return;
    }

    reqFile << email << ",edit," << productList[choice - 1].name << "," << newPrice << "," << reason << "\n";

    reqFile.close();
    cout << termcolor::red << "Price change request submitted successfully.\n";
    clearSystem(2000);
}

void MerchantRequest::viewRequests(string email) {
    ifstream inFile("productReq.txt");
    string line;
    int choice;

    if (!inFile) {
        cout << termcolor::red << "\nERROR: Could not open productReq.txt\n";
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
        } else if (action =="edit") {
            string name, price, reason;
            getline(ss, name, ',');
            getline(ss, price, ',');
            getline(ss, reason);

            string formatted = "Product: " + name + "\nChange price to: " + price + "\nReason: " + reason + "\n";
            changePriceRequests.push_back(formatted);
        }
    }

    inFile.close();

    do {
        cout << termcolor::bold << termcolor::yellow;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_white << "      Product Request       " << termcolor::yellow << "|\n";
        cout << "+------------------------------+\n";

        if (!addRequests.empty()) {
            cout << termcolor::bold << termcolor::yellow;
            cout << "\n+------------------------------+\n";
            cout << "|  " << termcolor::bright_white << "   Add Product Requests     " << termcolor::yellow << "|\n";
            cout << "+------------------------------+\n";
            for (const string& req : addRequests) {
                cout << req << endl;
            }
        }

        if (!deleteRequests.empty()) {
            cout << termcolor::bold << termcolor::yellow;
            cout << "\n+------------------------------+\n";
            cout << "|  " << termcolor::bright_white << "  Delete Product Requests   " << termcolor::yellow << "|\n";
            cout << "+------------------------------+\n";
            for (const string& req : deleteRequests) {
                cout << req << endl;
            }
        }

        if (!changePriceRequests.empty()) {
            cout << termcolor::bold << termcolor::yellow;
            cout << "\n+------------------------------+\n";
            cout << "|  " << termcolor::bright_white << "   Change Price Requests    " << termcolor::yellow << "|\n";
            cout << "+------------------------------+\n";
            for (const string& req : changePriceRequests) {
                cout << req << endl;
            }
        }

        ifstream cashoutInFile("cashout.txt");

        cout << termcolor::bold << termcolor::yellow;
            cout << "\n+------------------------------+\n";
            cout << "|  " << termcolor::bright_white << "  Token Cashout Requests    " << termcolor::yellow << "|\n";
            cout << "+------------------------------+\n";
        while (getline(cashoutInFile, line)) {
            stringstream ss(line);
            string merchantEmail, amount;

            getline(ss, merchantEmail, ',');
            getline(ss, amount);

            if (merchantEmail == email) {
                cout << "Requested " << amount << " token(s) for cashout.\n";
            }
        }
        cout << "+------------------------------+\n";
        cout << "1. Back\n";
        do {
            choice = promptChoice(1,1,"Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
        

        switch (choice){
            case 1:
                system("cls");
                break;
        }     
    } while (choice != 1);
}

void MerchantRequest::requestAdmin(string email) {
    int choice;
    
    do {
        cout << termcolor::bold << termcolor::yellow;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_white << "     Request to Admin       " << termcolor::yellow << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. Add Product              |\n";
        cout << "|  2. Delete Product           |\n";
        cout << "|  3. Change Product Price     |\n";
        cout << "|  4. Cashout                  |\n";
        cout << "|  5. View Requests            |\n";
        cout << "|  6. Back to Home             |\n";
        cout << "+------------------------------+\n";
        do {
            choice = promptChoice(1,6,"Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
        
        system("cls");

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
            case 6:
                cout << termcolor::red << "Returning to Home...\n";
                clearSystem();
                break;
            default:
                clearSystem();
                break;
        }
    } while (choice != 6);
}