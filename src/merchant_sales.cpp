#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void sales() {
    int choice;

    do {
        cout << "\n--- Sales ---\n";
        cout << "1. View Total Sales\n";
        cout << "2. Transactions\n";
        cout << "3. Back to Home\n";
    } while (choice != 3);
}