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
                    cout << termcolor::bold << termcolor::yellow;
                    cout << "\n+------------------------------+\n";
                    cout << "|" << termcolor::bright_white << "  Total Sales: " <<  m.balance << setw(12) << left << " token(s)." << termcolor::yellow << "|";
                    cout << "\n+------------------------------+\n";
                    found = true;
                }
            }
        }
        inFile.close();

        if (!found) {
            cout << termcolor::bold << termcolor::yellow;
            cout << "\n+------------------------------+\n";
            cout << "|" << termcolor::bright_white << setw(30) << left << "  Total Sales: 0 token(s)" << termcolor::yellow << "|";
            cout << "\n+------------------------------+\n";
        }

        cout << "1. Back\n";
        cout << termcolor::bright_white << "Choice: ";
        cin >> choice;
    } while (choice != 1);
}

void merchantTransactions (string email){
    string line;
    int choice;

    do {
        cout << termcolor::bold << termcolor::yellow;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_white << "       Transactions         " << termcolor::yellow << "|\n";
        cout << "+------------------------------+\n";
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
        cout << "+------------------------------+\n";
        cout << "1. Back\n";
        cout << termcolor::bright_white << "Choice: ";
        cin >> choice;

        switch (choice){
            case 1:
                system("cls");
                break;
            default:
                cout << termcolor::red << "Invalid choice.";
                clearSystem();
                break;
        }
    } while (choice != 1);
}

void sales(string email) {
    int choice;

    do {
        cout << termcolor::bold << termcolor::yellow;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_white << "           Sales            " << termcolor::yellow << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. View Total Sales         |\n";
        cout << "|  2. Transactions             |\n";
        cout << "|  3. Back to Home             |\n";
        cout << "+------------------------------+\n";
        cout << termcolor::bright_white << "Choice: ";
        cin >> choice;

        switch (choice){
            case 1:
                system("cls");
                totalSales(email);
                break;
            case 2:
                system("cls");
                merchantTransactions(email);               
                break;
            case 3: 
                cout << termcolor::red << "Returning to home...";    
                clearSystem();          
                break;
            default:
                cout << termcolor::red << "Invalid choice.";               
                clearSystem();
                break;
        }
    } while (choice != 3);
}