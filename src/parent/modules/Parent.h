#pragma once
#include "../../user/modules/Wallet.h"
#include "../../user/modules/Purchase.h"
#include "../../user/modules/Notifications.h"
#include "../../user/modules/Transactions.h"

class Parent : public Wallet, public Purchase, public Notifications, public Transactions {
public:
    void transferToChild();
    void viewChildBal();
    void parentMain(string insertedEmail, string insertedChildEmail);
    void setInsertedChildEmail(const std::string& e) { childEmail = e; }

private:
    void updateChildBalance(const std::string& childEmail, int newBalance);
    void recordChildTransaction(const std::string& childEmail, const std::string& type, int amount, int newBalance);
    
    std::string childEmail;
    int childTokenBalance;
};