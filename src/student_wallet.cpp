string line;
#include "admin/admin_helpers.h"

void viewBalance(string email) {
    vector<Student> balance;
    Student s;
    bool found = false;
    int choice;
    do {
        ifstream inFile("studentBalance.txt");
        while (getline(inFile, line)) {
            if (!line.empty()) {
                
                string strBalance;
                stringstream split(line);

                getline(split, s.email, ',');
                getline(split, strBalance);

                if (s.email == email){
                    s.balance = stoi(strBalance);
                    cout << "Token Balance: " << s.balance << endl;
                    found = true;
                }
            }
        }
        inFile.close();

        if (!found) {
            cout << "Token Balance: 0\n";
        }

        cout << "1. Back\n";
        cout << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void purchaseTokens(string email) {
    int quantity;
    cout << "How many tokens would you like to purchase? (PHP 3.00 = 1 Token): ";
    cin >> quantity;

    char choice;
    float totalAmount = quantity * 3;
    cout << "Total amount is " << totalAmount << ".\n";
    cout << "Are you sure you want to purchase " << quantity << " amount of tokens? (y/n)\n";
    cout << "Choice: ";
    cin >> choice;

    bool found = false;
    int currentBalance = 0;

    if (choice == 'y' || choice == 'Y'){
        vector<Student> balance;

        ifstream inFile("studentBalance.txt");
        while (getline(inFile, line)) {
            if (!line.empty()) {
                Student s;
                string strBalance;
                stringstream split(line);

                getline(split, s.email, ',');
                getline(split, strBalance);
                s.balance = stoi(strBalance);

                if (s.email == email){
                    s.balance += quantity;
                    found = true;
                }

                balance.push_back(s);
            }
        }
        inFile.close();

        if (!found) {
            Student ns;
            ns.email = email;
            ns.balance = quantity;

            balance.push_back(ns);
        }

        ofstream outFile("studentBalance.txt");
        for (const auto& s : balance) {
            outFile << s.email << "," << s.balance << endl;
        }
        outFile.close ();

        updateTotalTokens(-quantity);
        updateTotalMoney(totalAmount);
        cout << quantity << " tokens purchased successfully.\n";
    }
}

void convertTokens(string email) {
    int quantity;
    cout << "How many tokens would you like to convert?\n";
    cout << "(PHP 3.00 = 1 Token) with a 5 percent fee.\n";
    cout << "Tokens to convert: ";
    cin >> quantity;

    char choice;
    float totalAmount = (quantity *3.0f) * 0.95f;
    cout << "Total amount is PHP " << totalAmount << " (fee included).\n";
    cout << "Are you sure you want to convert " << quantity << " tokens? (y/n)\n";
    cout << "Choice: ";
    cin >> choice;

    if (choice == 'y' || choice == 'Y'){
        vector<Student> balance;
        Student s;
        
        ifstream inFile("studentBalance.txt");
        while (getline(inFile, line)) {
            if (!line.empty()) {
                string strBalance;
                stringstream split(line);
                getline(split, s.email, ',');
                getline(split, strBalance);
                s.balance = stoi(strBalance);

                if (s.email == email){
                    if (s.balance >= quantity){
                        s.balance -= quantity;
                        updateTotalTokens(quantity);
                        updateTotalMoney(-totalAmount);
                        cout << quantity << " tokens converted successfully.\n";
                    } else {
                        cout << "You have don't have enough tokens to convert.\n";
                    }
                }

                balance.push_back(s);
            }
        }
        inFile.close();

        ofstream outFile("studentBalance.txt");
        for (const auto& s : balance) {
            outFile << s.email << "," << s.balance << endl;
        }
        outFile.close ();
    }
}

void wallet(string email) {
    int choice;

    do {
        cout << "\n--- Token Wallet ---\n";
        cout << "1. View Balance\n";
        cout << "2. Purchase Tokens\n";
        cout << "3. Convert to Cash\n";
        cout << "4. Back to Home\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                viewBalance(email);
                break;
            case 2:
                purchaseTokens(email);
                break;
            case 3:
                convertTokens(email);
                break;
        }
    } while (choice != 4);
}