#include <vector>
#include <ctime>
#include "../../product_helpers.h"
#include "../../merchant/core/merchant_helpers.h"

void purchase(string email) {
    vector<string> merchantList;
    ifstream merchantInFile("merchantAccounts.txt");
    string line;

    cout << termcolor::bold << termcolor::blue;
    cout << "\n+------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "      Select a Merchant       "<< termcolor::blue <<"|\n";
    cout << "+------------------------------+\n";
    while (getline(merchantInFile, line)) {
        if (!line.empty()) {
            string merchantEmail, username, password;
            stringstream split(line);

            getline(split, merchantEmail, ',');
            getline(split, username, ',');
            getline(split, password);

            merchantList.push_back(merchantEmail);
            cout << "|  " << merchantList.size() << ". " << setw(25) << left << merchantEmail << termcolor::blue << "|" << endl;
        }
    }

    cout << "|  " << "3. " << setw(25) << left << termcolor::bright_cyan << "Back to Home" << termcolor::blue << "|" << endl;
    cout << "+------------------------------+\n";
    merchantInFile.close();

    if (merchantList.empty()) {
        cout << "No merchants available.\n";
        return;
    }

    int merchantChoice;
    cout << termcolor::bright_cyan << "Select number of merchant: ";
    cin >> merchantChoice;

    if (merchantChoice < 1 || merchantChoice > merchantList.size()) {
        if (merchantChoice == 3){
            cout << termcolor::red << "Returning to Home...\n";
        } else {
            cout << termcolor::red << "Invalid choice.\n"; 
        }
        clearSystem();
        return;
    }

    string selectedMerchant = merchantList[merchantChoice - 1];

    vector<Product> productList;
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
                productList.push_back(p);
            }
        }
    }
    productInFile.close();

    if (productList.empty()) {
        cout << "No products available for this merchant.\n";
        return;
    }

    cout << termcolor::bold << termcolor::blue;
    cout << "\n+------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "        " << selectedMerchant << " Products         "<< termcolor::blue <<"|\n";
    cout << "+------------------------------+\n";
    for (size_t i = 0; i < productList.size(); ++i) {
        cout << (i + 1) << ". " << productList[i].name << " | Price: " << productList[i].price << " tokens" << " | Stock(s) left: " << productList[i].quantity << endl;
    }
    cout << "+------------------------------+\n";

    int productChoice;
    cout << termcolor::bright_cyan << "Select number of product: ";
    cin >> productChoice;

    if (productChoice < 1 || productChoice > productList.size()) {
        cout << termcolor::red << "Invalid product selection.\n";
        clearSystem();
        return;
    }

    cout << "Selected: " << productList[productChoice - 1].name <<  " | Price: " << productList[productChoice - 1].price << " tokens" << endl;

    int productQty;
    cout << "Quantity: ";
    cin >> productQty;

    int totalAmount = productQty * productList[productChoice - 1].price;
    if (productQty > 0 && productQty <= productList[productChoice - 1].quantity){
        cout << "Total Amount: " << totalAmount << endl;
        cout << "Are you sure you want to purchase " << productQty << " " << productList[productChoice - 1].name << "? (y/n): ";
        char choice;
        cin >> choice;

        if (choice == 'y' || choice == 'Y'){
            vector<Student> studentBalance;
            Student s;

            ifstream studentInFile("studentBalance.txt");
            while (getline(studentInFile, line)) {
                if (!line.empty()) {
                    string strBalance;
                    stringstream split(line);
                    getline(split, s.email, ',');
                    getline(split, strBalance);
                    s.balance = stoi(strBalance);

                    if (s.email == email){
                        if (s.balance >= totalAmount){
                            s.balance -= totalAmount;

                            vector<MerchantAcc> merchantBalance;
                            bool found = false;

                            ifstream merchantInFile("merchantBalance.txt");
                            while (getline(merchantInFile, line)) {
                                if (!line.empty()) {
                                    MerchantAcc m;
                                    string strBalance;
                                    stringstream split(line);

                                    getline(split, m.email, ',');
                                    getline(split, strBalance);
                                    m.balance = stoi(strBalance);

                                    if (m.email == selectedMerchant){
                                        m.balance += totalAmount;
                                        found = true;
                                    }

                                    merchantBalance.push_back(m);
                                }
                            }
                            merchantInFile.close();

                            if (!found) {
                                MerchantAcc nm;
                                nm.email = selectedMerchant;
                                nm.balance = totalAmount;

                                merchantBalance.push_back(nm);
                            }

                            ofstream merchantOutFile("merchantBalance.txt");
                            for (const auto& m : merchantBalance) {
                                merchantOutFile << m.email << "," << m.balance << endl;
                            }
                            merchantOutFile.close ();

                            vector<Product> selectedProduct;
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

                                    if (p.merchant == selectedMerchant && p.name == productList[productChoice - 1].name) {
                                        p.quantity -= productQty;
                                    }

                                    selectedProduct.push_back(p);
                                }
                            }
                            productInFile.close();

                            ofstream productOutFile("productList.txt");
                            for (const auto& p : selectedProduct) {
                                productOutFile << p.merchant << "," << p.name << "," << p.price << "," << p.quantity << "," << p.desc << endl;
                            }
                            productOutFile.close ();

                            

                            cout << "Purchased successfully!\n";
                            clearSystem();
                        } else {
                            cout << termcolor::red << "You don't have enough tokens to purchase.\n";
                            clearSystem();
                        }
                    }
                    
                    studentBalance.push_back(s);
                }
            }
            studentInFile.close();

            ofstream studentOutFile("studentBalance.txt");
            for (const auto& s : studentBalance) {
                studentOutFile << s.email << "," << s.balance << endl;
            }
            studentOutFile.close();

            time_t now = time(0);
            string dt = ctime(&now);
            dt.pop_back();

            string currentStudentBalance;
            ifstream studentBalInFile("studentBalance.txt");
            while (getline(studentBalInFile, line)) {
                if (!line.empty()) {
                    string studentEmail, strBalance;
                    stringstream split(line);

                    getline(split, studentEmail, ',');
                    getline(split, strBalance);
                    
                    if (studentEmail == email){
                        currentStudentBalance = strBalance;
                        break;
                    }
                }
            }
            studentBalInFile.close();

            string currentMerchantBalance;
            ifstream merchantBalInFile("merchantBalance.txt");
            while (getline(merchantBalInFile, line)) {
                if (!line.empty()) {
                    string merchantEmail, strBalance;
                    stringstream split(line);

                    getline(split, merchantEmail, ',');
                    getline(split, strBalance);

                    if (merchantEmail == selectedMerchant){
                        currentMerchantBalance = strBalance;
                        break;
                    }
                }
            }
            merchantBalInFile.close();

            ofstream transactionOutFile("studentProductTransactions.txt", ios::app);
            transactionOutFile << email << "," << selectedMerchant << "," << productList[productChoice - 1].name << "," << totalAmount << "," << productQty << "," << currentStudentBalance << "," << currentMerchantBalance << "," << dt << endl;
            transactionOutFile.close();
        }
    }
}