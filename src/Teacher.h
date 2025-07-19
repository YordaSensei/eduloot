#pragma once
#include "User.h"

class Teacher : public User {
    public:
    Teacher(const std::string& name, double tokenBalance);

    void wallet() const override;
    void viewBalance() const override;
    void purchase() const override;
    void notifications() const override;
    void transactions() const override;
    void teacherMain();
};