#ifndef MANAGE_ACCOUNTS_H
#define MANAGE_ACCOUNTS_H

#include <string>
using namespace std;

void manageAccounts();
void createAccount();
bool isUsernameTaken(const string& accountsFile, const string& usernameToCheck);

#endif


