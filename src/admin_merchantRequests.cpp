#include "admin/admin_includes.h"

using namespace std;

struct Products {
    string shopName;
    string reqType;
    string name;
    double price;
    int quantity;
    string desc;
    string originalLine;
};


void merchantRequests() {
    int mainChoice, productChoice;
    string file, name, desc, line;
    int price, quantity, index;
    ifstream inFile;
    ofstream outFile;

    do {
        cout << termcolor::bold << termcolor::magenta;
            cout << "\n+-------------------------------+\n";
            cout << "|   " << termcolor::bright_yellow << "    MERCHANT REQUESTS       " << termcolor::magenta << "|\n";
            cout << "+-------------------------------+\n";
            cout << "|  1. Products                  |\n";
            cout << "|  2. Concerns                  |\n";
            cout << "|  3. Cash Out                  |\n";
            cout << "|  4. Back                      |\n";
            cout << "+-------------------------------+\n";

            while (true) {
                cout << termcolor::bright_yellow << "Choice: ";
                if (cin >> mainChoice && mainChoice >= 1 && mainChoice <= 5) break;
                cout << termcolor::red << "Invalid choice. Please enter 1-4.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            system("cls");

        switch (mainChoice) {
            case 1: { // PRODUCTS
                do {
                    cout << termcolor::bold << termcolor::magenta;
                    cout << "\n+-------------------------------+\n";
                    cout << "|   " << termcolor::bright_yellow << "     PRODUCT REQUESTS       " << termcolor::magenta << "|\n";
                    cout << "+-------------------------------+\n";
                    cout << "|  1. Add Product               |\n";
                    cout << "|  2. Delete Product            |\n";
                    cout << "|  3. Edit Product              |\n";
                    cout << "|  4. Back                      |\n";
                    cout << "+-------------------------------+\n";

                    while (true) {
                        cout << termcolor::bright_yellow << "Choice: ";
                        cin >> productChoice;

                        if (cin.fail() || productChoice < 1 || productChoice > 4) {
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                            cout << termcolor::red << "Invalid choice. Try again...\n" << termcolor::reset;
                        } else {
                            cin.ignore(); 
                            break; 
                        }
                    }

                    system("cls");

                    vector<Products> addEditReqs;
                    vector<Products> deleteReqs;
                    ifstream inFile("productReq.txt");
                    
                    while (getline(inFile, line)) {
                        if (!line.empty()) {
                            string priceStr, quantityStr;
                            Products p;
                            p.originalLine = line;
                            stringstream ss(line);

                            getline(ss, p.shopName, ',');
                            getline(ss, p.reqType, ',');
                            getline(ss, p.name, ',');

                            if (p.reqType == "delete") {
                                getline(ss, p.desc);
                                p.price = 0.0;
                                p.quantity = 0;
                                deleteReqs.push_back(p);
                            } else {
                                getline(ss, priceStr, ',');
                                getline(ss, quantityStr, ',');
                                getline(ss, p.desc);

                                try {
                                    p.price = stod(priceStr);
                                    p.quantity = stoi(quantityStr);
                                } catch (...) {
                                    continue; 
                                }

                                addEditReqs.push_back(p);
                            }
                        }
                    }
                    inFile.close();
                            
                    switch (productChoice) {
                       case 1: {
                            cout << termcolor::bold << termcolor::magenta;
                            cout << "\n+----------------------------------------------+\n";
                            cout << "| " << termcolor::bright_yellow << "     Pending [Add] Product Requests     " << termcolor::magenta << "|\n";
                            cout << "+----------------------------------------------+\n";

                            bool hasAddRequests = false;
                            for (size_t i = 0; i < addEditReqs.size(); i++) {
                                if (addEditReqs[i].reqType == "add") {
                                    hasAddRequests = true;
                                    cout << termcolor::bright_white << i + 1 << ". "
                                        << termcolor::bright_yellow << addEditReqs[i].shopName << " | "
                                        << termcolor::cyan << addEditReqs[i].reqType << " | "
                                        << termcolor::bright_yellow << addEditReqs[i].name << " | "
                                        << "₱" << fixed << setprecision(2) << addEditReqs[i].price << " | "
                                        << addEditReqs[i].quantity << " pcs | "
                                        << termcolor::bright_yellow << addEditReqs[i].desc << endl;
                                }
                            }

                            if (!hasAddRequests) {
                                cout << termcolor::red << "(No pending add product requests)\n";
                            }

                            cout << termcolor::reset;

                            while (true) {
                                cout << termcolor::bright_yellow << "Enter request number to approve: ";
                                if (cin >> index && index > 0 && index <= (int)addEditReqs.size()) break;
                                cout << termcolor::red << "Invalid input. Please enter a valid index.\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }

                            if (index <= 0 || index > addEditReqs.size()) break;

                            Products p = addEditReqs[index - 1];

                            if (p.reqType != "add") {
                                cout << "Selected request is not an 'add' request.\n";
                                break;
                            }

                            ostringstream priceStream;
                            priceStream << fixed << setprecision(2) << p.price;
                            string priceStr = priceStream.str();

                            if (deleteLine("productReq.txt", p.originalLine)) {
                                ofstream outFile("productList.txt", ios::app);
                                outFile << p.shopName << "," << p.name << "," << priceStr << "," << p.quantity << "," << p.desc << endl;

                                outFile.close();

                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << p.originalLine << endl;
                                approvedFile.close();

                                cout << "\nProduct approved and added to the product list.\n";
                                clearSystem();
                            }
                            break;
                        }

                        case 2: {
                            cout << termcolor::bold << termcolor::magenta;
                            cout << "\n+----------------------------------------------+\n";
                            cout << "| " << termcolor::bright_yellow << "   Pending [Delete] Product Requests    " << termcolor::magenta << "|\n";
                            cout << "+----------------------------------------------+\n";

                            bool hasDeleteRequests = false;
                            for (size_t i = 0; i < deleteReqs.size(); i++) {
                                hasDeleteRequests = true;
                                cout << termcolor::bright_white << i + 1 << ". "
                                    << termcolor::bright_yellow << deleteReqs[i].shopName << " | "
                                    << termcolor::cyan << deleteReqs[i].reqType << " | "
                                    << termcolor::bright_yellow << deleteReqs[i].name << " | "
                                    << termcolor::white << deleteReqs[i].desc << endl;
                            }

                            if (!hasDeleteRequests) {
                                cout << termcolor::red << "(No pending delete product requests)\n";
                            }

                            cout << termcolor::reset;

                            while (true) {
                                cout << termcolor::bright_yellow << "Enter request number to approve: ";
                                if (cin >> index && index > 0 && index <= (int)deleteReqs.size()) break;
                                cout << termcolor::red << "Invalid input. Please enter a valid index.\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }


                            if (index <= 0 || index > deleteReqs.size()) break;

                            Products p = deleteReqs[index - 1]; 

                            if (p.reqType != "delete") {
                                cout << "Selected request is not a 'delete' request.\n";
                                break;
                            }

                            string targetProduct;
                            ifstream listFile("productList.txt");
                            
                            while (getline(listFile, line)) {
                                stringstream ss(line);
                                string shop, name;
                                getline(ss, shop, ',');
                                getline(ss, name, ',');

                                if (shop == p.shopName && name == p.name) {
                                    targetProduct = line;
                                    break;
                                }
                            }
                            listFile.close();

                            if (targetProduct.empty()) {
                                cout << "Matching product not found in productList.txt.\n";
                                break;
                            }

                            if (deleteLine("productList.txt", targetProduct) && deleteLine("productReq.txt", p.originalLine)) {
                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << p.originalLine << endl;
                                approvedFile.close();

                                cout << "\nProduct deleted successfully.\n";
                                clearSystem();
                            }
                            break;
                        }

                       case 3: {
                            cout << termcolor::bold << termcolor::magenta;
                            cout << "\n+----------------------------------------------+\n";
                            cout << "| " << termcolor::bright_yellow << "       Pending [Edit] Product Requests       " << termcolor::magenta << "|\n";
                            cout << "+----------------------------------------------+\n";

                            int displayIndex = 1;
                            bool hasEditRequests = false;

                            for (size_t i = 0; i < addEditReqs.size(); i++) {
                                if (addEditReqs[i].reqType == "edit") {
                                    hasEditRequests = true;
                                    cout << termcolor::bright_white << displayIndex << ". "
                                        << termcolor::bright_yellow << addEditReqs[i].shopName << " | "
                                        << termcolor::cyan << addEditReqs[i].reqType << " | "
                                        << termcolor::bright_yellow << addEditReqs[i].name << " | "
                                        << "₱" << fixed << setprecision(2) << addEditReqs[i].price << " | "
                                        << addEditReqs[i].quantity << " pcs | "
                                        << termcolor::white << addEditReqs[i].desc << endl;
                                    displayIndex++;
                                }
                            }

                            if (!hasEditRequests) {
                                cout << termcolor::red << "(No pending edit product requests)\n";
                            }

                            cout << termcolor::reset;

                            while (true) {
                                cout << termcolor::bright_yellow << "Enter request number to approve: ";
                                if (cin >> index && index > 0 && index <= (int)addEditReqs.size()) break;
                                cout << termcolor::red << "Invalid input. Please enter a valid index.\n";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }

                            Products p = addEditReqs[index - 1];

                            if (p.reqType != "edit") {
                                cout << "Selected request is not an 'edit' request.\n";
                                break;
                            }

                            ostringstream oldPriceStream;
                            oldPriceStream << fixed << setprecision(2) << p.price;
                            string oldPriceStr = oldPriceStream.str();

                            string oldLine = p.shopName + "," + p.name + "," + oldPriceStr + "," + to_string(p.quantity) + "," + p.desc;

                            cout << termcolor::bold << termcolor::magenta;
                            cout << "\n+-------------------------+\n";
                            cout << "| " << termcolor::bright_yellow << "   New Product Info    " << termcolor::magenta << "|\n";
                            cout << "+-------------------------+\n";
                            cout << termcolor::reset;

                            string newName, newDesc;
                            double newPrice;
                            int newQty;

                            cout << termcolor::bright_yellow << "New Name: ";
                            getline(cin, newName);

                            while (true) {
                                cout << "New Price: ";
                                cin >> newPrice;

                                if (cin.fail() || newPrice < 0) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << termcolor::red << "Invalid price. Please enter a positive number.\n" << termcolor::reset;
                                } else {
                                    cin.ignore();
                                    break;
                                }
                            }

                            while (true) {
                                cout << "New Quantity: ";
                                cin >> newQty;

                                if (cin.fail() || newQty < 0) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << termcolor::red << "Invalid quantity. Please enter a non-negative integer.\n" << termcolor::reset;
                                } else {
                                    cin.ignore();
                                    break;
                                }
                            }

                            cout << "New Description: ";
                            getline(cin, newDesc);

                            cout << termcolor::reset;

                            ostringstream newPriceStream;
                            newPriceStream << fixed << setprecision(2) << newPrice;
                            string newPriceStr = newPriceStream.str();

                            string newLine = p.shopName + "," + newName + "," + newPriceStr + "," + to_string(newQty) + "," + newDesc;

                            if (editLine("productList.txt", oldLine, newLine) && deleteLine("productReq.txt", p.originalLine)) {
                                ofstream approvedFile("approvedReq.txt", ios::app);
                                approvedFile << "edit," + newLine << endl;
                                approvedFile.close();
                                cout << "\nProduct edited and request approved.\n";
                                clearSystem();
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
                vector<string> concerns;
                string line;
                int index;

                ifstream inFile("concerns.txt");
                while (getline(inFile, line)) {
                    concerns.push_back(line);
                }
                inFile.close();

                cout << termcolor::bold << termcolor::magenta;
                cout << "\n+------------------------------------+\n";
                cout << "| " << termcolor::bright_yellow << "   Pending Merchant Concerns   " << termcolor::magenta << "|\n";
                cout << "+------------------------------------+\n";
                cout << termcolor::reset;

                int displayedIndex = 1;
                for (size_t i = 0; i < concerns.size(); i++) {
                    cout << termcolor::bright_white << displayedIndex << ". " 
                        << termcolor::bright_yellow << concerns[i] << endl;
                    displayedIndex++;
                }

                while (true) {
                    cout << termcolor::bright_yellow << "Enter request number to approve: ";
                    if (cin >> index && index > 0 && index <= (int)concerns.size()) break;
                    cout << termcolor::red << "Invalid input. Please enter a valid index.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (index <= 0 || index > concerns.size()) {
                    cout << termcolor::red << "\nInvalid choice.\n" << termcolor::reset;
                    break;
                }

                string concernLine = concerns[index - 1];

                deleteLine("concerns.txt", concernLine);

                ofstream outFile("approvedReq.txt", ios::app);
                outFile << "concern," + concernLine << endl;
                outFile.close();

                cout << termcolor::green << "\nConcern approved.\n" << termcolor::reset;
                clearSystem();
                break;

            }

            case 3: { // CASH OUT
                const float tokenRate = 3.00, fee = 0.05;
                struct cashoutReq {
                    string shopName;
                    float tokenAmount;
                    string originalLine;
                };

                vector<cashoutReq> cashout;
                string line;
                int index;

                ifstream inFile("cashout.txt");
                while (getline(inFile, line)) {
                    cashoutReq c;
                    c.originalLine = line; 
                    string tokenStr;
                    stringstream ss(line);

                    getline(ss, c.shopName, ',');
                    getline(ss, tokenStr);

                    try {
                        c.tokenAmount = stof(tokenStr);
                    } catch (...) {
                        continue;
                    }

                    cashout.push_back(c);
                }
                inFile.close();

                cout << termcolor::bold << termcolor::magenta;
                cout << "\n+------------------------------------+\n";
                cout << "| " << termcolor::bright_yellow << "       Pending Merchant Cash Out       " << termcolor::magenta << "|\n";
                cout << "+------------------------------------+\n";
                cout << termcolor::reset;

                int displayedIndex = 1;
                for (size_t i = 0; i < cashout.size(); i++) {
                    cout << termcolor::bright_yellow << displayedIndex << ". "
                        << termcolor::bright_yellow << cashout[i].shopName << " | "
                        << cashout[i].tokenAmount << endl;
                    displayedIndex++;
                }

                while (true) {
                    cout << termcolor::bright_yellow << "Select cash out number: ";
                    if (cin >> index && index > 0 && index <= (int)cashout.size()) break;
                    cout << termcolor::red << "Invalid input. Please enter a valid index.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }

                if (index <= 0 || index > cashout.size()) {
                    cout << termcolor::red << "\nInvalid choice.\n" << termcolor::reset;
                    break;
                }

                cashoutReq selected = cashout[index - 1]; 

                deleteLine("cashout.txt", selected.originalLine); 

                ofstream outFile("approvedReq.txt", ios::app);
                outFile << "cashout," << selected.originalLine << endl; 
                outFile.close();

                float total = selected.tokenAmount * tokenRate;
                float moneyAfterFee = total - (total * fee);

                updateTotalTokens(selected.tokenAmount); 
                updateTotalMoney(-moneyAfterFee);

                vector<string> balanceLines;
                ifstream walletIn("merchantBalance.txt");
                string walletLine;
                bool found = false;

                while (getline(walletIn, walletLine)) {
                    stringstream ss(walletLine);
                    string shopName, balanceStr;
                    getline(ss, shopName, ',');
                    getline(ss, balanceStr);

                    if (shopName == selected.shopName) {
                        int balance = stoi(balanceStr);

                        if (balance < selected.tokenAmount) {
                            cout << termcolor::red << "ERROR: Insufficient balance.\n" << termcolor::reset;
                            walletIn.close();
                            return;
                        }

                        balance -= selected.tokenAmount;
                        balanceLines.push_back(shopName + "," + to_string(balance));
                        found = true;
                    } else {
                        balanceLines.push_back(walletLine);
                    }
                }
                walletIn.close();

                if (!found) {
                    balanceLines.push_back(selected.shopName + "," + to_string(selected.tokenAmount));
                }

                ofstream walletOut("merchantBalance.txt");
                for (const string& line : balanceLines) {
                    walletOut << line << endl;
                }
                walletOut.close();

                cout << termcolor::green << "\nTokens Successfully Cashed Out!" << endl;
                cout << "P" << moneyAfterFee << " transferred\n" << termcolor::reset;

                clearSystem();
                break;
            }

            case 4:
                break;

            default:
                cout << termcolor::bright_red << "\nERROR: Invalid main choice!\n" << termcolor::reset;
                break;
        }

    } while (mainChoice != 4);
}

