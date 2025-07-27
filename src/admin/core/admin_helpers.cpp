#include "../includes/admin_includes.h"  

using namespace std;

// verifies if the username already exists
bool isUsernameTaken (const string &accountsFile, const string &usernameToCheck) {
    ifstream file (accountsFile);
    if (!file.is_open()) return false;
    string line;

    while (getline(file, line)) {
        stringstream split (line);
        string email, username, password;

        if (getline(split, email, ',') &&
            getline(split, username, ',') &&
            getline(split, password)) {
        
                if (username == usernameToCheck) {
                return true;
            }
        }
    }

    return false;
}

// verifies if the email already exists
bool isEmailTaken (const string &accountsFile, const string &emailToCheck) {
    ifstream file (accountsFile);
    if (!file.is_open()) return false;
    string line;

    while (getline(file, line)) {
        stringstream split (line);
        string email, username, password;

        if (getline(split, email, ',') &&
            getline(split, username, ',') &&
            getline(split, password)) {
        
                if (email == emailToCheck) {
                return true;
            }
        }
    }

    return false;
}

// deletes a matching line from the file
bool deleteLine(const string &filename, const string &targetLine) {
    ifstream inFile(filename);
    ofstream tempFile("tempFile.txt");

    if (!inFile || !tempFile) {
        cout << "ERROR: Failed to access file.\n";
        return false;
    }

    string line;
    bool found = false;

    while (getline(inFile, line)) {
        if (line != targetLine) {
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

// edits a matching line from the file
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

// updates total tokens in the system
void updateTotalTokens (int change) {
    int systemTokens = 0;
    string line;

    ifstream inFile ("admin/files/tokensSystem.txt");
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

    ofstream outFile ("admin/files/tokensSystem.txt");
    if(outFile.is_open()) {
        outFile << systemTokens << endl;
        outFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }
}

// updates total money in the system
void updateTotalMoney (float pesos) {
    float systemMoney = 0;
    string line;

    ifstream inFile ("admin/files/moneySystem.txt");
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

    ofstream outFile ("admin/files/moneySystem.txt");
    if(outFile.is_open()) {
        outFile << systemMoney << endl;
        outFile.close();
    } else {
        cout << "\nERROR opening moneySystem.txt...\n";
    }
}

// clears the console with delay
void clearSystem(int delayMillis) { 
    Sleep(delayMillis); 
    system("cls");
}

// validates string input to not accept empty inputs
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

// validates double input for prices
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

// validates int input for quantity
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

// validates numeric input used to access vector elements
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

// validates integer input for menu choices within a specified range
int promptChoice (int min, int max, const string& promptText) {
    int choice;
    string input;

    while (true) {
        cout << termcolor::bright_yellow << promptText;
        getline (cin, input);

        if (input.empty()) {
            cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
            continue;
        }

        try {
            choice = stoi(input);
            if (choice >= min && choice <= max) {
                break;
            } else {
                cout << termcolor::red << "Invalid choice. Please enter 1-"<< max << ".\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } catch (...) {
            cout << termcolor::red << "Invalid input. Please enter a valid number.\n" << termcolor::reset;
            continue;
        }
    }

    return choice;
}