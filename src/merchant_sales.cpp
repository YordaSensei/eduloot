#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void totalSales(string email) {
    vector<MerchantAcc> balance;
    string line;
    MerchantAcc m;
    bool found = false;
    int choice;
    do {
        ifstream inFile("merchantBalance.txt");
        while (getline(inFile, line)) {
            if (!line.empty()) {
                
                string strBalance;
                stringstream split(line);

                getline(split, m.email, ',');
                getline(split, strBalance);

                if (m.email == email){
                    m.balance = stoi(strBalance);
                    cout << "Total Sales: " << m.balance <<  " token(s)." << endl;
                    found = true;
                }
            }
        }
        inFile.close();

        if (!found) {
            cout << "Total Sales: 0 token(s).\n";
        }

        cout << "1. Back\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void merchantTransactions (string email){
    string line;
    cout << "\n----- Transactions -----\n";
    ifstream productInFile("studentProductTransactions.txt");

    while (getline(productInFile, line)) {
        if (!line.empty()) {
            string studentEmail, merchant, name, price, quantity, currentBal, merchantBal, time;
            stringstream split(line);

            getline(split, studentEmail, ',');
            getline(split, merchant, ',');
            getline(split, name, ',');
            getline(split, price, ',');
            getline(split, quantity, ',');
            getline(split, currentBal, ',');
            getline(split, merchantBal, ',');
            getline(split, time);

            if (merchant == email){
                cout << "Student " << studentEmail << " bought " << quantity << " " << name << "(s) for " << price << " token(s) at " << time << " | You currently have " << merchantBal << " token(s)." << endl; 
            }
        }
    }
    productInFile.close();
    cout << "\n-------------------------\n";
}

void sales(string email) {
    int choice;

    do {
        cout << "\n--- Sales ---\n";
        cout << "1. View Total Sales\n";
        cout << "2. Transactions\n";
        cout << "3. Back to Home";
        cout << "\n-------------\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice){
            case 1:
                totalSales(email);
                break;
            case 2:
                merchantTransactions(email);
                break;
        }
    } while (choice != 3);
}