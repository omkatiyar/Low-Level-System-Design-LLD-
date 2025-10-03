#ifndef NOW_ORDER_FACTORY_H
#define NOW_ORDER_FACTORY_H

#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"

class NowOrderFactory : public OrderFactory {
public:
    Order* createOrder(User* user, Restaurant* restaurant, PaymentStrategy* ps,
                       Cart* cart, vector<Menu*>& items, string& orderType) override {
        Order* order = nullptr;
        if (orderType == "Delivery") {
            auto delivery = new DeliveryOrder();
            delivery->setLocation(user->getLocation());
            order = delivery;
        } else {
            auto pickup = new PickupOrder();
            pickup->setLocation(restaurant->getLocation());
            order = pickup;
        }
        order->setUser(user);
        order->setRestaurant(restaurant);
        order->setPaymentStrategy(ps);
        order->setMenuItems(items);
        order->setTotalAmount(cart->calculateTotal());
        order->setScheduledTime("NOW");
        return order;
    }
};

#endif
