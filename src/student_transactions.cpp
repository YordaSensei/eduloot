void studentTransactions(string email) {
    string line;

    cout << "\n----- Token Transactions -----\n";
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
    cout << "-------------------------\n";

    cout << "\n----- Product Transactions -----\n";
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
    cout << "-------------------------\n";
}