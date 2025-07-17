#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "admin_helpers.cpp"

using namespace std;

struct Account {
    string ciitEmail;       
    string username;
    string password;
};

struct Merchant {
    string shopname;      
    string username;
    string password;
};

void approveMerchantRequests() {
    int mainChoice, productChoice;
    string file, name, desc, line;
    int price, quantity;
    ifstream inFile;
    ofstream outFile;

    do {
        cout << "\n--- Select Request Type ---\n";
        cout << "-----------------------------\n";
        cout << "1. Products\n";
        cout << "2. Concerns\n";
        cout << "3. Cash Out\n";
        cout << "4. Back\n";
        cout << "------------------------------\n";
        cout << "Choice: ";
        cin >> mainChoice;
        cin.ignore();

        switch (mainChoice) {
            case 1: { // PRODUCTS
                do {
                    cout << "\n--- Product Requests ---\n";
                    cout << "-----------------------------\n";
                    cout << "1. Add Product\n";
                    cout << "2. Delete Product\n";
                    cout << "3. Edit Product\n";
                    cout << "4. Back\n";
                    cout << "------------------------------\n";
                    cout << "Choice: ";
                    cin >> productChoice;
                    cin.ignore();

                    cout << "\n--- Pending Product Requests ---\n";
                            inFile.open("productReq.txt");
                            while (getline(inFile, line)) {
                                if (line.find("add,") == 0) {
                                    cout << line << endl;
                                }
                            }
                            inFile.close();

                    switch (productChoice) {
                        case 1: { // ADD PRODUCT
                            cout << "\n--- Add Product ---\n";
                            cout << "Product Name: ";
                            getline(cin, name);
                            cout << "Price: ";
                            cin >> price;
                            cin.ignore();
                            cout << "Quantity: ";
                            cin >> quantity;
                            cin.ignore();
                            cout << "Description: ";
                            getline(cin, desc);

                            string target = "add," + name + "," + to_string(price) + "," + to_string(quantity) + "," + desc;

                            if (deleteLine("productReq.txt", target)) {
                                ofstream outFile("productList.txt", ios::app);
                                outFile << name << "," << to_string(price) << "," << to_string(quantity) << "," << desc << endl;
                                outFile.close();

                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << target << endl;
                                approvedFile.close();

                                cout << "\nProduct approved and added to the product list.\n";
                            } 
                            break;
                        }


                        case 2: { // DELETE PRODUCT
                            cout << "\n--- Delete Product ---\n";
                            cout << "Product Name: ";
                            getline(cin, name);
                            cout << "Price: ";
                            cin >> price;
                            cin.ignore();
                            cout << "Quantity: ";
                            cin >> quantity;
                            cin.ignore();
                            cout << "Description: ";
                            getline(cin, desc);

                            string target = name + "," + to_string(price) + "," + to_string(quantity) + "," + desc;

                            if (deleteLine("productList.txt", target)) {
                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << target << endl;
                                approvedFile.close();
                            }
                            break;
                        }

                        case 3: { // EDIT PRODUCT
                            cout << "\n--- Edit Product ---\n";
                            cout << "[Old Product Info]\n";
                            string oldName, oldDesc;
                            int oldPrice, oldQuantity;
                            cout << "Name: ";
                            getline(cin, oldName);
                            cout << "Price: ";
                            cin >> oldPrice;
                            cin.ignore();
                            cout << "Quantity: ";
                            cin >> oldQuantity;
                            cin.ignore();
                            cout << "Description: ";
                            getline(cin, oldDesc);

                            string oldLine = oldName + "," + to_string(oldPrice) + "," + to_string(oldQuantity) + "," + oldDesc;

                            cout << "\n[New Product Info]\n";
                            cout << "New Name: ";
                            getline(cin, name);
                            cout << "New Price: ";
                            cin >> price;
                            cin.ignore();
                            cout << "New Quantity: ";
                            cin >> quantity;
                            cin.ignore();
                            cout << "New Description: ";
                            getline(cin, desc);

                            string newLine = name + "," + to_string(price) + "," + to_string(quantity) + "," + desc;

                            if (editLine("productList.txt", oldLine, newLine)) {
                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << newLine << endl;
                                approvedFile.close();
                            }
                            break;
                        }

                        case 4:
                            break;

                        default:
                            cout << "\nERROR: Invalid product choice!\n";
                            break;
                    }
                } while (productChoice != 4);
                break;
            }

            case 2: { // CONCERNS
                string concernLine;
                inFile.open("concerns.txt");
                cout << "\n--- Pending Merchant Concerns ---\n";
                while (getline(inFile, concernLine)) {
                    cout << concernLine << endl;
                }
                inFile.close();

                cout << "\nEnter full concern line to approve:\n";
                getline(cin, concernLine);

                outFile.open("approvedReq.txt", ios::app);
                outFile << "concern," + concernLine << endl;
                outFile.close();

                ifstream inFile5("concerns.txt");
                ofstream tempFile("tempConcerns.txt");
                while (getline(inFile5, line)) {
                    if (line != concernLine) {
                        tempFile << line << endl;
                    }
                }
                inFile5.close();
                tempFile.close();
                remove("concerns.txt");
                rename("tempConcerns.txt", "concerns.txt");

                cout << "\nConcern approved.\n";
                break;
            }

            case 3: { // CASH OUT
                string cashoutLine;
                inFile.open("cashout.txt");
                cout << "\n--- Pending Cash Out Requests ---\n";
                while (getline(inFile, cashoutLine)) {
                    cout << cashoutLine << endl;
                }
                inFile.close();

                cout << "\nEnter full cash out line to approve:\n";
                getline(cin, cashoutLine);

                outFile.open("approvedReq.txt", ios::app);
                outFile << "cashout," + cashoutLine << endl;
                outFile.close();

                ifstream inFile6("cashout.txt");
                ofstream tempFile("tempCashout.txt");
                while (getline(inFile6, line)) {
                    if (line != cashoutLine) {
                        tempFile << line << endl;
                    }
                }
                inFile6.close();
                tempFile.close();
                remove("cashout.txt");
                rename("tempCashout.txt", "cashout.txt");

                cout << "\nCash out approved.\n";
                break;
            }

            case 4:
                break;

            default:
                cout << "\nERROR: Invalid main choice!\n";
                break;
        }

    } while (mainChoice != 4);
}


void merchantRequests() {
    int choice;

    do {
        cout << "\n--- Merchant Requests ---\n";
        cout << "---------------------------\n";
        cout << "1. View Requests\n";
        cout << "2. Back to dashboard\n";
        cout << "---------------------------\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                approveMerchantRequests();
                break;
            case 2:
                break;
            default:
                cout << "\nERROR: Invalid choice!\n";
                continue;
        }
    } while (choice != 2);
}