void emergencyFunds(string email) {
    ofstream outFile("studentEmergencyFunds.txt", ios::app);
    string reason;
    int amount;

    cout << termcolor::bold << termcolor::blue;
    cout << "\n+------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "   Request Emergency Funds   "<< termcolor::blue <<"|\n";
    cout << "+------------------------------+\n";

    cout << termcolor::bright_cyan << "Reason: ";
    cin.ignore();
    getline(cin, reason);

    cout << "Enter Amount: ";
    cin >> amount;

    outFile << email << "," << reason << "," << amount << endl;

    outFile.close();
    cout << termcolor::red << amount << " token(s) has been requested to admin. Approval will take a while.\n";
    clearSystem(3000);
}