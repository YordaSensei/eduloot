#include "admin/admin_includes.h"

using namespace std;

struct completedQuests {
    string email;
    string quest;
    int tokenAmount;
    string originalLine;
}; 

void viewQuests() {
    ifstream inFile("quests.txt");
    string line;

    if (!inFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-----------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << " Available Quests" << termcolor::magenta << "       |\n";
    cout << "+-----------------------------+\n";
    cout << termcolor::reset;

    while (getline(inFile, line)) {
        cout << termcolor::yellow << "- " << line << termcolor::reset << endl;
    }

    cout << termcolor::magenta <<  "+-----------------------------+\n" << termcolor::reset;

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

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+----------------------------------------------+\n";
    cout << "| " << termcolor::bright_yellow << "        Quests Completed by Students    " << termcolor::magenta << "     |\n";
    cout << "+----------------------------------------------+\n";
    cout << termcolor::reset;

    int displayIndex = 1;
    bool hasRequests = false;
    for (size_t i = 0; i < quests.size(); i++) {
        hasRequests = true;
        cout << termcolor::bright_yellow << displayIndex << ". " << termcolor::reset
            << quests[i].email << " | "
            << quests[i].quest << " | "
            << quests[i].tokenAmount << endl;
            displayIndex++;
    }

    if (!hasRequests) {
        cout << termcolor::red << "(No pending quest requests)\n";
        return;
    }

    cout << termcolor::magenta << "\n+----------------------------------------------+\n";
    
    index = promptValidatedIndex("Enter request number to approve (0 to cancel): ", quests.size(), true);
    if (index == 0) {
        cout << termcolor::yellow << "Cancelled. Returning to menu...\n" << termcolor::reset;
        return;
    }


    cin.ignore();
    cout << termcolor::reset;

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

    // Update claims
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

    cout << termcolor::green << "\nQuest Approved and " << q.tokenAmount
        << " tokens added to " << q.email << "'s wallet.\n" << termcolor::reset;

    ofstream approvedQuests ("approvedQuests.txt", ios::app);
    approvedQuests << q.originalLine << endl;
    clearSystem();
}

void createQuest() {
    int tokenAmount, studentLimit;
    string quest;

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-----------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << "CREATE QUEST     " << termcolor::magenta << "       |\n";
    cout << "+-----------------------------+\n";
    cout << termcolor::reset;

    cout << termcolor::bright_yellow;
    cout << "Quest: ";
    getline(cin, quest);

    quest = promptNonEmptyInput("Quest: ");
    tokenAmount = promptValidatedPrice("Token Reward: ");
    studentLimit = promptValidatedQuantity("Maximum Claims: ");

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

    viewQuests();

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-----------------------------+\n";
    cout << "|      " << termcolor::bright_yellow << " DELETE QUEST    " << termcolor::magenta << "      |\n";
    cout << "+-----------------------------+\n";
    cout << termcolor::reset;

    quest = promptNonEmptyInput("Quest: ");
    tokenAmount = promptValidatedPrice("Token Reward: ");
    studentLimit = promptValidatedQuantity("Maximum Claims: ");

    string concat = quest + "," + to_string(tokenAmount) + "," + to_string(studentLimit);
    deleteLine(filename, concat);
    clearSystem();
}

void questsTab() {
    int choice;

    do {
        cout << termcolor::bold << termcolor::magenta;
        cout << "\n+-------------------------------+\n";
        cout << "|      " << termcolor::bright_yellow << "   QUESTS TAB            " << termcolor::magenta << "|\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. View Available Quests     |\n";
        cout << "|  2. Approve Student Quest     |\n";
        cout << "|  3. Create Quest              |\n";
        cout << "|  4. Delete Quest              |\n";
        cout << "|  5. Back                      |\n";
        cout << "+-------------------------------+\n";

        choice = promptChoice(1, 5, "choice: ");
        system("cls");

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
        }
    } while (choice != 5);
}