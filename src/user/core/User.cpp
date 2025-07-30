#include "User.h"
#include <iostream>
#include <limits>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "../../admin/includes/admin_helpers.h"
#include "../modules/Notifications.cpp"
#include "../modules/Purchase.cpp"
#include "../modules/Transactions.cpp"
#include "../modules/Wallet.cpp"

using namespace std;

void User::updateBalanceInFile(int newBalance) {
        setTokenBalance(newBalance);
        vector<string> lines;
        string line;
        bool found = false;
        
        string filename = getUserType() + "Balance.txt";
        ifstream inFile(filename);
        
        while (getline(inFile, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                string fileEmail = line.substr(0, pos);
                
                if (fileEmail == getEmail()) {
                    lines.push_back(getEmail() + "," + to_string(newBalance));
                    found = true;
                } else {
                    lines.push_back(line);
                }
            }
        }
        inFile.close();
        
        if (!found) {
            lines.push_back(getEmail() + "," + to_string(newBalance));
        }
        
        ofstream outFile(filename);
        for (const auto& line : lines) {
            outFile << line << "\n";
        }
        outFile.close();
}

void User::initializeBalanceIfNeeded(const std::string& filename) {
        std::ifstream inFile(filename);
        bool exists = false;
        std::string line;
        
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                std::string fileEmail = line.substr(0, pos);
                if (fileEmail == getEmail()) {
                    exists = true;
                    break;
                }
            }
        }
        inFile.close();

        if (!exists) {
            std::ofstream outFile(filename, std::ios::app);
            outFile << getEmail() << ",0\n";
            outFile.close();
            setTokenBalance(0);
        }
}

void User::recordTransaction(const string& type, int amount, int newBalance) {
        time_t now = time(0);
        string dt = ctime(&now);
        dt.pop_back();

        ofstream outFile(getUserType() + "TokenTransactions.txt", ios::app);
        if (outFile.is_open()) {
            outFile << getEmail() << "," << type << "," << amount << "," << newBalance << "," << dt << endl;
            outFile.close();
        }
}