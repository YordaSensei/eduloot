#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

#include "admin_helpers.cpp"

using namespace std;

void viewQuests () {
    ifstream inFile ("quests.txt");
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

void approveStudentQuests () {
    string readFile = "studentAccomplishedQuests.txt";
    string line, student, quest;
    int tokenAmount;

    // Show all completed quests
    cout << "\n--- Quests Completed by Students ---\n";
    ifstream inFile(readFile);
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();

    // Input details for approval
    cout << "\n--- Enter Details to Approve ---\n";
    cout << "Student Username: ";
    getline(cin, student);
    cout << "Quest Name: ";
    getline(cin, quest);
    cout << "Token Amount: ";
    cin >> tokenAmount;
    cin.ignore();

    string approvedLine = student + "," + quest + "," + to_string(tokenAmount);
    deleteLine(readFile, approvedLine);

    bool found = false;
    string walletFile = "studentBalance.txt";
    ifstream walletIn(walletFile);
    ofstream tempFile("tempBalance.txt");
    string walletLine;

    while (getline(walletIn, walletLine)) {
        size_t pos = walletLine.find(',');
        string username = walletLine.substr(0, pos);
        int balance = stoi(walletLine.substr(pos + 1));

        if (username == student) {
            balance += tokenAmount;
            tempFile << username << "," << balance << endl;
            found = true;
        } else {
            tempFile << walletLine << endl;
        }
    }

    walletIn.close();

    if (!found) {
        tempFile << student << "," << tokenAmount << endl;
    }

    tempFile.close();
    remove(walletFile.c_str());
    rename("tempBalance.txt", walletFile.c_str());

    ofstream outFile("ApprovedQuests.txt", ios::app);
    outFile << approvedLine << endl;
    outFile.close();

    cout << "\nQuest Approved and " << tokenAmount << " tokens added to " << student << "'s wallet.\n";
}

void createQuest () {
    int tokenAmount;
    string quest;

    cout << "\n--- Create Quests ---\n";
    cout << "-----------------------\n";
    cout << "Quest: ";
    getline (cin, quest);
    cout << "Token Reward: ";
    cin >> tokenAmount;
    cin.ignore();

    string concat = quest + "," + to_string(tokenAmount);

    ofstream outFile("quests.txt", ios::app);
    if (!outFile) {
        cerr << "ERROR: Could not open quests.txt\n";
        return;
    }

    outFile << concat << endl;
    outFile.close();
}

void deleteQuest () {
    string quest;
    int tokenAmount;
    string filename = "quests.txt";

    cout << "\n--- Delete Quest ---\n";
    cout << "----------------------\n";
    cout << "Enter the quest: ";
    getline (cin, quest);
    cout << "Enter Token Amount: ";
    cin >> tokenAmount;

    string concat = quest + "," + to_string(tokenAmount);
    deleteLine(filename, concat);
}

void questsTab () {
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
                continue;
        }
    } while (choice != 5);
}