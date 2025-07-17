#ifndef ADMIN_STRUCTS_H
#define ADMIN_STRUCTS_H

#include <string>
using namespace std;

struct Account {
    string username;
    string ciitEmail;
    string password;
};

struct Merchant {
    string shopname;
    string username;
    string password;
};

#endif
