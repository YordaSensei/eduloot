#pragma once
#include "../core/User.h"

class Wallet : virtual public User {
public:
    void wallet();
    void viewBalance();
    void purchaseTokens();
    void convertTokens();
    
private:
    static const int tokenToPHPValue = 3;
};