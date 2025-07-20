#pragma once
#include <string>
#include <fstream>

class User {
public:
    User(const std::string& name, int tokenBalance);
    virtual ~User() = default;

    virtual void wallet() const;
    virtual void viewBalance() const;
    virtual void purchase() const;
    virtual void convert() const;
    virtual void notifications() const;
    virtual void transactions() const;

    std::string getName() const { return name; }
    int getTokenBalance() const { return tokenBalance; }
    
protected:
    void setTokenBalance(int newBalance) {
        int systemTokens = 0;
        string line;

        ifstream inFile ("tokensSystem.txt");
        if (inFile.is_open()) {
            getline(inFile, line);
            if (!line.empty()){
                systemTokens = stoi(line);
            }
            inFile.close();
        } else {
            cout << "\nERROR opening file...\n";
        }

        systemTokens += newBalance;
        if (systemTokens < 0) systemTokens = 0;

        ofstream outFile ("tokensSystem.txt");
        if(outFile.is_open()) {
            outFile << systemTokens << endl;
            outFile.close();
        } else {
            cout << "\nERROR opening file...\n";
        }
    }
    
private:
    std::string name;
    int tokenBalance;
};