#pragma once
#include "../../quest_helpers.h"

class StudentQuests {
    public:
        void quests(string email);
};

void StudentQuests::quests(string email) {
    int choice;
    do {

        cout << termcolor::bold << termcolor::blue;
        cout << "\n+-------------------------------+\n";
        cout << "|"<<termcolor::bright_cyan <<"            QUESTS             "<<termcolor::blue<<"|\n";
        cout << "+-------------------------------+\n";
        cout << "|  1. Claim quest               |\n";
        cout << "|  2. "<< termcolor::bright_cyan <<"Back to Home              "<<termcolor::blue<<"|\n";
        cout << "+-------------------------------+\n"<< termcolor::reset;

        do {
            choice = promptChoice(1,2, "Choice: ");
            if (choice == 0) {
                cout << termcolor::bright_red << "Zero is not a valid option here.\n" << termcolor::reset;
            }
        } while (choice == 0);

        switch (choice) {
            case 1: {
                system("cls");
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

                cout << termcolor::bold << termcolor::blue;
                cout << "\n+------------------------------+\n";
                cout << "|" << termcolor::bright_cyan << "     Available Quests     " << termcolor::blue <<"|\n";
                cout << "+------------------------------+\n";
                for (size_t i = 0; i < questList.size(); ++i) {
                    cout << i + 1 << ". Task: " << questList[i].desc
                         << " | Reward: " << questList[i].reward
                         << " tokens | Claims left: " << questList[i].claims << endl;
                }
                cout << "+------------------------------+\n";

                int questChoice = promptChoice (1,questList.size(),"Select number of finished quest (0 to cancel): ");

                // Save to accomplished quests file
                ofstream outFile("studentAccomplishedQuests.txt", ios::app);
                if (outFile) {
                    Quest selected = questList[questChoice - 1];
                    outFile << email << "," << selected.desc
                            << "," << selected.reward
                            << "," << selected.claims << endl;
                    outFile.close();

                    cout << termcolor::red << "Quest claimed! Admin confirmation will take a while.\n";
                    clearSystem(2000);
                } else {
                    cout << termcolor::red << "Failed to write to studentAccomplishedQuests.txt\n";
                }

                break;
            }

            case 2:
                cout << termcolor::red << "Returning to Home...\n";
                clearSystem();
                break;
        }
    } while (choice != 2);
}