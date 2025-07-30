#pragma once
#include "../core/User.h"
#include "../../product_helpers.h"
#include <string>

class Purchase : virtual public User {
public:
    void purchase();
    
protected:
    void displayMerchants();
    void displayProducts(const std::string& selectedMerchant);
    bool processPurchase(const std::string& selectedMerchant, 
                        const Product& product, 
                        int productQty, 
                        int totalAmount);
    void updateProductQuantity(const std::string& selectedMerchant, 
                              const Product& product, 
                              int productQty);
    void recordProductTransaction(const std::string& selectedMerchant,
                                 const Product& product,
                                 int totalAmount,
                                 int productQty,
                                 const std::string& currentUserBalance,
                                 const std::string& currentMerchantBalance);
};