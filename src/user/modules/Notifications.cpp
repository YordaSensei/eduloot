#include "Notifications.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "../../admin/includes/admin_helpers.h"

void Notifications::notifications() {
    int choice;

    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+--------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "          NOTIFICATIONS         " << termcolor::blue << "|\n";
        cout << "+--------------------------------+\n";
        cout << termcolor::reset;
        
        displayAdminMessages();
        
        displaySystemAlerts();
        
        cout << termcolor::bold << termcolor::blue;
        cout << "+--------------------------------+\n";
        cout << "| 1. " << termcolor::bright_cyan << "Back to Home " << termcolor::blue << setw(17) << "|\n";
        cout << "| 2. " << termcolor::bright_cyan << "Refresh" << termcolor::blue << setw(23) << "|\n";
        cout << "+--------------------------------+\n";
        cout << termcolor::reset;

        if (!getNumericInput(choice, "Choice: ", "Invalid input, select only numbers displayed in the menu.", 1, 2)) {
            continue;
        }
        
        if (choice == 2) {
            system("cls");
        }
    } while (choice != 1);
}

void Notifications::displayAdminMessages() {
    cout << termcolor::bold << termcolor::blue;
    cout << "\n+--------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "       MESSAGES FROM ADMIN      " << termcolor::blue << "|\n";
    cout << "+--------------------------------+\n";
    cout << termcolor::reset;
    
    ifstream msgFile(getUserType() + "AdminMessages.txt");
    string line;
    bool hasMessages = false;
    
    while (getline(msgFile, line)) {
        if (!line.empty()) {
            string recipient, message;
            stringstream ss(line);
            
            getline(ss, recipient, ',');
            getline(ss, message);
            
            if (recipient == getEmail() || recipient == getUserType()) {
                cout << " • " << message << "\n";
                hasMessages = true;
            }
        }
    }
    
    if (!hasMessages) {
        cout << " No messages from admin.\n";
    }
    
    msgFile.close();
    cout << termcolor::blue << "+--------------------------------+\n";
    cout << termcolor::reset;
}

void Notifications::displaySystemAlerts() {
    cout << termcolor::bold << termcolor::blue;
    cout << "\n+--------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "          SYSTEM ALERTS         " << termcolor::blue << "|\n";
    cout << "+--------------------------------+\n";
    cout << termcolor::reset;
    
    ifstream balanceFile(getUserType() + "Balance.txt");
    string line;
    bool hasAlerts = false;
    
    while (getline(balanceFile, line)) {
        if (!line.empty()) {
            string fileEmail, strBalance;
            stringstream ss(line);
            
            getline(ss, fileEmail, ',');
            getline(ss, strBalance);
            
            if (fileEmail == getEmail()) {
                int balance = stoi(strBalance);
                if (balance < 0) {
                    cout << termcolor::red << " ⚠ Your balance is negative (" << balance 
                         << " tokens). Please settle your debt.\n";
                    hasAlerts = true;
                }
            }
        }
    }
    balanceFile.close();
    
    ifstream alertsFile("systemAlerts.txt");
    while (getline(alertsFile, line)) {
        if (!line.empty()) {
            string recipient, alert;
            stringstream ss(line);
            
            getline(ss, recipient, ',');
            getline(ss, alert);
            
            if (recipient == getEmail() || recipient == "ALL") {
                cout << " ⚠ " << alert << "\n";
                hasAlerts = true;
            }
        }
    }
    alertsFile.close();
    
    if (!hasAlerts) {
        cout << " No system alerts.\n";
    }
    
    cout << termcolor::blue << "+--------------------------------+\n";
    cout << termcolor::reset;
}