#pragma once
#include <string>
#include <iostream>
#include <limits>

class User {

public:
    virtual ~User() = default;
    
    std::string getEmail() const { return email; }
    std::string getUserType() const { return userType; }
    int getTokenBalance() const { return tokenBalance; }

    void setUserType(const std::string& t) { userType = t; }
    void setEmail(const std::string& e) { email = e; }
    void setTokenBalance(int b) {tokenBalance = b; }
    
protected:
    void updateBalanceInFile(int newBalance);
    void initializeBalanceIfNeeded(const std::string& filename);
    void recordTransaction(const std::string& type, int amount, int newBalance);

    template<typename T>
    bool getNumericInput(T& input, const std::string& prompt = "", const std::string& errorMsg = "Invalid input.", 
        T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) 
    {
        if (!prompt.empty()) std::cout << termcolor::bright_cyan << prompt;
        
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << termcolor::red << errorMsg << "\n";
            clearSystem();
            return false;
        }
        
        if (input < min || input > max) {
            std::cerr << "Please enter a value between " << min 
                    << " and " << max << "\n";
            clearSystem();
            return false;
        }
        
        return true;
    }

    bool getYesNoInput(char& input, const std::string& prompt = "", 
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
            clearSystem();
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