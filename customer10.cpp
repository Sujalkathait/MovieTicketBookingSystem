#ifndef CUSTOMER10_CPP
#define CUSTOMER10_CPP

#include <string>

// Class: Customer
// Responsibility: Stores customer information

class Customer
{
private:
    std::string customerName;
    std::string phoneNumber;

public:
    // Constructor
    Customer(
        const std::string& name = "",
        const std::string& phone = ""
    )
        : customerName(name),
          phoneNumber(phone)
    {
    }

    // Getters
    const std::string& getCustomerName() const
    {
        return customerName;
    }

    const std::string& getPhoneNumber() const
    {
        return phoneNumber;
    }

    // Validation
    bool isValid() const
    {
        return !customerName.empty() && !phoneNumber.empty();
    }
};

#endif