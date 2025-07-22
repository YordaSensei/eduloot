#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "admin/admin_helpers.h"


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
    template<typename T>
    bool getValidInput(T& input, 
                const std::string& prompt = "", 
                const std::string& errorMsg = "Invalid input.",
                T min = std::numeric_limits<T>::lowest(),
                T max = std::numeric_limits<T>::max()) 
    {
        if (!prompt.empty()) std::cout << prompt;
        
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << errorMsg << "\n";
            return false;
        }
        
        if (input < min || input > max) {
            std::cout << "Please enter a value between " << min 
                    << " and " << max << "\n";
            return false;
        }
        
        return true;
    }

    
private:
    string email;
    string userType;
    int tokenBalance;
};