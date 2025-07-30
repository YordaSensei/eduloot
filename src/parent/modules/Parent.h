#pragma once
#include "../../user/modules/User.h"

class Parent : public User {
public:
    void transferToChild();
    void viewChildBal();
    void parentMain(string insertedEmail, string insertedChildEmail);
    void transactions() override;
    
    void setInsertedChildEmail(const std::string& e) { childEmail = e; }

private:
    void updateChildBalance(const std::string& childEmail, int newBalance);
    void recordChildTransaction(const std::string& childEmail, const std::string& type, int amount, int newBalance);
    
    std::string childEmail;
    int childTokenBalance;
};