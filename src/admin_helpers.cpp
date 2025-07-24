#include "admin/includes/admin_includes.h"

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
        cout << "ERROR: Failed to access file.\n";
        return false;
    }

    auto sanitize = [](string s) {
        while (!s.empty() && (s.back() == '\r' || s.back() == '\n' || s.back() == ' '))
            s.pop_back();
        return s;
    };

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (sanitize(line) != sanitize(targetLine)) {
            tempFile << line << '\n';
        } else {
            found = true;
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(filename.c_str());
        rename("tempFile.txt", filename.c_str());
        cout << "Successful\n";
    } else {
        remove("tempFile.txt");
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

string promptNonEmptyInput(const string& promptText) {
    string input;
    do {
        cout << termcolor::bright_yellow << promptText;
        getline(cin, input);
        cout << termcolor::reset;

        if (input.empty()) {
            cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
        }
    } while (input.empty());
    return input;
}

double promptValidatedPrice(const string& promptText) {
    double price;
    while (true) {
        cout << termcolor::bright_yellow << promptText;
        if (cin >> price && price >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return price;
        }
        cout << termcolor::bright_red << "ERROR: Invalid price input.\n" << termcolor::reset;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int promptValidatedQuantity(const string& promptText) {
    int quantity;
    while (true) {
        cout << termcolor::bright_yellow << promptText;
        if (cin >> quantity && quantity >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return quantity;
        }
        cout << termcolor::bright_red << "ERROR: Invalid quantity input.\n" << termcolor::reset;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int promptValidatedIndex(const string& promptText, size_t max, bool allowCancel) {
    int choice;

    while (true) {
        cout << termcolor::bright_yellow << promptText;
        if (cin >> choice) {
            if (allowCancel && choice == 0) return 0;
            if (choice >= 1 && choice <= static_cast<int>(max)) return choice;
        }

        cout << termcolor::red << "Invalid input. ";
        if (allowCancel)
            cout << "Enter 1-" << max << " or 0 to cancel.\n";
        else
            cout << "Enter a number between 1 and " << max << ".\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int promptChoice (int min, int max, const string& promptText) {
    int choice;
    while (true) {
        cout << termcolor::bright_yellow << promptText;
        if (cin >> choice && choice >= min && choice <= max) break;
        cout << termcolor::red << "Invalid choice. Please enter 1-"<< max << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return choice;
}