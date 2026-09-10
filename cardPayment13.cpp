
#ifndef CARDPAYMENT13_CPP
#define CARDPAYMENT13_CPP

#include <iostream>
#include <string>

#include "payment11.cpp"

// ============================================================================
// Class: CardPayment
// Responsibility: Handles card payment processing
// ============================================================================

class CardPayment : public Payment {
private:
  std::string cardNumber;
  std::string expiryDate;

public:
  // Constructor
  CardPayment(const std::string &number, const std::string &expiry)
      : cardNumber(number), expiryDate(expiry) {}

  // Process card payment
  bool pay(double amount) override {
    if (cardNumber.empty() || expiryDate.empty()) {
      std::cout << "[Card] Invalid card details.\n";
      return false;
    }

    std::cout << "[Card] Rs." << static_cast<int>(amount)
              << " paid successfully.\n";

    return true;
  }

  // Return payment type
  std::string getPaymentType() const override { return "Card"; }
};

#endif
