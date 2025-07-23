void studentNotifications(string email) {
    string line;

    cout << "\n----- Quests Approved -----\n";
    ifstream questInFile("approvedQuests.txt");

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
    cout << "-------------------------\n";

    cout << "\n----- Emergency Funds Approved -----\n";
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
    cout << "-------------------------\n";
}