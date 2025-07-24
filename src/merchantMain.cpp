#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "merchant_products.cpp"
#include "merchant_request.cpp"
#include "merchant_sales.cpp"

using namespace std;

void merchantMain(string email) {
    int choice;

    do {
        cout << termcolor::bold << termcolor::yellow;
        cout << "\n+------------------------------+\n";
        cout << "|  " << termcolor::bright_white << "   Good day, Merchant!      " << termcolor::yellow << "|\n";
        cout << "+------------------------------+\n";
        cout << "|  1. Products                 |\n";
        cout << "|  2. Sales                    |\n";
        cout << "|  3. Request To Admin         |\n";
        cout << "|  4. Log Out                  |\n";
        cout << "+------------------------------+\n";
        cout << termcolor::bright_white << "Choice: ";
        cin >> choice;
        system("cls");

        switch(choice) {
            case 1:
                products(email);
                break;
            case 2:
                sales(email);
                break;
            case 3:
                requestAdmin(email); 
                break;
            case 4:
                cout << termcolor::red << "Logging Out...";
                clearSystem();
        }
    } while (choice != 4);
    cout << termcolor::reset;
}