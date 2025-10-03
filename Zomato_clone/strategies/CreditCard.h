#ifndef CREDIT_CARD_H
#define CREDIT_CARD_H

#include "PaymentStrategy.h"
#include "../models/Order.h"
#include "../models/User.h"

class CreditCard : public PaymentStrategy {
public:
    void pay(double& amount) override {
        cout << "Amount " << amount << " paid by Credit Card." << endl;
    }
};

#endif
