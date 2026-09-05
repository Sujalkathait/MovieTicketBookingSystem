#ifndef CASHPAYMENT14_CPP
#define CASHPAYMENT14_CPP

#include <iostream>
#include <string>
#include "payment11.cpp"

// Class: CashPayment
// Responsibility: Handles cash payment processing

class CashPayment : public Payment
{
public:
    // Process payment
    bool pay(double amount) override
    {
        std::cout << "[Cash] Rs."
                  << static_cast<int>(amount)
                  << " paid successfully.\n";

        return true;
    }

    // Get payment type
    std::string getPaymentType() const override
    {
        return "Cash";
    }
};

#endif