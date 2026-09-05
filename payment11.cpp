#ifndef PAYMENT11_CPP
#define PAYMENT11_CPP

#include <string>

// Class: Payment
// Responsibility: Defines the common interface for payment methods

class Payment
{
public:
    // Virtual destructor
    virtual ~Payment() = default;

    // Process payment
    virtual bool pay(double amount) = 0;

    // Get payment type
    virtual std::string getPaymentType() const = 0;
};

#endif
