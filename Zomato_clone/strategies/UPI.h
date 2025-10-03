#ifndef UPI_H
#define UPI_H

#include "PaymentStrategy.h"
#include "../models/Order.h"

class UPI : public PaymentStrategy {
private:
    string mobile;
public:
    UPI(const string& mob = "") { mobile = mob; }

    void pay(double& amount) override {
        cout << "Amount " << amount << " paid via UPI: " 
             << mobile << "@ybl" << endl;
    }
};

#endif
