#include <iostream>
#include <fstream>
#include <string>
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
    cout << "Deletion equested to admin.\n";
}

void viewRequests() {
    ifstream inFile("productReq.txt");
    string line;

    cout << "\n--- Product Request(s) ---\n";

    vector<string> addRequests;
    vector<string> deleteRequests;
    vector<string> changePriceRequests;
    vector<string> cashoutRequests;

    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        if (pos == string::npos) continue;

        string type = line.substr(0, pos);
        string content = line.substr(pos + 1);

        if (type == "add") {
            addRequests.push_back(content);
        } else if (type == "delete") {
            deleteRequests.push_back(content);
        } else if (type == "change_price") {
            changePriceRequests.push_back(content);
        } else if (type == "cashout") {
            cashoutRequests.push_back(content);
        }
    }

    if (!addRequests.empty()) {
        cout << "\n[Add Product Requests]\n";
        for (const string& req : addRequests)
            cout << req << endl;
    }

    if (!deleteRequests.empty()) {
        cout << "\n[Delete Product Requests]\n";
        for (const string& req : deleteRequests)
            cout << req << endl;
    }

    if (!changePriceRequests.empty()) {
        cout << "\n[Change Price Requests]\n";
        for (const string& req : changePriceRequests)
            cout << req << endl;
    }

    if (!cashoutRequests.empty()) {
        cout << "\n[Cashout Requests]\n";
        for (const string& req : cashoutRequests)
            cout << req << endl;
    }

    if (addRequests.empty() && deleteRequests.empty() && changePriceRequests.empty() && cashoutRequests.empty()) {
        cout << "No requests found.\n";
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

int main() {
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
    return 0;
}