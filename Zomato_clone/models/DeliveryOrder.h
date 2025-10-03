#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include "Order.h"
#include <bits/stdc++.h>
using namespace std;

class DeliveryOrder : public Order {
private:
    string location;
public:
    DeliveryOrder(string location = "") {
        this->location = location;
    }

    string getType() override {
        return "Delivery";
    }

    string getLocation() {
        return location;
    }

    void setLocation(const string& loc) {
        location = loc;
    }
};

#endif
