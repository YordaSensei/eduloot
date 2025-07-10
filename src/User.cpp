#include "User.h"
#include <iostream>

User::User(const std::string& name, double tokenBalance) : name(name), tokenBalance(tokenBalance) {}

void User::getInfo() const {
    std::cout << "Type : User" << std::endl;
    std::cout << "Name :  " << name << std::endl;
    std::cout << "Token Balance : " << tokenBalance << std::endl;
}