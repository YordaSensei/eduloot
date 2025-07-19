#pragma once
#include "User.h"

class Parent : public User {
    public:
    Parent(const std::string& name, double tokenBalance);

    void wallet() const;
    void purchase() const;
    void viewBalance() const override;
    void transferToChild(double amount);
    void notifications() const override;
    void transactions() const override;
    void parentMain();

private:
    std::string childID;
};