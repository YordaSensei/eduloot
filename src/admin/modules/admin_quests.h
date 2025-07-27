#pragma once
#include "../includes/admin_includes.h"

using namespace std;

struct CompletedQuests {
    string email;
    string quest;
    int tokenAmount;
    string originalLine;
}; 

struct Quests {
    string name;
    int reward;
    int claimsLeft;
};

class questsModule {
    public:
        void questsTab();

    private:
        void viewQuests();
        void approveStudentQuests();
        void createQuest();
        void deleteQuest();
        void updateQuestClaims(const string& questName, int decrement);
        void updateStudentBalance(const string& email, int tokens);
};

void questsModule::viewQuests() {
    ifstream questFile("quests.txt");
    string line;

    if (!questFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-----------------------------+\n";
    cout << "|     " << termcolor::bright_yellow << " Available Quests" << termcolor::magenta << "       |\n";
    cout << "+-----------------------------+\n";
    cout << termcolor::reset;

    while (getline(questFile, line)) {
        cout << termcolor::yellow << "- " << line << termcolor::reset << endl;
    }

    cout << termcolor::magenta <<  "+-----------------------------+\n" << termcolor::reset;

    questFile.close();
}

void questsModule::approveStudentQuests() {
    ifstream accomplishedQuestsFile("studentAccomplishedQuests.txt");
    vector<CompletedQuests> quests;
    string line;

    while (getline(accomplishedQuestsFile, line)) {
        CompletedQuests q;
        string tokenStr;
        stringstream split(line);
        q.originalLine = line;

        getline(split, q.email, ',');
        getline(split, q.quest, ',');
        getline(split, tokenStr, ',');

        try {
            q.tokenAmount = stoi(tokenStr);
        } catch (...) {
            continue;
        }

        quests.push_back(q);
    }
    accomplishedQuestsFile.close();

    if (quests.empty()) {
        cout << termcolor::red << "(No pending quest requests)\n" << termcolor::reset;
        return;
    }

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+----------------------------------------------+\n";
    cout << "| " << termcolor::bright_yellow << "        Quests Completed by Students    " << termcolor::magenta << "     |\n";
    cout << "+----------------------------------------------+\n";
    cout << termcolor::reset;

    int displayIndex = 1;
    for (size_t i = 0; i < quests.size(); i++) {
        cout << termcolor::bright_yellow << displayIndex << ". " << termcolor::reset
            << quests[i].email << " | "
            << quests[i].quest << " | "
            << quests[i].tokenAmount << endl;
            displayIndex++;
    }

    cout << termcolor::magenta << "\n+----------------------------------------------+\n";
    
    int index = promptValidatedIndex("Enter request number to approve (0 to cancel): ", quests.size());
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << termcolor::reset;

    CompletedQuests selected = quests[index - 1];
    deleteLine("studentAccomplishedQuests.txt", selected.originalLine);

    updateStudentBalance(selected.email, selected.tokenAmount);
    updateQuestClaims(selected.quest, 1);

    ofstream approvedQuests ("admin/files/approvedQuests.txt", ios::app);
    approvedQuests << selected.originalLine << endl;
    approvedQuests.close();

    cout << termcolor::green << "\nQuest Approved and " << selected.tokenAmount
        << " tokens added to " << selected.email << "'s wallet.\n" << termcolor::reset;
    clearSystem(3000);
}

void questsModule::updateStudentBalance(const string &email, int tokenAmount) {
    vector<string> balanceLines;
    ifstream walletIn("studentBalance.txt");
    string walletLine;

    while (getline(walletIn, walletLine)) {
        stringstream ss(walletLine);
        string username, balanceStr;
        getline(ss, username, ',');
        getline(ss, balanceStr);

        if (username == email) {
            int balance = stoi(balanceStr) + tokenAmount;
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
}

void questsModule::updateQuestClaims (const string &questName, int decrement) {
    // Update claims
    ifstream questsIn("quests.txt");
    vector<string> updatedQuests;
    string questLine;

    while (getline(questsIn, questLine)) {
        stringstream ss(questLine);
        string name, tokenStr, claimsStr;

        getline(ss, name, ',');
        getline(ss, tokenStr, ',');
        getline(ss, claimsStr);

        if (name == questName) {
            int claims = stoi(claimsStr) - decrement;
            if (claims > 0) {
                string updatedLine = questName + "," + tokenStr + "," + to_string(claims);
            updatedQuests.push_back(updatedLine);
            } 
            
            if (claims == 0) continue;
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
}

void questsModule::createQuest() {
    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-----------------------------+\n";
    cout << "|        " << termcolor::bright_yellow << "CREATE QUEST     " << termcolor::magenta << "    |\n";
    cout << "+-----------------------------+\n";
    cout << termcolor::reset;
    cout << termcolor::red << "Press 0 to cancel\n" << termcolor::reset;

    string questName = promptNonEmptyInput("Quest: ");
    if (cancelInput(questName)) {
        return;
    }
    int tokenAmount = promptValidatedPrice("Token Reward: ");
    int studentLimit = promptValidatedQuantity("Maximum Claims: ");

    string quest = questName + "," + to_string(tokenAmount) + "," + to_string(studentLimit);

    ofstream questFile("quests.txt", ios::app);
    if (!questFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    questFile << quest << endl;
    questFile.close();
}

void questsModule::deleteQuest() {
    viewQuests();

    cout << termcolor::bold << termcolor::magenta;
    cout << "\n+-----------------------------+\n";
    cout << "|      " << termcolor::bright_yellow << " DELETE QUEST    " << termcolor::magenta << "      |\n";
    cout << "+-----------------------------+\n";
    cout << termcolor::reset;
    cout << termcolor::red << "Press 0 to cancel\n" << termcolor::reset;

    string quest = promptNonEmptyInput("Quest: ");
    if (cancelInput(quest)) {
        return;
    }
    int tokenAmount = promptValidatedPrice("Token Reward: ");
    int studentLimit = promptValidatedQuantity("Maximum Claims: ");

    string concat = quest + "," + to_string(tokenAmount) + "," + to_string(studentLimit);
    deleteLine("quests.txt", concat);
    clearSystem(2000);
}

void questsModule::questsTab() {
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
            case 1:viewQuests();break;
            case 2:approveStudentQuests(); break;
            case 3: createQuest(); break;
            case 4: deleteQuest(); break;
            case 5: 
                cout << termcolor::bright_red << "\nReturning to dashboard...\n" << termcolor::reset;
                clearSystem(1200);
                break;
            default:
                cout << termcolor::bright_red << "\nInvalid choice!\n" << termcolor::reset;
                continue;
        }
    } while (choice != 5);
}