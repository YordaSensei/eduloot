#include <vector>
#include "product_helpers.h"

void purchase(string email) {
    vector<string> merchantList;
    ifstream merchantInFile("merchantAccounts.txt");
    string line;

    cout << "\n--- Select a Merchant ---\n";
    while (getline(merchantInFile, line)) {
        if (!line.empty()) {
            string merchantEmail, username, password;
            stringstream split(line);

            getline(split, merchantEmail, ',');
            getline(split, username, ',');
            getline(split, password);

            merchantList.push_back(merchantEmail);
            cout << merchantList.size() << ". " << merchantEmail << endl;
        }
    }
    merchantInFile.close();

    if (merchantList.empty()) {
        cout << "No merchants available.\n";
        return;
    }

    int merchantChoice;
    cout << "Select number of merchant: ";
    cin >> merchantChoice;

    if (merchantChoice < 1 || merchantChoice > merchantList.size()) {
        cout << "Invalid choice.\n";
        return;
    }

    string selectedMerchant = merchantList[merchantChoice - 1];

    vector<Product> filteredProducts;
    ifstream productInFile("productList.txt");

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
                filteredProducts.push_back(p);
            }
        }
    }
    productInFile.close();

    if (filteredProducts.empty()) {
        cout << "No products available for this merchant.\n";
        return;
    }

    cout << "\n--- Choose a product to purchase ---\n";
    for (size_t i = 0; i < filteredProducts.size(); ++i) {
        cout << i + 1 << ". " << filteredProducts[i].name
             << " | Price: PHP " << filteredProducts[i].price
             << " | Stock(s) left: " << filteredProducts[i].quantity << endl;
    }

    int productChoice;
    cout << "Select number of product: ";
    cin >> productChoice;

    if (productChoice < 1 || productChoice > filteredProducts.size()) {
        cout << "Invalid product selection.\n";
        return;
    }

}
