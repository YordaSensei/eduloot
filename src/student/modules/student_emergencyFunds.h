#pragma once

class emergencyFunds {
    public:
        void requestFunds(string email);
};

void emergencyFunds::requestFunds(string email) {
    ofstream outFile("studentEmergencyFunds.txt", ios::app);

    cout << termcolor::bold << termcolor::blue;
    cout << "\n+------------------------------+\n";
    cout << "|" << termcolor::bright_cyan << "    Request Emergency Funds   "<< termcolor::blue <<"|\n";
    cout << "+------------------------------+\n";

    int amount = promptValidatedQuantity("Enter Amount (0 to cancel): ");
    if (amount == 0) {
        cout << termcolor::red << "\nCancelled. Returning to menu...\n" << termcolor::reset;
        clearSystem();
        return;
    }

    string reason = promptNonEmptyInput("Reason: ");

    outFile << email << "," << reason << "," << amount << endl;

    outFile.close();
    cout << termcolor::red << amount << " token(s) has been requested to admin. Approval will take a while.\n";
    clearSystem(3000);
}