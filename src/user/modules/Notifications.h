#pragma once
#include "../core/User.h"
#include <string>

class Notifications : virtual public User {
public:
    void notifications();
    
private:
    void displayAdminMessages();
    void displaySystemAlerts();
};