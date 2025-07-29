#include <vector>
#include <limits>

#include "../modules/merchant_products.h"
#include "../modules/merchant_request.cpp"
#include "../modules/merchant_sales.cpp"

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
        do {
            choice = promptChoice(1,4,"Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
        system("cls");

        switch(choice) {
            case 1:
                MerchantProducts products;
                products.products(email);
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