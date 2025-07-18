#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <sstream>
#include <iomanip>

#include "admin_helpers.h"
#include "admin_structs.h"

using namespace std;

struct Products {
    string name;
    double price;
    int quantity;
    string desc;
    string shopName;
    string reqType;
};


void approveMerchantRequests() {
    int mainChoice, productChoice;
    string file, name, desc, line;
    int price, quantity, index;
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

                    vector<Products> productReq;
                    inFile.open("productReq.txt");
                            while (getline(inFile, line)) {
                                if (!line.empty()) {
                                    Products p;
                                    string priceStr, quantityStr;
                                    stringstream ss(line);

                                    getline(ss, p.shopName, ',');
                                    getline(ss, p.reqType, ',');
                                    getline(ss, p.name, ',');
                                    getline(ss, priceStr, ',');
                                    getline(ss, quantityStr, ',');
                                    getline(ss, p.desc);

                                    try {
                                        p.price = stod(priceStr);
                                        p.quantity =  stoi(quantityStr);
                                    } catch (...) {
                                        continue;
                                    }

                                    productReq.push_back(p);
                                }
                            }
                        inFile.close();

                        if (productReq.empty()) {
                            cout << "\n-- No product requests --\n";
                            break;
                        }
                    
                    inFile.close();

                    cout << "\n--- Pending Product Requests ---\n";
                            
                    switch (productChoice) {
                       case 1: {
                            cout << "\n--- Pending [Add] Product Requests ---\n";
                            for (size_t i = 0; i < productReq.size(); i++) {
                                cout << i + 1 << ". " << productReq[i].shopName << " | "
                                    << productReq[i].reqType << " | "
                                    << productReq[i].name << " | "
                                    << productReq[i].price << " | "
                                    << productReq[i].quantity << " | "
                                    << productReq[i].desc << endl;
                            }

                            cout << "\nEnter request number: ";
                            cin >> index;
                            cin.ignore();

                            if (index <= 0 || index > productReq.size()) break;

                            Products p = productReq[index - 1];

                            if (p.reqType != "add") {
                                cout << "Selected request is not an 'add' request.\n";
                                break;
                            }

                            ostringstream priceStream;
                            priceStream << fixed << setprecision(2) << p.price;
                            string priceStr = priceStream.str();

                            string targetLine = p.shopName + "," + p.reqType + "," + p.name + "," +
                                                priceStr + "," + to_string(p.quantity) + "," + p.desc;



                            if (deleteLine("productReq.txt", targetLine)) {
                                ofstream outFile("productList.txt", ios::app);
                                outFile << p.shopName << "," << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;
                                outFile.close();

                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << targetLine << endl;
                                approvedFile.close();

                                cout << "\nProduct approved and added to the product list.\n";
                            }
                            break;
                        }

                        case 2: {
                            cout << "\n--- Pending [Delete] Product Requests ---\n";
                            for (size_t i = 0; i < productReq.size(); i++) {
                                cout << i + 1 << ". " << productReq[i].shopName << " | "
                                    << productReq[i].reqType << " | "
                                    << productReq[i].name << " | "
                                    << productReq[i].price << " | "
                                    << productReq[i].quantity << " | "
                                    << productReq[i].desc << endl;
                            }

                            cout << "Enter request number: ";
                            cin >> index;
                            cin.ignore();

                            if (index <= 0 || index > productReq.size()) break;

                            Products p = productReq[index - 1];

                            if (p.reqType != "delete") {
                                cout << "Selected request is not a 'delete' request.\n";
                                break;
                            }

                            ostringstream priceStream;
                            priceStream << fixed << setprecision(2) << p.price;
                            string priceStr = priceStream.str();

                            string targetProduct = p.shopName + "," + p.name + "," + priceStr + "," + to_string(p.quantity) + "," + p.desc;
                            string targetRequest = p.shopName + "," + p.reqType + "," + p.name + "," + priceStr + "," + to_string(p.quantity) + "," + p.desc;


                            if (deleteLine("productList.txt", targetProduct) && deleteLine("productReq.txt", targetRequest)) {
                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << targetRequest << endl;
                                approvedFile.close();

                                cout << "\nProduct deleted successfully.\n";
                            }
                            break;
                        }

                       case 3: {
                            cout << "\n--- Pending 'Edit' Product Requests ---\n";
                            for (size_t i = 0; i < productReq.size(); i++) {
                                cout << i + 1 << ". " << productReq[i].shopName << " | "
                                    << productReq[i].reqType << " | "
                                    << productReq[i].name << " | "
                                    << productReq[i].price << " | "
                                    << productReq[i].quantity << " | "
                                    << productReq[i].desc << endl;
                            }

                            cout << "Enter request number: ";
                            cin >> index;
                            cin.ignore();

                            if (index <= 0 || index > productReq.size()) break;

                            Products p = productReq[index - 1];

                            if (p.reqType != "edit") {
                                cout << "Selected request is not an 'edit' request.\n";
                                break;
                            }

                            ostringstream oldPriceStream;
                            oldPriceStream << fixed << setprecision(2) << p.price;
                            string oldPriceStr = oldPriceStream.str();

                            string oldLine = p.shopName + "," + p.name + "," + oldPriceStr + "," + to_string(p.quantity) + "," + p.desc;
                            string requestLine = p.shopName + "," + p.reqType + "," + p.name + "," + oldPriceStr + "," + to_string(p.quantity) + "," + p.desc;

                            cout << "\n[New Product Info]\n";
                            string newName, newDesc;
                            double newPrice;
                            int newQty;

                            cout << "New Name: ";
                            getline(cin, newName);
                            cout << "New Price: ";
                            cin >> newPrice;
                            cin.ignore();
                            cout << "New Quantity: ";
                            cin >> newQty;
                            cin.ignore();
                            cout << "New Description: ";
                            getline(cin, newDesc);

                            ostringstream newPriceStream;
                            newPriceStream << fixed << setprecision(2) << newPrice;
                            string newPriceStr = newPriceStream.str();

                            string newLine = p.shopName + "," + newName + "," + newPriceStr + "," + to_string(newQty) + "," + newDesc;

                            if (editLine("productList.txt", oldLine, newLine) && deleteLine("productReq.txt", requestLine)) {
                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << "edit," + newLine << endl;
                                approvedFile.close();
                                cout << "\nProduct edited and request approved.\n";
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
                vector<Products> productReq;
                    inFile.open("productReq.txt");
                            while (getline(inFile, line)) {
                                if (!line.empty()) {
                                    Products p;
                                    string priceStr, quantityStr;
                                    stringstream ss(line);

                                    getline(ss, p.shopName, ',');
                                    getline(ss, p.reqType, ',');
                                    getline(ss, p.name, ',');
                                    getline(ss, priceStr, ',');
                                    getline(ss, quantityStr, ',');
                                    getline(ss, p.desc);

                                    try {
                                        p.price = stod(priceStr);
                                        p.quantity =  stoi(quantityStr);
                                    } catch (...) {
                                        continue;
                                    }

                                    productReq.push_back(p);
                                }
                            }
                        inFile.close();

                        if (productReq.empty()) {
                            cout << "\n-- No product requests --\n";
                            break;
                        }
                    
                    inFile.close();

                    cout << "\n--- Pending Product Requests ---\n";
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