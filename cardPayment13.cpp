#ifndef CARDPAYMENT13_CPP
#define CARDPAYMENT13_CPP

#include <iostream>
#include <string>
#include "payment11.cpp"

// Class: CardPayment
// Responsibility: Handles card payment processing

class CardPayment : public Payment
{
private:
    std::string cardNumber;
    std::string expiryDate;

public:
    // Constructor
    CardPayment(
        const std::string& number = "4532123456789012",
        const std::string& expiry = "12/28"
    )
        : cardNumber(number),
          expiryDate(expiry)
    {
    }

    // Process payment
    bool pay(double amount) override
    {
        if (cardNumber.empty() || cardNumber.length() < 4)
        {
            std::cout << "[Card] Payment failed: Invalid card details.\n";
            return false;
        }

        std::cout << "[Card] Rs."
                  << static_cast<int>(amount)
                  << " paid successfully.\n";

        return true;
    }

    // Get payment type
    std::string getPaymentType() const override
    {
        std::string lastFour = cardNumber.substr(cardNumber.length() - 4);
        return "Card (ending in " + lastFour + ")";
    }

    // Get card number
    const std::string& getCardNumber() const
    {
        return cardNumber;
    }

    // Get expiry date
    const std::string& getExpiryDate() const
    {
        return expiryDate;
    }
};

#endif