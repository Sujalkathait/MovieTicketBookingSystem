#ifndef UPIPAYMENT12_CPP
#define UPIPAYMENT12_CPP

#include <iostream>
#include <string>
#include "payment11.cpp"

// Class: UpiPayment
// Responsibility: Handles UPI payment processing

class UpiPayment : public Payment
{
private:
    std::string upiId;

public:
    // Constructor
    UpiPayment(const std::string& id = "user@upi")
        : upiId(id)
    {
    }

    // Process payment
    bool pay(double amount) override
    {
        if (upiId.empty())
        {
            std::cout << "[UPI] Payment failed: Invalid UPI ID.\n";
            return false;
        }

        std::cout << "[UPI] Rs."
                  << static_cast<int>(amount)
                  << " paid successfully.\n";

        return true;
    }

    // Get payment type
    std::string getPaymentType() const override
    {
        return "UPI";
    }

    // Get UPI ID
    const std::string& getUpiId() const
    {
        return upiId;
    }
};

#endif
