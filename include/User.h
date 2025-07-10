#pragma once
#include <string>

class User {
    public:
    User(const std::string& name, double tokenBalance);
    virtual ~User() = default;

    virtual void getInfo() const;

    protected:
    std::string name;
    double tokenBalance;
};