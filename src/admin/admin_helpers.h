#ifndef ADMIN_HELPERS_H
#define ADMIN_HELPERS_H

#include <string>
using namespace std;

bool isUsernameTaken(const string &accountsFile, const string &usernameToCheck);
bool isEmailTaken(const string &accountsFile, const string &emailToCheck);
bool deleteLine(const string &filename, const string &targetLine);
bool editLine(const string &filename, const string &targetLine, const string &updatedLine);
void updateTotalTokens(int change);
void updateTotalMoney(int pesos);
void clearSystem(int delayMillis = 1000);

#endif
