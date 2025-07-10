#pragma once
#include "User.h"

class Teacher : public User {
    public:
    Teacher(const std::string& name, double tokenBalance);

    void getInfo() const override;
    void makePurchase() const;
};