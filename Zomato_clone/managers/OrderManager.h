#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include "../models/Order.h"
#include <bits/stdc++.h>
using namespace std;

class OrderManager {
private:
    vector<Order*> orders;
    static OrderManager* instance;

    OrderManager() {}

public:
    static OrderManager* getInstance() {
        if (!instance) instance = new OrderManager();
        return instance;
    }

    void addOrder(Order* o) { orders.push_back(o); }

    void listOrders() {
        for (auto o : orders) {
            cout << o->getUser()->getName() << " ordered from " 
                 << o->getRestaurant()->getName() << endl;
        }
    }
};

OrderManager* OrderManager::instance = nullptr;

#endif
