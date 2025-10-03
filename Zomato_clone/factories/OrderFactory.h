#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include "../models/Order.h"
#include "../models/Restaurant.h"
#include "../models/Cart.h"
#include "../models/Menu.h"
#include "../strategies/PaymentStrategy.h"
using namespace std;

class OrderFactory {
public:
    virtual Order* createOrder(User* user, Restaurant* res, PaymentStrategy* ps,
                               Cart* cart, vector<Menu*>& items, string& orderType) = 0;
    virtual ~OrderFactory() {}
};

#endif
