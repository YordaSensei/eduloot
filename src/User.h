#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "admin/includes/admin_helpers.h"

class User {

public:
    virtual ~User() = default;

    virtual void wallet();
    virtual void viewBalance();
    virtual void purchase();
    virtual void purchaseTokens();
    virtual void convertTokens();
    virtual void notifications();
    virtual void transactions();
    
    std::string getEmail() const { return email; }
    int getTokenBalance() const { return tokenBalance; }

    void setUserType(const std::string& t) { userType = t; }
    void setEmail(const std::string& e) { email = e; }
    
protected:
    void updateBalanceInFile(int newBalance) {
        tokenBalance = newBalance;
        vector<string> lines;
        string line;
        bool found = false;
        
        string filename = userType + "Balance.txt";
        ifstream inFile(filename);
        
        while (getline(inFile, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                string fileEmail = line.substr(0, pos);
                
                if (fileEmail == email) {
                    lines.push_back(email + "," + to_string(newBalance));
                    found = true;
                } else {
                    lines.push_back(line);
                }
            }
        }
        inFile.close();
        
        if (!found) {
            lines.push_back(email + "," + to_string(newBalance));
        }
        
        ofstream outFile(filename);
        for (const auto& line : lines) {
            outFile << line << "\n";
        }
        outFile.close();
    }

    void recordTransaction(const string& type, int amount, int newBalance) {
        ofstream outFile(userType + "TokenTransactions.txt", ios::app);
        if (outFile.is_open()) {
            outFile << email << "," << type << "," << amount << "," << newBalance << "\n";
            outFile.close();
        }
    }

    template<typename T>
    bool getNumericInput(T& input, 
                const std::string& prompt = "", 
                const std::string& errorMsg = "Invalid input.",
                T min = std::numeric_limits<T>::lowest(),
                T max = std::numeric_limits<T>::max()) 
    {
        if (!prompt.empty()) std::cout << prompt;
        
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << errorMsg << "\n";
            return false;
        }
        
        if (input < min || input > max) {
            std::cerr << "Please enter a value between " << min 
                    << " and " << max << "\n";
            return false;
        }
        
        return true;
    }

    bool getYesNoInput(char& input, 
                  const std::string& prompt = "",
                  const std::string& errorMsg = "Please enter 'y' or 'n'.") 
    {
        while (true) {
            if (!prompt.empty()) std::cout << prompt;
            
            std::string temp;
            std::cin >> temp;
            
            if (temp.length() == 1) {
                input = tolower(temp[0]);
                if (input == 'y' || input == 'n') {
                    return true;
                }
            }
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << errorMsg << "\n";
            return false;
        }
    }

    
private:
    string email;
    string userType;
    int tokenBalance;
};