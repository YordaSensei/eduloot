#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "student_helpers.h"
#include "quest_helpers.h"
using namespace std;

void quests(string email) {
    int choice;
    do {
        cout << "1. Claim quest\n";
        cout << "2. Back to Home\n";

        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                vector<Quest> questList;
                ifstream questInFile("quests.txt");
                string line;

                if (!questInFile) {
                    cout << "Failed to open quests.txt\n";
                    return;
                }

                while (getline(questInFile, line)) {
                    if (!line.empty()) {
                        Quest q;
                        string rewardStr, claimsStr;
                        stringstream split(line);

                        getline(split, q.desc, ',');
                        getline(split, rewardStr, ',');
                        getline(split, claimsStr);

                        q.reward = stoi(rewardStr);
                        q.claims = stoi(claimsStr);

                        questList.push_back(q);
                    }
                }
                questInFile.close();

                if (questList.empty()) {
                    cout << "No quests available.\n";
                    return;
                }

                cout << "\n--- Available Quests ---\n";
                for (size_t i = 0; i < questList.size(); ++i) {
                    cout << i + 1 << ". Task: " << questList[i].desc
                         << " | Reward: " << questList[i].reward
                         << " tokens | Claims left: " << questList[i].claims << endl;
                }
                cout << "------------------------\n";

                int questChoice;
                cout << "Select number of quest: ";
                cin >> questChoice;

                if (questChoice < 1 || questChoice > questList.size()) {
                    cout << "Invalid choice.\n";
                    return;
                }

                // Save to accomplished quests file
                ofstream outFile("studentAccomplishedQuests.txt", ios::app);
                if (outFile) {
                    Quest selected = questList[questChoice - 1];
                    outFile << email << "," << selected.desc
                            << "," << selected.reward
                            << "," << selected.claims << endl;
                    outFile.close();

                    cout << "Quest claimed! Admin confirmation will take a while.\n";
                } else {
                    cout << "Failed to write to studentAccomplishedQuests.txt\n";
                }

                break;
            }

            case 2:
                cout << "Returning to home...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 2);
}