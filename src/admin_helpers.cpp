#include "admin/admin_includes.h"

using namespace std;

bool isUsernameTaken (const string &accountsFile, const string &usernameToCheck) {
    ifstream file (accountsFile);
    if (!file.is_open()) return false;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        size_t pos2 = line.find(',', pos1 + 1);
        if (pos2 == string::npos) continue;

        string username = line.substr(pos1 + 1, pos2 - pos1 - 1);
        
        if (username == usernameToCheck) {
            return true;
        }
    }

    return false;
}

bool isEmailTaken (const string &accountsFile, const string &emailToCheck) {
    ifstream file (accountsFile);
    if (!file.is_open()) return false;
    string line;

    while (getline(file, line)) {
        size_t pos1 = line.find(',');
        if (pos1 == string::npos) continue;

        string email = line.substr(0, pos1);
        
        if (email == emailToCheck) {
            return true;
        }
    }

    return false;
}

bool deleteLine(const string &filename, const string &targetLine) {
    ifstream inFile(filename);
    ofstream tempFile("tempFile.txt");

    if (!inFile || !tempFile) {
        cout << "\nERROR: Failed to access file.\n";
        return false;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line != targetLine) {
            tempFile << line << endl;
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("tempFile.txt", filename.c_str());

    if (found) {
        cout << "\n-- Successful --\n";
    } else {
        cout << "\n-- NOT found (check spelling/case) --\n";
    }

    return found;
}

bool editLine (const string &filename, const string &targetLine, const string &updatedLine) {
    ifstream inFile (filename);
    ofstream tempFile ("tempFile.txt");

    if (!inFile || !tempFile) {
    cout << "\nERROR: Failed to access file.\n";
    return false;
    }   

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line == targetLine) {
            tempFile << updatedLine << endl;
            found = true;
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove(filename.c_str());
    rename("tempFile.txt", filename.c_str());

    if (found) {
        cout << "\n-- Edited successfully --\n";
    } else {
        cout << "\n-- NOT found --\n";
    }

    return found;
}

void updateTotalTokens (int change) {
    int systemTokens = 0;
    string line;

    ifstream inFile ("tokensSystem.txt");
    if (inFile.is_open()) {
        getline(inFile, line);
        if (!line.empty()){
            systemTokens = stoi(line);
        }
        inFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }

    systemTokens += change;
    if (systemTokens < 0) systemTokens = 0;

    ofstream outFile ("tokensSystem.txt");
    if(outFile.is_open()) {
        outFile << systemTokens << endl;
        outFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }
}

void updateTotalMoney (float pesos) {
    float systemMoney = 0;
    string line;

    ifstream inFile ("moneySystem.txt");
    if (inFile.is_open()) {
        getline(inFile, line);
        if (!line.empty()){
            systemMoney = stoi(line);
        }
        inFile.close();
    } else {
        cout << "\nERROR opening moneySystem.txt...\n";
    }

    systemMoney += pesos;
    if (systemMoney < 0) systemMoney = 0;

    ofstream outFile ("moneySystem.txt");
    if(outFile.is_open()) {
        outFile << systemMoney << endl;
        outFile.close();
    } else {
        cout << "\nERROR opening moneySystem.txt...\n";
    }
}

void clearSystem(int delayMillis) { 
    Sleep(delayMillis); 
    system("cls");
}


