#ifndef ADMIN_HELPERS_H
#define ADMIN_HELPERS_H

#include <string>
using namespace std;

bool isUsernameTaken(const string &accountsFile, const string &usernameToCheck);
bool isEmailTaken(const string &accountsFile, const string &emailToCheck);
bool deleteLine(const string &filename, const string &targetLine);
bool editLine(const string &filename, const string &targetLine, const string &updatedLine);
void updateTotalTokens(int change);
void updateTotalMoney(float pesos);
void updateTokensOut (int tokens);
void clearSystem(int delayMillis);
void clearSystem(int delayMillis = 1200);
string promptNonEmptyInput(const string& promptText);
double promptValidatedPrice(const string& promptText);
int promptValidatedQuantity(const string& promptText);
int promptValidatedIndex(const string& promptText, size_t max);
int promptChoice (int min, int max, const string& promptText);
bool cancelInput (string& input);

#endif