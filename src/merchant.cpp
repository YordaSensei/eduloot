#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
    string desc;
};

void reqAddProduct() {
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

    outFile << "add," << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;

    outFile.close();
    cout << "Product requested to admin.\n";
}

void reqDeleteProduct() {
    string reason;

    ofstream outFile("productReq.txt", ios::app);
    Product p;

    cout << "What would you like to delete? (Enter Product Name): ";
    cin.ignore();
    getline(cin, p.name);

    cout << "Reason for deletion: ";
    cin.ignore();
    getline(cin, reason);

    outFile << "delete," << p.name << "," << reason << endl;

    outFile.close();
    cout << "Deletion requested to admin.\n";
}

void reqChangePrice() {
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
        outFile << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;
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

    cout << "\n--- Product Request(s) ---\n";

    bool hasAdd = false, hasDelete = false, hasChange = false, hasCashout = false;

    inFile.clear();
    inFile.seekg(0);
    while (getline(inFile, line)) {
        if (line.substr(0, 4) == "add,") {
            if (!hasAdd) {
                cout << "\n[Add Product Requests]\n";
                hasAdd = true;
            }
            cout << line.substr(4) << endl;
        }
    }

    inFile.clear();
    inFile.seekg(0);
    while (getline(inFile, line)) {
        if (line.substr(0, 7) == "delete,") {
            if (!hasDelete) {
                cout << "\n[Delete Product Requests]\n";
                hasDelete = true;
            }
            cout << line.substr(7) << endl;
        }
    }

    inFile.clear();
    inFile.seekg(0);
    while (getline(inFile, line)) {
        if (line.substr(0, 13) == "change_price,") {
            if (!hasChange) {
                cout << "\n[Change Price Requests]\n";
                hasChange = true;
            }
            cout << line.substr(13) << endl;
        }
    }

    inFile.clear();
    inFile.seekg(0);
    while (getline(inFile, line)) {
        if (line.substr(0, 8) == "cashout,") {
            if (!hasCashout) {
                cout << "\n[Cashout Requests]\n";
                hasCashout = true;
            }
            cout << line.substr(8) << endl;
        }
    }

    if (!hasAdd && !hasDelete && !hasChange && !hasCashout) {
        cout << "No requests found.\n";
    }

    inFile.close();
}

void editStock() {
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
        outFile << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;
    }
    outFile.close();

    cout << "Stock updated successfully.\n";
}

void products() {
    int choice;

    do {
        cout << "\n--- Products ---\n";

        ifstream inFile("productList.txt");
        string line;
        bool hasProducts = false;

        while (getline(inFile, line)) {
            if (!line.empty()) {
                hasProducts = true;

                // Parse using your Product struct
                Product p;
                stringstream ss(line);
                string priceStr, quantityStr;

                getline(ss, p.name, ',');
                getline(ss, priceStr, ',');
                getline(ss, quantityStr, ',');
                getline(ss, p.desc);

                p.price = stod(priceStr);
                p.quantity = stoi(quantityStr);

                // Display the product
                cout << "Name: " << p.name
                     << " | Token Price: " << p.price
                     << " | Quantity: " << p.quantity
                     << " | Description: " << p.desc << endl;
            }
        }

        if (!hasProducts) {
            cout << "No products found.\n";
        }

        inFile.close();

        cout << "\n----------------\n";
        cout << "1. Edit Stock\n";
        cout << "2. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                editStock();
                break;
            case 2:
                cout << "Returning to home...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 2);
}

void sales() {
    int choice;

    do {
        cout << "\n--- Sales ---\n";
        cout << "1. View Total Sales\n";
        cout << "2. Transactions\n";
        cout << "3. Back to Home\n";
    } while (choice != 3);
}

void requestAdmin() {
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
                reqAddProduct();
                break;
            case 2:
                reqDeleteProduct();
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

void merchantMain() {
    int choice;

    do {
        cout << "\n--- Good day, Merchant! ---\n";
        cout << "1. Products\n";
        cout << "2. Sales\n";
        cout << "3. Request To Admin\n";
        cout << "4. QR Code\n";
        cout << "5. Log Out\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                products();
                break;
            case 2:
                sales();
                break;
            case 3:
                requestAdmin(); 
                break;
            case 4:
                break;
        }
    } while (choice != 5);

    cout << "Logging Out...";
}