#include "admin/admin_includes.h"

using namespace std;

struct completedQuests {
    string email;
    string quest;
    int tokenAmount;
    string originalLine;
}; // ← Missing semicolon fixed

void viewQuests() {
    ifstream inFile("quests.txt");
    string line;

    if (!inFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    cout << "\n--- Available Quests ---\n";
    cout << "--------------------------\n";

    while (getline(inFile, line)) {
        cout << line << endl;
    }

    inFile.close();
}

void approveStudentQuests() {
    string readFile = "studentAccomplishedQuests.txt";
    string line;
    int index;

    vector<completedQuests> quests;

    ifstream inFile(readFile);
    while (getline(inFile, line)) {
        completedQuests q;
        string tokenStr;
        stringstream ss(line);
        q.originalLine = line;

        getline(ss, q.email, ',');
        getline(ss, q.quest, ',');
        getline(ss, tokenStr, ',');

        try {
            q.tokenAmount = stoi(tokenStr);
        } catch (...) {
            continue;
        }

        quests.push_back(q);
        }
        inFile.close();

        if (quests.empty()) {
            cout << "\nNo completed quests found.\n";
            return;
        }

        cout << "\n--- Quests Completed by Students ---\n";
        for (size_t i = 0; i < quests.size(); i++) {
            cout << (i + 1) << ". " << quests[i].email << " | "
                << quests[i].quest << " | "
                << quests[i].tokenAmount << endl;
        }

        cout << "\nEnter accomplished student quest to approve: ";
        cin >> index;
        cin.ignore();

        if (index <= 0 || index > quests.size()) {
            cout << "\nInvalid choice.\n";
            return;
        }

        completedQuests q = quests[index - 1];
        deleteLine(readFile, q.originalLine);

        vector<string> balanceLines;
        ifstream walletIn("studentBalance.txt");
        string walletLine;

        while (getline(walletIn, walletLine)) {
            stringstream ss(walletLine);
            string username, balanceStr;
            getline(ss, username, ',');
            getline(ss, balanceStr);

            if (username == q.email) {
                int balance = stoi(balanceStr);
                balance += q.tokenAmount;
                balanceLines.push_back(username + "," + to_string(balance));
            } else {
                balanceLines.push_back(walletLine);
            }
        }
        walletIn.close();

        ofstream walletOut("studentBalance.txt");
        for (const string& line : balanceLines) {
            walletOut << line << endl;
        }
        walletOut.close();

        //update claims
        ifstream questsIn("quests.txt");
        vector<string> updatedQuests;
        string questLine;

        while (getline(questsIn, questLine)) {
            stringstream ss(questLine);
            string questName, tokenStr, claimsStr;

            getline(ss, questName, ',');
            getline(ss, tokenStr, ',');
            getline(ss, claimsStr);

            if (questName == q.quest) {
                int claims = stoi(claimsStr);
                if (claims > 0) claims--;
                if (claims == 0) continue;

                string updatedLine = questName + "," + tokenStr + "," + to_string(claims);
                updatedQuests.push_back(updatedLine);
            } else {
                updatedQuests.push_back(questLine);
            }
        }

        questsIn.close();

        ofstream questsOut("quests.txt");
        for (const string& line : updatedQuests) {
            questsOut << line << endl;
        }
        questsOut.close();

        cout << "\nQuest Approved and " << q.tokenAmount
            << " tokens added to " << q.email << "'s wallet.\n";
}

void createQuest() {
    int tokenAmount, studentLimit;
    string quest;

    cout << "\n--- Create Quests ---\n";
    cout << "-----------------------\n";
    cout << "Quest: ";
    getline(cin, quest);
    cout << "Token Reward: ";
    cin >> tokenAmount;
    cout << "Maximum Claims: ";
    cin >> studentLimit;
    cin.ignore();

    string concat = quest + "," + to_string(tokenAmount) + "," + to_string(studentLimit);

    ofstream outFile("quests.txt", ios::app);
    if (!outFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    outFile << concat << endl;
    outFile.close();
}

void deleteQuest() {
    string quest;
    int tokenAmount, studentLimit;
    string filename = "quests.txt";

    cout << "\n--- Delete Quest ---\n";
    cout << "----------------------\n";
    cout << "Enter the quest: ";
    getline(cin, quest);
    cout << "Enter Token Amount: ";
    cin >> tokenAmount;
    cout << "Enter Maximum Claims: ";
    cin >> studentLimit;
    cin.ignore();

    string concat = quest + "," + to_string(tokenAmount) + "," + to_string(studentLimit);
    deleteLine(filename, concat);
}

void questsTab() {
    int choice;

    do {
        cout << "\n--- Quests Tab ---\n";
        cout << "--------------------\n";
        cout << "1. View Available Quests\n";
        cout << "2. Approve Student Quest\n";
        cout << "3. Create Quest\n";
        cout << "4. Delete Quest\n";
        cout << "5. Back\n";
        cout << "--------------------\n";
        cout << "Choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                viewQuests();
                break;
            case 2:
                approveStudentQuests();
                break;
            case 3:
                createQuest();
                break;
            case 4:
                deleteQuest();
                break;
            case 5:
                break;
            default:
                cout << "\nERROR: Invalid choice!\n";
        }
    } while (choice != 5);
}
