#include "../includes/admin_includes.h"  

using namespace std;

// Checks if the given username already exists in the specified accounts file
bool isUsernameTaken(const string &accountsFile, const string &usernameToCheck) {
    ifstream file(accountsFile);
    if (!file.is_open()) return false; // Return false if file couldn't be opened

    string line;

    // Read the file line by line
    while (getline(file, line)) {
        stringstream split(line);
        string email, username, password;

        // Parse each line by comma
        if (getline(split, email, ',') &&
            getline(split, username, ',') &&
            getline(split, password)) {
            
            // Check if the username matches the one to check
            if (username == usernameToCheck) {
                return true; // Return true if username is found
            }
        }
    }

    return false; // Return false if username is not found
}

// Checks if the given email already exists in the specified accounts file
bool isEmailTaken(const string &accountsFile, const string &emailToCheck) {
    ifstream file(accountsFile);
    if (!file.is_open()) return false; // Return false if the file couldn't be opened

    string line;

    // Read the file line by line
    while (getline(file, line)) {
        stringstream split(line);
        string email, username, password;

        // Parse each line by comma
        if (getline(split, email, ',') &&
            getline(split, username, ',') &&
            getline(split, password)) {
            
            // Check if the email matches the one to check
            if (email == emailToCheck) {
                return true; // Return true if email is found
            }
        }
    }

    return false; // Return false if email is not found
}

// Deletes a matching line from the specified file
bool deleteLine(const string &filename, const string &targetLine) {
    ifstream inFile(filename);
    ofstream tempFile("tempFile.txt");

    if (!inFile || !tempFile) {
        cout << "ERROR: Failed to access file.\n";
        return false;
    }

    string line;
    bool found = false; // Flag to track if the target line was found

    // Read the file line by line
    while (getline(inFile, line)) {
        if (line != targetLine) {
            tempFile << line << '\n'; // Write non-matching lines to the temp file
        } else {
            found = true; // Skip writing the target line (effectively deleting it)
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(filename.c_str());                  // Remove the original file
        rename("tempFile.txt", filename.c_str()); 
    } else {
        remove("tempFile.txt"); // Clean up the unused temp file
    }

    return found;
}

// Edits a matching line from the specified file and replaces it with the updated line
bool editLine(const string &filename, const string &targetLine, const string &updatedLine) {
    ifstream inFile(filename);
    ofstream tempFile("tempFile.txt");

    if (!inFile || !tempFile) {
        cout << "\nERROR: Failed to access file.\n";
        return false;
    }

    string line;
    bool found = false;

    // Read the file line by line
    while (getline(inFile, line)) {
        if (line == targetLine) {
            tempFile << updatedLine << endl; // Replace the matching line with the updated line
            found = true;
        } else {
            tempFile << line << endl; // Write the other lines
        }
    }

    inFile.close();
    tempFile.close();

    if (found) {
        remove(filename.c_str());                    // Delete the original file
        rename("tempFile.txt", filename.c_str());    // Rename temp file to original file name
        cout << "\n-- Edited successfully --\n";
    } else {
        cout << "\n-- NOT found --\n";
    }

    return found;
}

// Updates the total number of tokens in the system using the given change amount
void updateTotalTokens(int change) {
    int systemTokens = 0;
    string line;

    ifstream inFile("admin/files/tokensSystem.txt");
    if (inFile.is_open()) {
        getline(inFile, line); // Read the current token value from the file
        if (!line.empty()) {
            systemTokens = stoi(line); // Convert the string to an integer
        }
        inFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }

    systemTokens += change; // Add the change to the current total
    if (systemTokens < 0) systemTokens = 0; // Ensure tokens don't go negative

    ofstream outFile("admin/files/tokensSystem.txt");
    if (outFile.is_open()) {
        outFile << systemTokens << endl; // Write the updated value back to the file
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
        getline(inFile, line); // Read the current money amount from the file
        if (!line.empty()){
            systemMoney = stof(line); // Convert the string to an integer
        }
        inFile.close();
    } else {
        cout << "\nERROR opening moneySystem.txt...\n";
    }

    systemMoney += pesos; // Add the change to the current total
    if (systemMoney < 0) systemMoney = 0; // Ensure money don't go negative

    ofstream outFile ("admin/files/moneySystem.txt");
    if(outFile.is_open()) {
        outFile << systemMoney << endl; // Write the updated value back to the file
        outFile.close();
    } else {
        cout << "\nERROR opening moneySystem.txt...\n";
    }
}

void updateTokensOut (int tokens) {
    int tokensOut = 0;
    string line;

    ifstream inFile("admin/files/tokensOut.txt");
    if (inFile.is_open()) {
        getline(inFile, line); // Read the current token value from the file
        if (!line.empty()) {
            tokensOut = stoi(line); // Convert the string to an integer
        }
        inFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }

    tokensOut += tokens; // Add the change to the current total
    if (tokensOut < 0) tokensOut = 0; // Ensure tokens don't go negative

    ofstream outFile("admin/files/tokensOut.txt");
    if (outFile.is_open()) {
        outFile << tokensOut << endl; // Write the updated value back to the file
        outFile.close();
    } else {
        cout << "\nERROR opening file...\n";
    }

}

// clears the console with delay
void clearSystem(int delayMillis) { 
    Sleep(delayMillis); 
    system("cls");
}

// Prompts the user for a non-empty string input using the given prompt text
string promptNonEmptyInput(const string& promptText) {
    string input;

    do {
        cout << termcolor::bright_yellow << promptText;
        getline(cin, input);
        cout << termcolor::reset;

        if (input.empty()) {
            cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
        }
    } while (input.empty()); // Repeat until the user enters a non-empty value

    return input;
}

// Prompts the user for a valid price input (double) with basic validation and a cancel option
double promptValidatedPrice(const string& promptText) {
    double price;
    string input;

    while (true) {
        cout << termcolor::bright_yellow << promptText;
        getline (cin, input);

        if (input.empty()) {
            cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
            continue;
        }

        try {
            price = stod(input);

           if (price == 0) {
                return 0; // returns 0 for cancel option
            } 

            if (price > 0) {
                // Valid positive price input
                return price;
            } else {
                // Handles negative numbers
                cout << termcolor::red << "Please enter a positive number or 0 to cancel.\n" << termcolor::reset;
            }
            
        } catch (...) {
            // handles non-numeric input
            cout << termcolor::bright_red << "ERROR: Invalid price input.\n" << termcolor::reset;
            continue;
        }
    }
}

// Prompts the user for a valid quantity input (integer) with basic validation and a cancel option
int promptValidatedQuantity(const string& promptText) {
    int quantity;
    string input;

    while (true) {
        cout << termcolor::bright_yellow << promptText;
        getline (cin, input);

        if (input.empty()) {
            cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
            continue;
        }

        try {
            quantity = stoi(input);

            if (quantity == 0) {
                return 0;
            }

            if (quantity > 0) {
                // Valid positive quantity
                return quantity;
            } else {
                // Handles negative numbers
                cout << termcolor::red << "Please enter a positive number or 0 to cancel.\n" << termcolor::reset;
            }
        } catch (...) {
            // Handles non-numeric input
            cout << termcolor::red << "Invalid input. Please enter a valid number.\n" << termcolor::reset;
            continue;
        }
    }
}

// validates integer input for choices within a specified range
int promptChoice (int min, int max, const string& promptText) {
    int choice;
    string input;

    while (true) {
        cout << termcolor::bright_yellow << promptText;
        getline (cin, input); // gets string input

        if (input.empty()) { // Checks if the user submitted an empty input 
            cout << termcolor::bright_red << "ERROR: Field cannot be empty.\n" << termcolor::reset;
            continue;
        }

        try {
            choice = stoi(input); // converts string to integer

            if (choice == 0) {
                return 0;
            };

            if (choice >= min && choice <= max) {
                // valid input
                break;
            } else {
                cout << termcolor::red << "Invalid choice. Please enter a valid option.\n";
            }
        } catch (...) {
            cout << termcolor::red << "Invalid input. Please enter a valid number.\n" << termcolor::reset;
            continue;
        }
    }

    return choice;
}

// Checks if the user entered "0" to cancel the current string input process.
bool cancelInput (string& input) {
    if (input == "0") {
        cout << termcolor::red << "\nCancelling...\nReturning to menu..." << termcolor::reset;
        clearSystem(1200);
        return true;
    }

    return false;
}