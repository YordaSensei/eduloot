#pragma once
#include "../includes/admin_includes.h"

using namespace std;

struct Products {
    string shopName;
    string reqType;
    string name;
    double price;
    int quantity;
    string desc;
    string originalLine;
};

class MerchantRequestsModule {
    public:
        void merchantRequest();

    private:
        //core menus
        void handleProducts();
        void handleConcerns();
        void handleCashout();

        //sub-handlers for products
        void handleAddRequests(const vector<Products> &addRequests);
        void handleDeleteRequests(const vector<Products> &deleteRequests);
        void handleEditRequests(const vector<Products> &editRequests);

        //helpers
        void loadProductRequests(map <string, vector<Products>> &requestsByMerchant);
        vector<Products> filterByType(map<string, vector<Products>> &allRequests, const string &type);
};

void MerchantRequestsModule::merchantRequest() {
    int mainChoice;

    do {
        cout << termcolor::bold << termcolor::magenta;
            cout << "\n+-------------------------------+\n";
            cout << "|   " << termcolor::bright_yellow << "    MERCHANT REQUESTS       " << termcolor::magenta << "|\n";
            cout << "+-------------------------------+\n";
            cout << "|  1. Products                  |\n";
            cout << "|  2. Concerns                  |\n";
            cout << "|  3. Cash Out                  |\n";
            cout << "|  4. Back                      |\n";
            cout << "+-------------------------------+\n";

            mainChoice = promptChoice(1, 4, "Choice: ");
            system("cls");

            switch (mainChoice) {
                case 1: handleProducts(); break;
                case 2: handleConcerns(); break;
                case 3: handleCashout(); break;
                case 4: 
                    cout << termcolor::bright_red <<"Returning to admin menu...\n" << termcolor::reset; 
                    clearSystem(); break;
                default: 
                    cout << termcolor::bright_red << "\nInvalid choice!\n" << termcolor::reset;
                    continue;
            }
    } while (mainChoice != 4);
}

// groups the requests by merchant
void MerchantRequestsModule::loadProductRequests (map <string, vector<Products>> &requestsByMerchant) {
    ifstream productReqsFile ("productReq.txt");
    string line;

    while (getline(productReqsFile, line)) {
        if (line.empty()) continue;

        Products p;
        p.originalLine = line;
        string pricestr, quantitystr;
        stringstream split(line);

        getline (split, p.shopName, ',');
        getline (split, p.reqType, ',');
        getline (split, p.name, ',');

        if (p.reqType == "delete") {
            getline(split, p.desc);
            p.price = 0.00;
            p.quantity = 0;
        } else {
            getline (split, pricestr, ',');
            getline (split, quantitystr, ',');

            try {
                p.price = stod(pricestr);
                p.quantity = stoi(quantitystr);
            } catch (...) {
                continue;
            }
        }

        requestsByMerchant[p.shopName].push_back(p);
    }

    productReqsFile.close();
}

// groups the request by type according to merchant
vector<Products> MerchantRequestsModule::filterByType (map<string, vector<Products>> &allRequests, const string &type) {
    vector<Products> filtered;

    for (const auto &entry : allRequests) {
        for (const auto &product : entry.second) {
            if (product.reqType == type) {
                filtered.push_back(product);
            }
        }
    }

    return filtered;
}

void MerchantRequestsModule::handleProducts() {
    int productChoice;

    // loads all product requests grouped by merchant
    map<string, vector<Products>> allRequests;
    loadProductRequests(allRequests);

    // filter by type (still according to merchant)
    vector <Products> addRequests = filterByType (allRequests, "add");
    vector <Products> deleteRequests = filterByType (allRequests, "delete");
    vector <Products> editRequests = filterByType (allRequests, "edit");

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|   " << termcolor::bright_yellow << "     PRODUCT REQUESTS       " << termcolor::magenta << "|\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. Add Product               |\n";
        cout << "|  2. Delete Product            |\n";
        cout << "|  3. Edit Product              |\n";
        cout << "|  4. Back                      |\n";
        cout << "+-------------------------------+\n";

        productChoice = promptChoice(1, 4, "Choice: ");
        system("cls");

        switch (productChoice) {
            case 1: handleAddRequests(addRequests); break;
            case 2: handleDeleteRequests(deleteRequests); break;
            case 3: handleEditRequests(editRequests); break;
            case 4: 
                cout << termcolor::bright_red <<"Returning to menu...\n" << termcolor::reset; 
                clearSystem(); break;
            default: 
                cout << termcolor::bright_red << "\nInvalid choice!\n" << termcolor::reset;
        }

    } while (productChoice !=4);
}

// handles add requests
void MerchantRequestsModule::handleAddRequests(const vector<Products> &addRequests) {
    if (addRequests.empty()) {
        cout << termcolor::red << "(No pending add product requests)\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+----------------------------------------------+\n";
    cout << "|   " << termcolor::bright_yellow << "     Pending [Add] Product Requests     " << termcolor::magenta << "  |\n";
    cout << "+----------------------------------------------+\n";

        int displayedIndex = 1;
        for (size_t i = 0; i < addRequests.size(); i++) {
            const Products& p = addRequests[i];
            cout << termcolor::bright_white << displayedIndex << ". "
            << termcolor::bright_yellow << p.shopName << " | "
            << termcolor::cyan << p.reqType 
            << termcolor::bright_yellow << " | " << p.name << " | "
            << "P" << p.price << " | "
            << p.quantity << " pcs | "
            << termcolor::bright_yellow << p.desc << "\n";
        displayedIndex++;
    }

    cout << termcolor::reset;

    int index = promptChoice(1, addRequests.size(), "Enter request number to approve (0 to cancel): ");
    if (cancelInput(index)) {
        return;
    }

    const Products& selected = addRequests[index - 1];

    // add approved product to product list
    ofstream productListFile("productList.txt", ios::app);
    if (productListFile.is_open()) {
        productListFile << selected.shopName << ',' << selected.name << ','
                << selected.price << ',' << selected.quantity << ',' 
                << selected.desc << "\n";
        productListFile.close();
    }

    // log approved request
    ofstream approvedFile ("admin/files/approvedReq.txt", ios::app);
    if (approvedFile.is_open()) {
        approvedFile << selected.originalLine << "\n";
        approvedFile.close();
    }

    // remove request from file
    if (deleteLine("productReq.txt", selected.originalLine)) {
        cout << termcolor::green << "\nProduct approved and added to product list!\n Returning to menu..\n" << termcolor::reset;
        clearSystem(2000);
    }
}

// handles delete requests
void MerchantRequestsModule::handleDeleteRequests (const vector<Products> &deleteRequests) {
    if (deleteRequests.empty()) {
        cout << termcolor::red << "(No pending delete product requests)\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+----------------------------------------------+\n";
    cout << "|   " << termcolor::bright_yellow << "   Pending [Delete] Product Requests    " << termcolor::magenta << "  |\n";
    cout << "+----------------------------------------------+\n";

    int displayedIndex = 1;
    for (size_t i = 0; i < deleteRequests.size(); i++) {
        const Products& p = deleteRequests[i];
        cout << termcolor::bright_white << i + 1 << ". "
        << termcolor::bright_yellow << p.shopName << " | "
        << termcolor::cyan << p.reqType 
        << termcolor::bright_yellow << " | " << p.name << " | "
        << termcolor::white << p.desc << endl;
        displayedIndex++;
    }

    cout << termcolor::reset;

    int index = promptChoice(1, deleteRequests.size(), "Enter request number to approve (0 to cancel): ");
    if (cancelInput(index)) {
        return;
    }

    const Products selected = deleteRequests[index - 1];

    ifstream findProduct("productList.txt");
    string line, targetLine;
    while (getline(findProduct, line)) {
        stringstream split(line);
        string shop, name;

        getline(split, shop, ',');
        getline (split, name, ',');

        if (shop == selected.shopName && name == selected.name) {
            targetLine = line;
            break;
        }
    }
    findProduct.close();

    if (targetLine.empty()) {
        cout << termcolor::red << "Matching product not found in productList.txt.\n" << termcolor::reset;
        return;
    }

    if (deleteLine("productReq.txt", selected.originalLine) && deleteLine("productList.txt", targetLine)) {
        ofstream approvedFile("admin/files/approvedReq.txt", ios::app);
        approvedFile << selected.originalLine << "\n";
        approvedFile.close();
        
        cout << termcolor::green << "\nProduct deleted successfully.\n" << termcolor::reset;
        clearSystem(2000);
    }
}

// handles edit request
void MerchantRequestsModule::handleEditRequests (const vector<Products> &editRequests) {
    if (editRequests.empty()) {
        cout << termcolor::red << "(No pending edit product requests)\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+----------------------------------------------+\n";
    cout << "| " << termcolor::bright_yellow << "       Pending [Edit] Product Requests       " << termcolor::magenta << "|\n";
    cout << "+----------------------------------------------+\n";

    int displayedIndex = 1;
    for (size_t i = 0; i < editRequests.size(); i++) {
        const Products& p = editRequests[i];
        cout << termcolor::bright_white << displayedIndex << ". "
            << termcolor::bright_yellow << p.shopName << " | "
            << termcolor::cyan << p.reqType 
            << termcolor::bright_yellow << " | " << p.name << " | "
            << "P" << p.price << " | "
            << p.quantity << " pcs | "
            << termcolor::bright_yellow << p.desc << "\n";
        displayedIndex++;
    }

    cout << termcolor::reset;

    int index = promptChoice(1, editRequests.size(), "Enter request number to approve (0 to cancel): ");
    if (cancelInput(index)) {
        return;
    }

    const Products& selected = editRequests[index - 1];

    ifstream findProduct("productList.txt");
    string line, oldLine;
    while (getline(findProduct, line)) {
        string shopname, name;
        stringstream split(line);

        getline (split, shopname, ',');
        getline (split, name, ',');

        if (selected.shopName == shopname && selected.name == name) {
            oldLine = line;
        }
    }
    findProduct.close();

    if (oldLine.empty()) {
        cout << termcolor::red << "Original product not found in productList.txt.\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-------------------------+\n";
    cout << "| " << termcolor::bright_yellow << "   New Product Info    " << termcolor::magenta << "|\n";
    cout << "+-------------------------+\n";
    cout << termcolor::reset;

    string newName, newDesc;
    double newPrice;
    int newQty;

    newName = promptNonEmptyInput("New Name: ");
    if (cancelInput(newName)) {
        return;
    }
    newPrice = promptValidatedPrice("New Price: ");
    newQty = promptValidatedQuantity("New Quantity: ");
    newDesc = promptNonEmptyInput("New Description: ");
    if (cancelInput(newDesc)) {
        return;
    }

    cout << termcolor::reset;

    ostringstream newLineStream;
    newLineStream << selected.shopName << ',' << newName << ','
                  << fixed << setprecision(2) << newPrice << ','
                  << newQty << ',' << newDesc;
    string newLine = newLineStream.str();

    if (editLine("productList.txt", oldLine, newLine) && deleteLine("productReq.txt", selected.originalLine)) {
        ofstream approvedFile("admin/files/approvedReq.txt", ios::app);
        approvedFile << "edit," + newLine << endl;
        approvedFile.close();

        cout << termcolor::green << "\nProduct edited and request approved.\n" << termcolor::reset;
        clearSystem(2000);
    }
}

// handles concerns
void MerchantRequestsModule::handleConcerns() {
    vector <string> concerns;
    string line;

    ifstream inFile("concerns.txt");
    while (getline(inFile, line)) {
        concerns.push_back(line);
    }
    inFile.close();

    if (concerns.empty()) {
        cout << termcolor::red << "(No pending concerns)\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+------------------------------------+\n";
    cout << "| " << termcolor::bright_yellow << "     Pending Merchant Concerns     " << termcolor::magenta << "|\n";
    cout << "+------------------------------------+\n";
    cout << termcolor::reset;

    int displayedIndex = 1;
    for (size_t i = 0; i < concerns.size(); i++) {
        cout << termcolor::bright_white << displayedIndex << ". " 
        << termcolor::bright_yellow << concerns[i] << endl;
        displayedIndex++;
    }
    
    cout << termcolor::reset;

    int index = promptChoice(1, concerns.size(), "Enter request number to approve (0 to cancel): ");
    if (cancelInput(index)) {
        return;
    }

    string selectedConcern = concerns[index - 1];

    if (deleteLine("concerns.txt", selectedConcern)) {
        ofstream approvedFile("admin/files/approvedReq.txt", ios::app);
        approvedFile << "concern," + selectedConcern << endl;
        approvedFile.close();

        cout << termcolor::green << "\nConcern approved.\n" << termcolor::reset;
        clearSystem(2000);
    }
}

//handles cashout
void MerchantRequestsModule::handleCashout() {
    const double tokenRate = 3.00, fee = 0.05;

    struct cashoutRequest {
        string shopName;
        float tokenAmount;
        string originalLine;
    };

    vector<cashoutRequest> cashout;
    string line;

    ifstream cashoutFile("cashout.txt");
    while (getline(cashoutFile, line)) {
        cashoutRequest c;
        c.originalLine = line; 
        string tokenStr;
        stringstream ss(line);

        getline(ss, c.shopName, ',');
        getline(ss, tokenStr);

        try {
            c.tokenAmount = stof(tokenStr);
        } catch (...) {
            continue;
        }

        cashout.push_back(c);
    }
    cashoutFile.close();

    if (cashout.empty()) {
        cout << termcolor::red << "(No pending cash out requests)\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+------------------------------------+\n";
    cout << "| " << termcolor::bright_yellow << "     Pending Merchant Cash Out     " << termcolor::magenta << "|\n";
    cout << "+------------------------------------+\n";
    cout << termcolor::reset;

    int displayedIndex = 1;
    for (size_t i = 0; i < cashout.size(); i++) {
        cout << termcolor::bright_yellow << displayedIndex << ". "
        << termcolor::bright_yellow << cashout[i].shopName << " | "
        << cashout[i].tokenAmount << endl;
        displayedIndex++;
    }

    int index = promptChoice(1, cashout.size(), "Enter request number to approve (0 to cancel): ");
    if (cancelInput(index)) {
        return;
    }

    const cashoutRequest selected = cashout[index - 1]; 

    vector <string> balanceLines;
    string walletLine;
    bool found = false;
    ifstream walletFile ("merchantBalance.txt");

    while (getline(walletFile, walletLine)) {
        stringstream split(walletLine);
        string shopname, balanceStr;

        getline (split, shopname, ',');
        getline (split, balanceStr, ',');

        if (shopname == selected.shopName) {
            int balance = stoi(balanceStr);

            if (balance < selected.tokenAmount) {
                cout << termcolor::bright_red << "\nERROR: Insufficient balance.\n" << termcolor::reset;
                return;
            }

            balance -= selected.tokenAmount;
            balanceLines.push_back(selected.shopName + ',' + to_string(balance));
            found = true;
        } else {
            balanceLines.push_back(walletLine);
        }
    }
    walletFile.close();

    if (!found) {
        cout << termcolor::red << "ERROR: Merchant balance not found.\n" << termcolor::reset;
        return;
    }

    ofstream walletOut("merchantBalance.txt");
    for (const auto& updatedLines : balanceLines) {
        walletOut << updatedLines << "\n";
    }
    walletOut.close();

    float gross = selected.tokenAmount * tokenRate;
    float net = gross - (gross * fee);

    updateTotalTokens(selected.tokenAmount); // system tokens increase
    updateTotalMoney(-net); // system cash decreases

    if (deleteLine("cashout.txt", selected.originalLine)) {
        ofstream approvedFile("admin/files/approvedReq.txt", ios::app);
        approvedFile << "cashout," << selected.originalLine << "\n"; 
        approvedFile.close();

        cout << termcolor::green << "\nTokens Successfully Cashed Out!\n";
        cout << "P" << net << " transferred\n" << termcolor::reset;
        clearSystem(3000);
    } 
}