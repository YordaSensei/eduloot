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
void clearSystem(int delayMillis);
void updateTotalMoney(float pesos);
void clearSystem(int delayMillis);
string promptNonEmptyInput(const string& promptText);
double promptValidatedPrice(const string& promptText);
int promptValidatedQuantity(const string& promptText);
int promptValidatedIndex(const string& promptText, size_t max, bool allowCancel = false);
int promptChoice (int min, int max, const string& promptText);

#endif