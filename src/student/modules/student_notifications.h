#pragma once

class studentNotifications {
    public:
        void notifications(string email);
};

void studentNotifications::notifications(string email) {
    string line;
    int choice;

    do {
        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "       Quests Approved        "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n" << endl;
        ifstream questInFile("../../admin/files/approvedQuests.txt");  

        while (getline(questInFile, line)) {
            if (!line.empty()) {
                string studentEmail, quest, reward, claims;
                stringstream ss(line);

                getline(ss, studentEmail, ',');
                getline(ss, quest, ',');
                getline(ss, reward, ',');
                getline(ss, claims);
                
                if (studentEmail == email) {
                    cout << "Quest: " << quest << " has been approved. " << reward << " token(s) added to balance.\n";
                }
            }
        }
        questInFile.close();
        cout << "\n+------------------------------+\n";

        cout << termcolor::bold << termcolor::blue;
        cout << "\n+------------------------------+\n";
        cout << "|" << termcolor::bright_cyan << "   Emergency Funds Approved   "<< termcolor::blue <<"|\n";
        cout << "+------------------------------+\n" << endl;
        ifstream emergencyFundsInFile("studentApprovedReqs.txt");

        while (getline(emergencyFundsInFile, line)) {
            if (!line.empty()) {
                string studentEmail, reason, amount;
                stringstream ss(line);

                getline(ss, studentEmail, ',');
                getline(ss, reason, ',');
                getline(ss, amount, ',');

                if (studentEmail == email) {
                    cout << "Your request for emergency funds has been approved. " << amount << " token(s) added to balance.\n";
                }
            }
        }
        emergencyFundsInFile.close();
        cout << "\n+------------------------------+\n";

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