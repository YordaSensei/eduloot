#pragma once
#include "../../product_helpers.h"

class MerchantProducts {
    public:
        void products(string email);
    
    private:
        void editStock(string email);
};

void MerchantProducts::editStock(string email) {
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
        cout << termcolor::red << "No products available to edit.\n";
        return;
    }

    cout << termcolor::bold << termcolor::yellow;
    cout << "\n+------------------------------+\n";
    cout << "|  " << termcolor::bright_white << "    Change Product Stock    " << termcolor::yellow << "|\n";
    cout << "+------------------------------+\n";
    for (size_t i = 0; i < merchantProducts.size(); ++i) {
        cout << i + 1 << ". " << merchantProducts[i].name
             << " (Current Stock: " << merchantProducts[i].quantity << ")\n";   
    }
    cout << "+------------------------------+\n";

    int choice = promptChoice (1,merchantProducts.size(),"Enter product number to edit stock (0 to cancel): ");
    if (choice == 0) {
        cout << termcolor::red << "\nCancelled. Returning to menu...\n" << termcolor::reset;
        clearSystem(1200);
        return;
    } 

    int newQty = promptValidatedQuantity("Enter new stock quantity: ");

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

    cout << termcolor::red << "Stock updated successfully.\n";
    clearSystem();
}

void MerchantProducts::products(string email) {
    int choice;

    do {
        cout << termcolor::bold << termcolor::yellow;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_white << "         Products           " << termcolor::yellow << "|\n";
        cout << "+------------------------------+\n";

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
            cout << termcolor::red << "No products found.\n";
        }

        inFile.close();

        cout << termcolor::yellow << "+------------------------------+\n";
        cout << "1. Edit Stock\n";
        cout << "2. Back to Home\n";
        do {
            choice = promptChoice(1,2,"Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
        system("cls");

        switch (choice) {
            case 1:
                editStock(email);
                break;
            case 2:
                cout << termcolor::red << "Returning to Home...\n";
                clearSystem();
                break;
            default:
                cout << termcolor::red << "Invalid choice.\n";
                clearSystem();
                break;
        }
    } while (choice != 2);
}