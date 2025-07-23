#pragma once
#include "User.h"

class Parent : public User {
public:
    void viewBalance() override;
    void transferToChild(int amount);
    void parentMain(string insertedEmail, string insertedChildEmail);

    
    void setInsertedChildEmail(const std::string& e) { childEmail = e; }

private:
    std::string childEmail;
    int childTokenBalance;
};