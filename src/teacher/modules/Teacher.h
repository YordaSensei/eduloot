#pragma once
#include "../../user/modules/Wallet.h"
#include "../../user/modules/Purchase.h"
#include "../../user/modules/Notifications.h"
#include "../../user/modules/Transactions.h"

class Teacher : public Wallet, public Purchase, public Notifications, public Transactions {
public:
    void teacherMain(string insertedEmail);
};