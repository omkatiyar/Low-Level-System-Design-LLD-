#ifndef PICKUP_ORDER_H
#define PICKUP_ORDER_H

#include "Order.h"
#include <bits/stdc++.h>
using namespace std;

class PickupOrder : public Order {
private:
    string resLocation;
public:
    PickupOrder(string location = "") {
        resLocation = location;
    }

    string getType() override {
        return "Pickup";
    }

    string getLocation() {
        return resLocation;
    }

    void setLocation(const string& loc) {
        resLocation = loc;
    }
};

#endif
