#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "../../admin/includes/admin_helpers.h"

class User {

public:
    virtual ~User() = default;

    virtual void wallet();
    virtual void viewBalance();
    virtual void purchase();
    virtual void purchaseTokens();
    virtual void convertTokens();
    virtual void notifications();
    virtual void transactions();
    
    std::string getEmail() const { return email; }
    std::string getUserType() const { return userType; }
    int getTokenBalance() const { return tokenBalance; }

    void setUserType(const std::string& t) { userType = t; }
    void setEmail(const std::string& e) { email = e; }
    
protected:
    void displayAdminMessages();
    void displaySystemAlerts();
    void displayMerchants();
    void displayProducts(const std::string& selectedMerchant);
    bool processPurchase(const std::string& selectedMerchant, const Product& product, int productQty, int totalAmount);

    void initializeBalanceIfNeeded(const std::string& filename) {
        std::ifstream inFile(filename);
        bool exists = false;
        std::string line;
        
        while (std::getline(inFile, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                std::string fileEmail = line.substr(0, pos);
                if (fileEmail == email) {
                    exists = true;
                    break;
                }
            }
        }
        inFile.close();

        if (!exists) {
            std::ofstream outFile(filename, std::ios::app);
            outFile << email << ",0\n";
            outFile.close();
            tokenBalance = 0;
        }
    }

    void updateBalanceInFile(int newBalance) {
        tokenBalance = newBalance;
        vector<string> lines;
        string line;
        bool found = false;
        
        string filename = userType + "Balance.txt";
        ifstream inFile(filename);
        
        while (getline(inFile, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                string fileEmail = line.substr(0, pos);
                
                if (fileEmail == email) {
                    lines.push_back(email + "," + to_string(newBalance));
                    found = true;
                } else {
                    lines.push_back(line);
                }
            }
        }
        inFile.close();
        
        if (!found) {
            lines.push_back(email + "," + to_string(newBalance));
        }
        
        ofstream outFile(filename);
        for (const auto& line : lines) {
            outFile << line << "\n";
        }
        outFile.close();
    }

    void updateProductQuantity(const std::string& selectedMerchant, const Product& product, int productQty) {
        vector<Product> products;
        ifstream productInFile("productList.txt");
        string line;

        while (getline(productInFile, line)) {
            if (!line.empty()) {
                Product p;
                string strPrice, strQuantity;
                stringstream split(line);

                getline(split, p.merchant, ',');
                getline(split, p.name, ',');
                getline(split, strPrice, ',');
                getline(split, strQuantity, ',');
                getline(split, p.desc);

                p.price = stod(strPrice);
                p.quantity = stoi(strQuantity);

                if (p.merchant == selectedMerchant && p.name == product.name) {
                    p.quantity -= productQty;
                }

                products.push_back(p);
            }
        }
        productInFile.close();

        ofstream productOutFile("productList.txt");
        for (const auto& p : products) {
            productOutFile << p.merchant << "," << p.name << "," 
                        << p.price << "," << p.quantity << "," 
                        << p.desc << endl;
        }
        productOutFile.close();
    }

    void recordTransaction(const string& type, int amount, int newBalance) {
        time_t now = time(0);
        string dt = ctime(&now);
        dt.pop_back();

        ofstream outFile(userType + "TokenTransactions.txt", ios::app);
        if (outFile.is_open()) {
            outFile << email << "," << type << "," << amount << "," << newBalance << "," << dt << endl;
            outFile.close();
        }
    }

    void recordProductTransaction(const std::string& selectedMerchant,
                                  const Product& product,
                                  int totalAmount,
                                  int productQty,
                                  const std::string& currentUserBalance,
                                  const std::string& currentMerchantBalance) {
        time_t now = time(0);
        string dt = ctime(&now);
        dt.pop_back();

        ofstream transactionOutFile(userType + "ProductTransactions.txt", ios::app);
        transactionOutFile << email << "," << selectedMerchant << "," 
                        << product.name << "," << totalAmount << "," 
                        << productQty << "," << currentUserBalance << "," 
                        << currentMerchantBalance << "," << dt << endl;
        transactionOutFile.close();
    }

    template<typename T>
    bool getNumericInput(T& input, const std::string& prompt = "", const std::string& errorMsg = "Invalid input.", 
        T min = std::numeric_limits<T>::lowest(), T max = std::numeric_limits<T>::max()) 
    {
        if (!prompt.empty()) std::cout << termcolor::bright_cyan << prompt;
        
        if (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << termcolor::red << errorMsg << "\n";
            clearSystem();
            return false;
        }
        
        if (input < min || input > max) {
            std::cerr << "Please enter a value between " << min 
                    << " and " << max << "\n";
            clearSystem();
            return false;
        }
        
        return true;
    }

    bool getYesNoInput(char& input, const std::string& prompt = "", 
        const std::string& errorMsg = "Please enter 'y' or 'n'.") 
    {
        while (true) {
            if (!prompt.empty()) std::cout << prompt;
            
            std::string temp;
            std::cin >> temp;
            
            if (temp.length() == 1) {
                input = tolower(temp[0]);
                if (input == 'y' || input == 'n') {
                    return true;
                }
            }
            clearSystem();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << errorMsg << "\n";
            return false;
        }
    }

    
private:
    string email;
    string userType;
    int tokenBalance;
};