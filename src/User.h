#pragma once
#include <string>

class User {
public:
    User(const std::string& name, double tokenBalance);
    virtual ~User() = default;

    virtual void wallet() const;
    virtual void viewBalance() const;
    virtual void purchase() const;
    virtual void convert() const;
    virtual void notifications() const;
    virtual void transactions() const;

    std::string getName() const { return name; }
    double getTokenBalance() const { return tokenBalance; }
    
protected:
    void setTokenBalance(double newBalance) { tokenBalance = newBalance; }
    
private:
    std::string name;
    double tokenBalance;
};