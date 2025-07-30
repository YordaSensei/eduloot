#pragma once
#include "../core/User.h"
#include <string>

class Transactions : virtual public User {
public:
    void transactions();
};