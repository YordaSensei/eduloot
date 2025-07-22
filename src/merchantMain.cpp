#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "merchant_products.cpp"
#include "merchant_qr.cpp"
#include "merchant_request.cpp"
#include "merchant_sales.cpp"

using namespace std;

void merchantMain(string email) {
    int choice;

    do {
        cout << "\n--- Good day, " << email << "! ---\n";
        cout << "1. Products\n";
        cout << "2. Sales\n";
        cout << "3. Request To Admin\n";
        cout << "4. QR Code\n";
        cout << "5. Log Out\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                products(email);
                break;
            case 2:
                sales();
                break;
            case 3:
                requestAdmin(email); 
                break;
            case 4:
                break;
        }
    } while (choice != 5);

    cout << "Logging Out...";
}