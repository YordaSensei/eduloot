#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

            try {
                p.price = stod(priceStr);
                p.quantity = stoi(quantityStr);
            } catch (...) {
                continue;
            }

            if (store == email) {
                productList.push_back(p);
            }
        }
    }
    inFile.close();

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

    cout << "Reason for deletion: ";
    cin.ignore();
    getline(cin, reason);

    ofstream outFile("productReq.txt", ios::app);
    outFile << email << ",delete," << productList[choice - 1].name << "," << reason << endl;
    outFile.close();
    
    cout << "Deletion requested to admin.\n";
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

            productList.push_back(p);
        }
    }
    inFile.close();

    if (productList.empty()) {
        cout << "No products available to edit.\n";
        return;
    }

    cout << "\n--- Choose a product to edit ---\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << i + 1 << ". " << productList[i].name
             << " (Current Stock: " << productList[i].quantity << ")\n";
    }

    int choice;
    cout << "Enter product number to edit: ";
    cin >> choice;

    if (choice < 1 || choice > productList.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    int newQty;
    cout << "Enter new stock quantity for " << productList[choice - 1].name << ": ";
    cin >> newQty;

    productList[choice - 1].quantity = newQty;

    ofstream outFile("productList.txt");
    for (const Product& p : productList) {
        outFile << email << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;
    }
    outFile.close();

    cout << "Stock updated successfully.\n";
}

void viewRequests() {
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
        string email, action, name, price, quantity, desc;

        getline(ss, email, ',');
        getline(ss, action, ',');
        getline(ss, name, ',');
        getline(ss, price, ',');
        getline(ss, quantity, ',');
        getline(ss, desc);

        string formatted = "Requested by: " + email +
                           "\n  Product: " + name +
                           "\n  Price: " + price +
                           "\n  Quantity: " + quantity +
                           "\n  Description: " + desc + "\n";

        if (action == "add") {
            addRequests.push_back(formatted);
        } else if (action == "delete") {
            deleteRequests.push_back(formatted);
        } else if (action == "change_price") {
            changePriceRequests.push_back(formatted);
        } else if (action == "cashout") {
            cashoutRequests.push_back(formatted);
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

    if (!cashoutRequests.empty()) {
        cout << "\n[Cashout Requests]\n";
        for (const string& req : cashoutRequests) {
            cout << req << endl;
        }
    }

    if (addRequests.empty() && deleteRequests.empty() && changePriceRequests.empty() && cashoutRequests.empty()) {
        cout << "No requests found.\n";
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
                break;
            case 4:
                break;
            case 5:
                viewRequests();
                break;
        }
    } while (choice != 6);
}