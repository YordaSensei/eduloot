#include "Teacher.h"
#include <iostream>

Teacher::Teacher(const std::string& name, double tokenBalance) : User(name, tokenBalance) {}

void Teacher::getInfo() const {
    std::cout << "Type : Teacher" << std::endl;
    std::cout << "Name :  " << name << std::endl;
    std::cout << "Token Balance : " << tokenBalance << std::endl;
}

void Teacher::makePurchase() const {
    std::cout << "Teacher Purchased!" << std::endl;
}