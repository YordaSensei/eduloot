#include <iostream>
#include <fstream>
#include <string>

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

    outFile << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;

    outFile.close();
    cout << "Product requested to admin.\n";
}

void viewRequests() {
    ifstream inFile("productReq.txt");
    string line;

    cout << "\n--- Product Request(s) ---\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

void products() {
    int choice;

    do {
        cout << "\n--- Products ---\n";
        cout << "\n----------------\n";
        cout << "1. Edit Stock\n";
        cout << "2. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:

                break;
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
    int reqChoice;

    do {
        cout << "\n--- What would you like to request? ---\n";
        cout << "1. Add Product\n";
        cout << "2. Delete Product\n";
        cout << "3. Change Product Price\n";
        cout << "4. Cashout\n";
        cout << "5. View Requests\n";
        cout << "6. Back to Home\n";

        switch(reqChoice) {
            case 1:
                reqAddProduct();
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                viewRequests();
                break;
        }
    } while (reqChoice != 6);
}

int main() {
    int mainChoice;

    do {
        cout << "\n--- Good day, Merchant! ---\n";
        cout << "1. Products\n";
        cout << "2. Sales\n";
        cout << "3. Request To Admin\n";
        cout << "4. QR Code\n";
        cout << "5. Log Out\n";
        cout << "Choice: ";
        cin >> mainChoice;

        switch(mainChoice) {
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
    } while (mainChoice != 5);

    cout << "Logging Out...";
    return 0;
}