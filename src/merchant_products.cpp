#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct Product {
    string name;
    double price;
    int quantity;
    string desc;
};

void editStock() {
    vector<Product> productList;
    ifstream inFile("productList.txt");
    string line;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            Product p;
            string priceStr, quantityStr;
            stringstream split(line);

            getline(split, p.name, ',');
            getline(split, priceStr, ',');
            getline(split, quantityStr, ',');
            getline(split, p.desc);

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
                stringstream split(line);
                string priceStr, quantityStr;

                getline(split, p.name, ',');
                getline(split, priceStr, ',');
                getline(split, quantityStr, ',');
                getline(split, p.desc);

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