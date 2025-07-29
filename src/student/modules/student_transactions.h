#pragma once

class studentTransactions {
    public:
        void transactions(string email);
};

void studentTransactions::transactions(string email) {
    string line;
    int choice;

    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "      Token Transactions      "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n" << endl;
        ifstream tokenInFile("studentTokenTransactions.txt");

        while (getline(tokenInFile, line)) {
            if (!line.empty()) {
                string studentEmail, type, amount, currentBal, time;
                stringstream split(line);

                getline(split, studentEmail, ',');
                getline(split, type, ',');
                getline(split, amount, ',');
                getline(split, currentBal, ',');
                getline(split, time);

                if (studentEmail == email) {
                    cout << type << " " << amount << " token(s) at " << time 
                        << " | You currently have " << currentBal << " tokens.\n";
                }
            }
        }
        tokenInFile.close();
        cout << "\n+------------------------------+\n" << endl;

        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "     Product Transactions     "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n" << endl;
        ifstream productInFile("studentProductTransactions.txt");

        while (getline(productInFile, line)) {
            if (!line.empty()) {
                string studentEmail, merchant, name, price, quantity, studentBal, merchantBal, time;
                stringstream split(line);

                getline(split, studentEmail, ',');
                getline(split, merchant, ',');
                getline(split, name, ',');
                getline(split, price, ',');
                getline(split, quantity, ',');
                getline(split, studentBal, ',');
                getline(split, merchantBal, ',');
                getline(split, time);

                if (studentEmail == email) {
                    cout << "You bought " << quantity << " " << name << "(s) from " << merchant
                    << " for " << price << " token(s) at " << time << " | You currently have " << studentBal << " token(s)." << endl;
                }
            }
        }
        productInFile.close();
        cout << "\n+------------------------------+" << endl;

        cout << "1. " << termcolor::bright_cyan << "Back to Home\n";
        do {
            choice = promptChoice(1,1,"Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);
    } while (choice != 1);

    cout << termcolor::red << "Returning to Home...\n";
    clearSystem();
}