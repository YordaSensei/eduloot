void emergencyFunds(string email) {
    ofstream outFile("studentEmergencyFunds.txt", ios::app);
    string reason;
    int amount;

    cout << "Reason: ";
    cin.ignore();
    getline(cin, reason);

    cout << "Enter Amount: ";
    cin >> amount;

    outFile << email << "," << reason << "," << amount << endl;

    outFile.close();
    cout << amount << " token(s) has been requested to admin. Approval will take a while.\n";
}