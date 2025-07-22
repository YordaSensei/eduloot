#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "product_helpers.h"

using namespace std;

void editStock(string email) {
    vector<Product> productList;
    ifstream inFile("productList.txt");
    string line;

    while (getline(inFile, line)) {
        if (!line.empty()) {
            Product p;
            string strPrice, strQuantity;
            stringstream split(line);

            getline(split, p.merchant, ',');
            getline(split, p.name, ',');
            getline(split, strPrice, ',');
            getline(split, strQuantity, ',');
            getline(split, p.desc);

            p.price = stoi(strPrice);
            p.quantity = stoi(strQuantity);

            productList.push_back(p);
        }
    }
    inFile.close();

    vector<Product> merchantProducts;
    for (Product& p : productList) { 
        if (p.merchant == email){
            merchantProducts.push_back(p);
        }
    }

    if (merchantProducts.empty()) {
        cout << "No products available to edit.\n";
        return;
    }

    cout << "\n--- Choose a product to edit ---\n";
    for (size_t i = 0; i < merchantProducts.size(); ++i) {
        cout << i + 1 << ". " << merchantProducts[i].name
             << " (Current Stock: " << merchantProducts[i].quantity << ")\n";
    }

    int choice;
    cout << "Enter product number to edit: ";
    cin >> choice;

    if (choice < 1 || choice > merchantProducts.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    int newQty;
    cout << "Enter new stock quantity for " << merchantProducts[choice - 1].name << ": ";
    cin >> newQty;

    for (Product& p : productList) {
        if (p.merchant == email && p.name == merchantProducts[choice - 1].name) {
            p.quantity = newQty;
            break;
        }
    }

    ofstream outFile("productList.txt");
    for (const Product& p : productList) {
        outFile << p.merchant << "," << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;
    }
    outFile.close();

    cout << "Stock updated successfully.\n";
}

void products(string email) {
    int choice;

    do {
        cout << "\n--- Products ---\n";

        ifstream inFile("productList.txt");
        string line;
        bool hasProducts = false;
        vector<Product> merchantProducts;

        while (getline(inFile, line)) {
            if (!line.empty()) {
                Product p;
                stringstream split(line);
                string priceStr, quantityStr;

                getline(split, p.merchant, ',');
                getline(split, p.name, ',');
                getline(split, priceStr, ',');
                getline(split, quantityStr, ',');
                getline(split, p.desc);

                p.price = stoi(priceStr);
                p.quantity = stoi(quantityStr);

                if (p.merchant == email) {
                    hasProducts = true;
                    merchantProducts.push_back(p);

                    cout << "Name: " << p.name
                     << " | Token Price: " << p.price
                     << " | Quantity: " << p.quantity
                     << " | Description: " << p.desc << endl;
                }   
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
                editStock(email);
                break;
            case 2:
                cout << "Returning to home...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 2);
}