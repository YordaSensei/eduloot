#pragma once
#include "User.h"

class Parent : public User {
public:
    void viewBalance() override;
    void transferToChild(int amount);
    void parentMain(string insertedEmail);

private:
    std::string childID;
};